#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_Visualizer(m_Logic),
      m_Initiated(false)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(m_Visualizer.GetScene());
    ui->graphicsView->setInteractive(false);
    ui->graphicsView->scale(1, -1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    if(m_Initiated){
        m_Visualizer.UpdateScene(double(event->size().width())/event->oldSize().width(),
                             double(event->size().height())/event->oldSize().height());
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_Initiated = true;
    this->setFixedSize(this->size());
    m_Visualizer.StartWorld(ui->delay->value(),ui->graphicsView->size(), ui->activePart->value());
}

void MainWindow::on_pause_clicked()
{
    auto timer = m_Visualizer.GetTimer();
    if(timer->isActive()){
        timer->stop();
    }
    else{
        timer->start();
    }
}

void MainWindow::on_delay_sliderMoved(int position)
{
    m_Visualizer.GetTimer()->setInterval(position);
}

void MainWindow::on_activePart_valueChanged(int value)
{
    m_Visualizer.SetActivePart(value);
}
