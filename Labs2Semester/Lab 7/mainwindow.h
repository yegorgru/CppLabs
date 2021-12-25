#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Bots.h"
#include "botinfo.h"

#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <deque>

#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtCore>
#include <QtGui>
#include <QTableWidgetItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QTableWidget>
#include <QAbstractItemDelegate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void action();

    void form_scene();

    void update_scene();

    void make_start_elements();

private slots:
    void on_pushButton_clicked();

    void on_play_clicked();

    void on_Meat_energy_textChanged(const QString &arg1);

    void on_Plants_energy_textChanged(const QString &arg1);

    void on_Name_textChanged(const QString &arg1);

    void on_update_clicked();

    void select();

private:
    Ui::MainWindow *ui;

    struct coordinates{
        int x;
        int y;


        coordinates(){
            x=0;
            y=0;
        }

        coordinates(int i,int j){
            x=i;
            y=j;
        }
    };

    QString name;

    QTimer* m_timer;

    std::deque<Bot>bots;
    Bot current_bot=Bot(0,0,0);

    int number_of_live_cells;
    int initial_live_cell_energy;
    int max_energy;
    int number_of_gens_of_action;
    int min_energy_for_division;
    int number_of_plants;
    int plants_energy;
    int meat_energy;
    int tree_propagation_speed;

    bool is_action;
    int delay;
    int speed;

    long long turns;
    long long trees_counter;
    long long bots_counter;

    long long red_counter;
    long long blue_counter;
    long long yellow_counter;
    long long orange_counter;
    long long violet_counter;
    long long green_counter;


    unsigned short int elements[50][50]={};
    QGraphicsPixmapItem* items[50][50];
    std::vector<coordinates>changed;

    QIntValidator *validator1;
    QIntValidator *validator2;

    QPixmap RedT;
    QPixmap RedTR;
    QPixmap RedR;
    QPixmap RedDR;
    QPixmap RedD;
    QPixmap RedDL;
    QPixmap RedL;
    QPixmap RedTL;

    QPixmap YellowT;
    QPixmap YellowTR;
    QPixmap YellowR;
    QPixmap YellowDR;
    QPixmap YellowD;
    QPixmap YellowDL;
    QPixmap YellowL;
    QPixmap YellowTL;

    QPixmap BlueT;
    QPixmap BlueTR;
    QPixmap BlueR;
    QPixmap BlueDR;
    QPixmap BlueD;
    QPixmap BlueDL;
    QPixmap BlueL;
    QPixmap BlueTL;

    QPixmap GreenT;
    QPixmap GreenTR;
    QPixmap GreenR;
    QPixmap GreenDR;
    QPixmap GreenD;
    QPixmap GreenDL;
    QPixmap GreenL;
    QPixmap GreenTL;

    QPixmap OrangeT;
    QPixmap OrangeTR;
    QPixmap OrangeR;
    QPixmap OrangeDR;
    QPixmap OrangeD;
    QPixmap OrangeDL;
    QPixmap OrangeL;
    QPixmap OrangeTL;

    QPixmap VioletT;
    QPixmap VioletTR;
    QPixmap VioletR;
    QPixmap VioletDR;
    QPixmap VioletD;
    QPixmap VioletDL;
    QPixmap VioletL;
    QPixmap VioletTL;

    QPixmap Empty;
    QPixmap Meat;
    QPixmap Salad;

    QGraphicsScene *scene;

    coordinates get_ahead(int& what_is_ahead,const Bot& bot){
        coordinates ahead;
        if(bot.view>-1 && bot.view<8){
            if(bot.view==0){
                what_is_ahead=elements[bot.posX][bot.posY-1];
                ahead.x=bot.posX;
                ahead.y=bot.posY-1;
            }
            else if(bot.view==1){
                what_is_ahead=elements[bot.posX+1][bot.posY-1];
                ahead.x=bot.posX+1;
                ahead.y=bot.posY-1;
            }
            else if(bot.view==2){
                what_is_ahead=elements[bot.posX+1][bot.posY];
                ahead.x=bot.posX+1;
                ahead.y=bot.posY;
            }
            else if(bot.view==3){
                what_is_ahead=elements[bot.posX+1][bot.posY+1];
                ahead.x=bot.posX+1;
                ahead.y=bot.posY+1;
            }
            else if(bot.view==4){
                what_is_ahead=elements[bot.posX][bot.posY+1];
                ahead.x=bot.posX;
                ahead.y=bot.posY+1;
            }
            else if(bot.view==5){
                what_is_ahead=elements[bot.posX-1][bot.posY+1];
                ahead.x=bot.posX-1;
                ahead.y=bot.posY+1;
            }
            else if(bot.view==6){
                what_is_ahead=elements[bot.posX-1][bot.posY];
                ahead.x=bot.posX-1;
                ahead.y=bot.posY;
            }
            else {
                what_is_ahead=elements[bot.posX-1][bot.posY-1];
                ahead.x=bot.posX-1;
                ahead.y=bot.posY-1;
            }
        }
        return ahead;
    }

};


#endif // MAINWINDOW_H
