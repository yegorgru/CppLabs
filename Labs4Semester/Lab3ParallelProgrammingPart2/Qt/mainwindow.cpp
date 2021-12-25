/**
\file
\brief .cpp file with implementation of MainWindow class
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
       m_Timer(new QTimer(this)),
       m_SingleShotTimer(new QTimer(this)),
       m_Scene(new QGraphicsScene),
       m_Runner(8)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(m_Scene);

    m_ForkPixmap = QPixmap::fromImage(QImage(":/fork.png"));
    m_PhilosopherPixmap = QPixmap::fromImage(QImage(":/philosopher.png"));
    m_TablePixmap = QPixmap::fromImage(QImage(":/table.png"));
    m_PhilosopherEatPixmap = QPixmap::fromImage(QImage(":/philosopher_eat.png"));
    m_PhilosopherWaitPixmap = QPixmap::fromImage(QImage(":/philosopher_wait.jpg"));
    m_PhilosopherSpeakPixmap = QPixmap::fromImage(QImage(":/philosopher_speak.jpg"));

    connect (m_SingleShotTimer,&QTimer::timeout,this,&MainWindow::PlayChanges);
    m_SingleShotTimer->setSingleShot(true);

    connect (m_Timer,&QTimer::timeout,this,&MainWindow::updateScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_run_button_clicked()
{
    this->setFixedSize(this->size());
    ui->controlBox->setEnabled(false);
    auto size = ui->graphicsView->size();
    m_Items.clear();
    m_Scene->clear();

    m_PhilosopherPixmap = m_PhilosopherPixmap.scaled(QSize(size.width()/12, size.height()/12));
    m_PhilosopherWaitPixmap = m_PhilosopherWaitPixmap.scaled(QSize(size.width()/12, size.height()/12));
    m_PhilosopherEatPixmap = m_PhilosopherEatPixmap.scaled(QSize(size.width()/12, size.height()/12));
    m_PhilosopherSpeakPixmap = m_PhilosopherSpeakPixmap.scaled(QSize(size.width()/12, size.height()/12));
    m_TablePixmap = m_TablePixmap.scaled(QSize(size.width()/2, size.height()/2));
    m_ForkPixmap = m_ForkPixmap.scaled(QSize(size.width()/12, size.height()/12));

    m_Scene->setSceneRect(0,0,size.width()*0.95, size.height()*0.95);

    for(int j = 0; j < 9; j+=2){
        auto item =new QGraphicsPixmapItem;
        if(j % 4 == 0){
            item->setPixmap(m_ForkPixmap);
        }
        else{
            item->setPixmap(m_PhilosopherPixmap);
        }
        item->setPos(j * size.width() / 9, 0);
        m_Items.push_back(item);
        m_Scene->addItem(item);
    }

    for(int i = 2; i < 9; i+=2){
        auto item =new QGraphicsPixmapItem;
        if(i % 4 == 0){
            item->setPixmap(m_ForkPixmap);
        }
        else{
            item->setPixmap(m_PhilosopherPixmap);
        }
        item->setPos(8 * size.width() / 9, i * size.height() / 9);
        m_Items.push_back(item);
        m_Scene->addItem(item);
    }

    for(int j = 6; j >= 0; j-=2){
        auto item =new QGraphicsPixmapItem;
        if(j % 4 == 0){
            item->setPixmap(m_ForkPixmap);
        }
        else{
            item->setPixmap(m_PhilosopherPixmap);
        }
        item->setPos(j * size.width() / 9, 8 * size.height() / 9);
        m_Items.push_back(item);
        m_Scene->addItem(item);
    }

    for(int i = 6; i > 0; i-=2){
        auto item =new QGraphicsPixmapItem;
        if(i % 4 == 0){
            item->setPixmap(m_ForkPixmap);
        }
        else{
            item->setPixmap(m_PhilosopherPixmap);
        }
        item->setPos(0, i * size.height() / 9);
        m_Items.push_back(item);
        m_Scene->addItem(item);
    }

    {
        auto table =new QGraphicsPixmapItem;
        table->setPixmap(m_TablePixmap);
        table->setPos(size.width() / 4, size.height() / 4);
        m_Items.push_back(table);
        m_Scene->addItem(table);
    }

    m_Scene->update();

    m_SingleShotTimer->start(5000);
    m_Runner.Run(ui->steps->value(), ui->eat_chance->value());
}

void MainWindow::PlayChanges(){
    m_Changes = m_Runner.GetResult();
    m_CurPos = 0;
    m_Timer->start(ui->delay->value());
}

void MainWindow::updateScene(){
    int philosopher = m_Changes[m_CurPos].first;
    switch(m_Changes[m_CurPos].second){
    case PhilosophersRunner::TYPE::PH_ORDINARY : {
        m_Items[2*philosopher + 1]->setPixmap(m_PhilosopherPixmap);
        if(m_States[philosopher] == PhilosophersRunner::TYPE::PH_EAT){
            m_Items[2*philosopher]->setPixmap(m_ForkPixmap);
            m_Items[(2*philosopher+2)%16]->setPixmap(m_ForkPixmap);
        }
        m_States[philosopher] = PhilosophersRunner::TYPE::PH_ORDINARY;
        break;
    }
    case PhilosophersRunner::TYPE::PH_EAT : {
        m_Items[2*philosopher + 1]->setPixmap(m_PhilosopherEatPixmap);
        m_Items[2*philosopher]->setPixmap(QPixmap());
        m_Items[(2*philosopher+2)%16]->setPixmap(QPixmap());
        m_States[philosopher] = PhilosophersRunner::TYPE::PH_EAT;
        break;
    }
    case PhilosophersRunner::TYPE::PH_WAIT : {
        m_Items[2*philosopher + 1]->setPixmap(m_PhilosopherWaitPixmap);
        m_States[philosopher] = PhilosophersRunner::TYPE::PH_WAIT;
        break;
    }
    case PhilosophersRunner::TYPE::PH_SPEAK : {
        m_Items[2*philosopher + 1]->setPixmap(m_PhilosopherSpeakPixmap);
        m_States[philosopher] = PhilosophersRunner::TYPE::PH_SPEAK;
        break;
    }
    }
    m_Scene->update();
    if(m_CurPos == m_Changes.size()-1){
        m_Timer->stop();
        ui->controlBox->setEnabled(true);
    }
    else{
        m_CurPos++;
    }
    if(ui->delay->value() == 5000){
        for(auto i : m_States){
            if(i.second == PhilosophersRunner::TYPE::PH_EAT){
                QSound::play(":/Cheawing.wav");
            }
            else if(i.second == PhilosophersRunner::TYPE::PH_SPEAK){
                QSound::play(":/voice"+QString::fromStdString(std::to_string(i.first+1))+".wav");
            }
        }
    }
}
