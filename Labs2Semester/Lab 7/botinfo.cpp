#include "botinfo.h"
#include "choose_gen.h"

botInfo::botInfo(Bot& bot, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::botInfo)
{
    ui->setupUi(this);

    B=&bot;

    if(bot.color==1){
        ui->color_value->setText("Red");
        ui->superpower_value->setText("tasteless");
    }
    else if(bot.color==2){
        ui->color_value->setText("Yellow");
        ui->superpower_value->setText("salad eater");
    }
    else if(bot.color==3){
        ui->color_value->setText("Violet");
        ui->superpower_value->setText("meat eater");
    }
    else if(bot.color==4){
        ui->color_value->setText("Orange");
        ui->superpower_value->setText("killer");
    }
    else if(bot.color==5){
        ui->color_value->setText("Blue");
        //ui->color_value->setText(QString::number(bot.color));
        ui->superpower_value->setText("altruist");
    }
    else{
        ui->color_value->setText("Green");
        //ui->color_value->setText(QString::number(bot.color));
        ui->superpower_value->setText("inspires confidence");
    }
    ui->energy_value->setText(QString::number(bot.energy));
    ui->view_value->setText(QString::number(bot.view));
    ui->age_value->setText(QString::number(bot.age));

    ui->number_of_gens_of_action_value->setText(QString::number(bot.number_of_gens_of_action));
    ui->chance_of_mutation_value->setText(QString::number(bot.chance_of_mutation));
    ui->min_energy_for_division_value->setText(QString::number(bot.min_energy_for_division));
    ui->number_of_gens_of_action_value->setText(QString::number(bot.number_of_gens_of_action));
    ui->condition_for_attack_value->setText(QString::number(bot.condition_for_attack));

    ui->Gens_action_table->setRowCount(10);
    ui->Gens_action_table->setColumnCount(7);
    for(int i=0;i<7;i++){
        ui->Gens_action_table->setColumnWidth(i,70);
    }
    ui->Gens_action_table->setHorizontalHeaderLabels({"Nothing","Meat","Salad","Wall","Friend","Enemy","Fail"});
    ui->Gens_action_table->setVerticalHeaderLabels({"1","2","3","4","5","6","7","8","9","10"});

    ui->Gens_irritation_table->setRowCount(8);
    ui->Gens_irritation_table->setColumnCount(7);
    for(int i=0;i<7;i++){
        ui->Gens_irritation_table->setColumnWidth(i,70);
    }
    ui->Gens_irritation_table->setHorizontalHeaderLabels({"Nothing","Meat","Salad","Wall","Friend","Enemy","Fail"});
    ui->Gens_irritation_table->setVerticalHeaderLabels({"T","TR","R","DR","D","DL","L","TL"});

    for(int i=0;i<bot.number_of_gens_of_action;i++){
        for(int j=0;j<7;j++){
            ui->Gens_action_table->setItem(i,j,new QTableWidgetItem(QString::number(bot.gens_of_action[i][j])));
            if(bot.gens_of_action[i][j]==0){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/T.png")).scaled(30, 30));
            }
            else if(bot.gens_of_action[i][j]==1){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/TR.png")).scaled(30, 30));
            }
            else if(bot.gens_of_action[i][j]==2){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/R.png")).scaled(30, 30));
            }
            else if(bot.gens_of_action[i][j]==3){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/DR.png")).scaled(30, 30));
            }
            else if(bot.gens_of_action[i][j]==4){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/D.png")).scaled(30, 30));
            }
            else if(bot.gens_of_action[i][j]==5){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/DL.png")).scaled(30, 30));
            }
            else if(bot.gens_of_action[i][j]==6){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/L.png")).scaled(30, 30));
            }
            else if(bot.gens_of_action[i][j]==7){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/TL.png")).scaled(30, 30));
            }
            else if(bot.gens_of_action[i][j]==8){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/stop.png")).scaled(30, 30));
            }
            else if(bot.gens_of_action[i][j]==9){
                ui->Gens_action_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/war.jpg")).scaled(30, 30));
            }
        }
    }

    for(int i=0;i<8;i++){
        for(int j=0;j<7;j++){
            ui->Gens_irritation_table->setItem(i,j,new QTableWidgetItem(QString::number(bot.gens_of_irritation[i][j])));
            if(bot.gens_of_irritation[i][j]==0){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/T.png")).scaled(30, 30));
            }
            else if(bot.gens_of_irritation[i][j]==1){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/TR.png")).scaled(30, 30));
            }
            else if(bot.gens_of_irritation[i][j]==2){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/R.png")).scaled(30, 30));
            }
            else if(bot.gens_of_irritation[i][j]==3){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/DR.png")).scaled(30, 30));
            }
            else if(bot.gens_of_irritation[i][j]==4){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/D.png")).scaled(30, 30));
            }
            else if(bot.gens_of_irritation[i][j]==5){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/DL.png")).scaled(30, 30));
            }
            else if(bot.gens_of_irritation[i][j]==6){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/L.png")).scaled(30, 30));
            }
            else if(bot.gens_of_irritation[i][j]==7){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/TL.png")).scaled(30, 30));
            }
            else if(bot.gens_of_irritation[i][j]==8){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/stop.png")).scaled(30, 30));
            }
            else if(bot.gens_of_irritation[i][j]==9){
                ui->Gens_irritation_table->item(i,j)->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(":/images/war.jpg")).scaled(30, 30));
            }
        }
    }

    int element = bot.color*10+bot.view;
    ui->image->setScaledContents(true);
    QPixmap a;
    switch(element){
    case 10:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/RedT.png")));
        break;
    case 11:
        a=QPixmap::fromImage(QImage(":/images/RedTR.png"));
        ui->image->setPixmap(a);
        break;
    case 12:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/RedR.png")));
        break;
    case 13:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/RedDR.png")));
        break;
    case 14:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/RedD.png")));
        break;
    case 15:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/RedDL.png")));
        break;
    case 16:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/RedL.png")));
        break;
    case 17:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/RedTL.png")));
        break;
    case 20:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/YellowT.png")));
        break;
    case 21:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/YellowTR.png")));
        break;
    case 22:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/YellowR.png")));
        break;
    case 23:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/YellowDR.png")));
        break;
    case 24:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/YellowD.png")));
        break;
    case 25:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/YellowDL.png")));
        break;
    case 26:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/YellowL.png")));
        break;
    case 27:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/YellowTL.png")));
        break;
    case 30:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/VioletT.png")));
        break;
    case 31:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/VioletTR.png")));
        break;
    case 32:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/VioletR.png")));
        break;
    case 33:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/VioletDR.png")));
        break;
    case 34:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/VioletD.png")));
        break;
    case 35:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/VioletDL.png")));
        break;
    case 36:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/VioletL.png")));
        break;
    case 37:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/VioletTL.png")));
        break;
    case 40:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/OrangeT.png")));
        break;
    case 41:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/OrangeTR.png")));
        break;
    case 42:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/OrangeR.png")));
        break;
    case 43:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/OrangeDR.png")));
        break;
    case 44:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/OrangeD.png")));
        break;
    case 45:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/OrangeDL.png")));
        break;
    case 46:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/OrangeL.png")));
        break;
    case 47:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/OrangeTL.png")));
        break;
    case 50:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/BlueT.png")));
        break;
    case 51:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/BlueTR.png")));
        break;
    case 52:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/BlueR.png")));
        break;
    case 53:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/BlueDR.png")));
        break;
    case 54:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/BlueD.png")));
        break;
    case 55:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/BlueDL.png")));
        break;
    case 56:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/BlueL.png")));
        break;
    case 57:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/BlueTL.png")));
        break;
    case 60:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/GreenT.png")));
        break;
    case 61:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/GreenTR.png")));
        break;
    case 62:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/GreenR.png")));
        break;
    case 63:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/GreenDR.png")));
        break;
    case 64:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/GreenD.png")));
        break;
    case 65:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/GreenDL.png")));
        break;
    case 66:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/GreenL.png")));
        break;
    case 67:
        ui->image->setPixmap(QPixmap::fromImage(QImage(":/images/GreenTL.png")));
        break;
    }

}

botInfo::~botInfo()
{
    ui->Gens_action_table->clear();
    ui->Gens_irritation_table->clear();
    delete ui;
}


void botInfo::on_Gens_action_table_itemClicked(QTableWidgetItem *item)
{
    try {
        int& value = B->gens_of_action[item->row()][item->column()];
        choose_gen info(value,item);
        info.setModal(true);
        info.exec();
    } catch(_exception) {

    }
}

void botInfo::on_Gens_irritation_table_itemClicked(QTableWidgetItem *item)
{
    try {
        int& value = B->gens_of_irritation[item->row()][item->column()];
        choose_gen info(value,item);
        info.setModal(true);
        info.exec();
    } catch(_exception) {

    }
}
