#include "choose_gen.h"
#include "ui_choose_gen.h"

choose_gen::choose_gen(int& v, QTableWidgetItem *item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choose_gen)
{
    ui->setupUi(this);

    scene=new QGraphicsScene;
    scene->setSceneRect ( 0,0,70,700 ) ;

    for(int i=0;i<10;i++){
        items[i]=new QGraphicsPixmapItem;
        if(!(item->column()==6 && i==9)){
            items[i]->setFlags(QGraphicsItem::ItemIsSelectable);
        }
        items[i]->setY(70*i);
        scene->addItem(items[i]);
    }
    items[0]->setScale(0.1);
    items[1]->setScale(0.15);
    items[2]->setScale(0.1);
    items[3]->setScale(0.15);
    items[4]->setScale(0.1);
    items[5]->setScale(0.15);
    items[6]->setScale(0.1);
    items[7]->setScale(0.15);
    items[8]->setScale(0.1);
    items[9]->setScale(0.12);
    items[0]->setPixmap( QPixmap::fromImage(QImage(":/images/T.png")));
    items[1]->setPixmap( QPixmap::fromImage(QImage(":/images/TR.png")));
    items[2]->setPixmap( QPixmap::fromImage(QImage(":/images/R.png")));
    items[3]->setPixmap( QPixmap::fromImage(QImage(":/images/DR.png")));
    items[4]->setPixmap( QPixmap::fromImage(QImage(":/images/D.png")));
    items[5]->setPixmap( QPixmap::fromImage(QImage(":/images/DL.png")));
    items[6]->setPixmap( QPixmap::fromImage(QImage(":/images/L.png")));
    items[7]->setPixmap( QPixmap::fromImage(QImage(":/images/TL.png")));
    items[8]->setPixmap( QPixmap::fromImage(QImage(":/images/stop.png")));
    items[9]->setPixmap( QPixmap::fromImage(QImage(":/images/war.jpg")));
    value=&v;
    it=item;

    ui->graphicsView->setScene(scene);

    connect (scene,&QGraphicsScene::selectionChanged, this, &choose_gen::select);
}

choose_gen::~choose_gen()
{
    scene->clear();
    delete scene;
    delete ui;
}


void choose_gen::select(){
        if(scene->selectedItems().size()>0){
            if(scene->selectedItems().last() == items[0]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/T.png")).scaled(30, 30));
                it->setText("0");
                *value = 0;
            }
            else if(scene->selectedItems().last() == items[1]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/TR.png")).scaled(30, 30));
                it->setText("1");
                *value = 1;
            }
            else if(scene->selectedItems().last() == items[2]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/R.png")).scaled(30, 30));
                it->setText("2");
                *value = 2;
            }
            else if(scene->selectedItems().last() == items[3]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/DR.png")).scaled(30, 30));
                it->setText("3");
                *value = 3;
            }
            else if(scene->selectedItems().last() == items[4]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/D.png")).scaled(30, 30));
                it->setText("4");
                *value = 4;
            }
            else if(scene->selectedItems().last() == items[5]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/DL.png")).scaled(30, 30));
                it->setText("5");
                *value = 5;
            }
            else if(scene->selectedItems().last() == items[6]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/L.png")).scaled(30, 30));
                it->setText("6");
                *value = 6;
            }
            else if(scene->selectedItems().last() == items[7]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/TL.png")).scaled(30, 30));
                it->setText("7");
                *value = 7;
            }
            else if(scene->selectedItems().last() == items[8]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/stop.png")).scaled(30, 30));
                it->setText("8");
                *value = 8;
            }
            else if(scene->selectedItems().last() == items[9]){
                it->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/war.jpg")).scaled(30, 30));
                it->setText("9");
                *value = 9;
            }

        }
}
