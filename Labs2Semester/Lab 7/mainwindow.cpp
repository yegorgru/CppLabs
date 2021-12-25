#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worldparameters.h"

std::random_device rd;
std::mt19937 mersenne(rd());

const QString part_way=":/images/";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/images/drawing.png"));
    name="";
    number_of_live_cells=0;
    initial_live_cell_energy=0;
    number_of_gens_of_action=0;
    min_energy_for_division=0;
    number_of_plants=0;
    plants_energy=0;
    meat_energy=0;
    is_action=false;
    delay=500;
    turns = 0;
    bots_counter = 0;
    trees_counter = 0;

    current_bot.alive=false;

    m_timer = new QTimer(this);
    connect (m_timer,&QTimer::timeout,this,&MainWindow::update_scene);

    scene=new QGraphicsScene;
    scene->setSceneRect ( 0,0,900,900 );



    connect (scene,&QGraphicsScene::selectionChanged, this, &MainWindow::select);

    QPixmap wall = QPixmap::fromImage(QImage(part_way+"Wall.png"));

    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++){
            items[i][j]=new QGraphicsPixmapItem;
            if(i==0||j==0||i==49||j==49){
                items[i][j]->setPixmap(wall);
                elements[i][j]=4;
            }
            items[i][j]->setScale(0.02);
            items[i][j]->setFlags(QGraphicsItem::ItemIsSelectable);
            items[i][j]->setPos(18*i,18*j);
            scene->addItem(items[i][j]);
        }
    }

    RedT = QPixmap::fromImage(QImage(part_way+"RedT.png"));
    RedTR = QPixmap::fromImage(QImage(part_way+"RedTR.png"));
    RedR = QPixmap::fromImage(QImage(part_way+"RedR.png"));
    RedDR = QPixmap::fromImage(QImage(part_way+"RedDR.png"));
    RedD = QPixmap::fromImage(QImage(part_way+"RedD.png"));
    RedDL = QPixmap::fromImage(QImage(part_way+"RedDL.png"));
    RedL = QPixmap::fromImage(QImage(part_way+"RedL.png"));
    RedTL = QPixmap::fromImage(QImage(part_way+"RedTL.png"));

    YellowT = QPixmap::fromImage(QImage(part_way+"YellowT.png"));
    YellowTR = QPixmap::fromImage(QImage(part_way+"YellowTR.png"));
    YellowR = QPixmap::fromImage(QImage(part_way+"YellowR.png"));
    YellowDR = QPixmap::fromImage(QImage(part_way+"YellowDR.png"));
    YellowD = QPixmap::fromImage(QImage(part_way+"YellowD.png"));
    YellowDL = QPixmap::fromImage(QImage(part_way+"YellowDL.png"));
    YellowL = QPixmap::fromImage(QImage(part_way+"YellowL.png"));
    YellowTL = QPixmap::fromImage(QImage(part_way+"YellowTL.png"));

    BlueT = QPixmap::fromImage(QImage(part_way+"BlueT.png"));
    BlueTR = QPixmap::fromImage(QImage(part_way+"BlueTR.png"));
    BlueR = QPixmap::fromImage(QImage(part_way+"BlueR.png"));
    BlueDR = QPixmap::fromImage(QImage(part_way+"BlueDR.png"));
    BlueD = QPixmap::fromImage(QImage(part_way+"BlueD.png"));
    BlueDL = QPixmap::fromImage(QImage(part_way+"BlueDL.png"));
    BlueL = QPixmap::fromImage(QImage(part_way+"BlueL.png"));
    BlueTL = QPixmap::fromImage(QImage(part_way+"BlueTL.png"));

    GreenT = QPixmap::fromImage(QImage(part_way+"GreenT.png"));
    GreenTR = QPixmap::fromImage(QImage(part_way+"GreenTR.png"));
    GreenR = QPixmap::fromImage(QImage(part_way+"GreenR.png"));
    GreenDR = QPixmap::fromImage(QImage(part_way+"GreenDR.png"));
    GreenD = QPixmap::fromImage(QImage(part_way+"GreenD.png"));
    GreenDL = QPixmap::fromImage(QImage(part_way+"GreenDL.png"));
    GreenL = QPixmap::fromImage(QImage(part_way+"GreenL.png"));
    GreenTL = QPixmap::fromImage(QImage(part_way+"GreenTL.png"));

    OrangeT = QPixmap::fromImage(QImage(part_way+"OrangeT.png"));
    OrangeTR = QPixmap::fromImage(QImage(part_way+"OrangeTR.png"));
    OrangeR = QPixmap::fromImage(QImage(part_way+"OrangeR.png"));
    OrangeDR = QPixmap::fromImage(QImage(part_way+"OrangeDR.png"));
    OrangeD = QPixmap::fromImage(QImage(part_way+"OrangeD.png"));
    OrangeDL = QPixmap::fromImage(QImage(part_way+"OrangeDL.png"));
    OrangeL = QPixmap::fromImage(QImage(part_way+"OrangeL.png"));
    OrangeTL = QPixmap::fromImage(QImage(part_way+"OrangeTL.png"));

    VioletT = QPixmap::fromImage(QImage(part_way+"VioletT.png"));
    VioletTR = QPixmap::fromImage(QImage(part_way+"VioletTR.png"));
    VioletR = QPixmap::fromImage(QImage(part_way+"VioletR.png"));
    VioletDR = QPixmap::fromImage(QImage(part_way+"VioletDR.png"));
    VioletD = QPixmap::fromImage(QImage(part_way+"VioletD.png"));
    VioletDL = QPixmap::fromImage(QImage(part_way+"VioletDL.png"));
    VioletL = QPixmap::fromImage(QImage(part_way+"VioletL.png"));
    VioletTL = QPixmap::fromImage(QImage(part_way+"VioletTL.png"));

    Meat = QPixmap::fromImage(QImage(part_way+"Meat.png"));
    Salad = QPixmap::fromImage(QImage(part_way+"Salad.png"));
    Empty = QPixmap::fromImage(QImage(part_way+"Empty.png"));

    ui->graphicsView->setScene(scene);

    validator1 = new QIntValidator(1,200,this);
    ui->Plants_energy->setValidator(validator1);
    validator2 = new QIntValidator(1,300,this);
    ui->Meat_energy->setValidator(validator2);

    red_counter = 0 ;
    blue_counter = 0 ;
    yellow_counter = 0 ;
    orange_counter = 0 ;
    violet_counter = 0 ;
    green_counter = 0 ;

    ui->play->setVisible(false);
    ui->update->setVisible(false);
    ui->parameters->setVisible(false);
    ui->turns_text->setVisible(false);
    ui->Turns_counter->setVisible(false);
    ui->statistic_information->setVisible(false);
    ui->without_changes_2->setVisible(false);
}

MainWindow::~MainWindow()
{
    scene->clear();
    delete scene;
    delete validator1;
    delete validator2;
    delete m_timer;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    on_play_clicked();
    bots.clear();
    turns=0;
    trees_counter=0;
    bots_counter=0;
    yellow_counter=0;
    blue_counter=0;
    violet_counter=0;
    orange_counter=0;
    green_counter=0;
    red_counter=0;
    for(int i=1;i<49;i++){
        for(int j=1;j<49;j++){
            elements[i][j]=0;
        }
    }
    QMessageBox msgBox;
    msgBox.setText("Create random world?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int reply = msgBox.exec();

    if(reply==QMessageBox::Yes){
            this->name="Random world";
            this->number_of_live_cells=1+mersenne()%1000;
            this->initial_live_cell_energy=1+mersenne()%1000;
            this->number_of_gens_of_action=1+mersenne()%10;
            this->min_energy_for_division=1+mersenne()%600;
            this->number_of_plants=1+mersenne()%2000;
            this->plants_energy=1+mersenne()%200;
            this->meat_energy=1+mersenne()%300;
            this->tree_propagation_speed=1+mersenne()%3;;
            this->speed = 1+mersenne()%10;;
            this->delay = (11-this->speed)*100;
            this->bots_counter = this->number_of_live_cells;
            this->trees_counter = this->number_of_plants;
            this->max_energy =  1+mersenne()%1000;

            this->ui->Name->setText(name);
            this->ui->Plants_energy->setText(QString::number(plants_energy));
            this->ui->Meat_energy->setText(QString::number(meat_energy));
            this->ui->Speed->setValue(this->speed);
            this->ui->Tree_propagation_speed->setValue(tree_propagation_speed);
            ui->number_of_gens->setText(QString::number(this->number_of_gens_of_action));
            ui->number_of_live->setText(QString::number(this->number_of_live_cells));
            ui->number_of_plant->setText(QString::number(this->number_of_plants));
            ui->initial_live->setText(QString::number(this->initial_live_cell_energy));
            ui->min_energy->setText(QString::number(this->min_energy_for_division));
            ui->max_live->setText(QString::number(this->max_energy));
            is_action=true;
            if(is_action){
                for(int i=1;i<49;i++){
                    for(int j=1;j<49;j++){
                        changed.push_back({i,j});
                    }
                }
                is_action=false;
                make_start_elements();
                form_scene();
                scene->update();
                ui->graphicsView->update();
                ui->play->setVisible(true);
                ui->update->setVisible(true);
                ui->parameters->setVisible(true);
                ui->turns_text->setVisible(true);
                ui->Turns_counter->setVisible(true);
                ui->statistic_information->setVisible(true);
                ui->without_changes_2->setVisible(true);
            }

    }
    else if(reply==QMessageBox::No){
        WorldParameters Parameters;
        Parameters.setModal(true);
        Parameters.exec();

        if(Parameters.correct)
        {
            this->name=Parameters.name;
            this->number_of_live_cells=Parameters.number_of_live_cells;
            this->initial_live_cell_energy=Parameters.initial_live_cell_energy;
            this->number_of_gens_of_action=Parameters.number_of_gens_of_action;
            this->min_energy_for_division=Parameters.min_energy_for_division;
            this->number_of_plants=Parameters.number_of_plants;
            this->plants_energy=Parameters.plants_energy;
            this->meat_energy=Parameters.meat_energy;
            this->tree_propagation_speed=Parameters.tree_propagation_speed;
            this->speed = Parameters.speed;
            this->delay = (11-Parameters.speed)*100;
            this->bots_counter = this->number_of_live_cells;
            this->trees_counter = this->number_of_plants;
            this->max_energy=Parameters.max_energy;

            this->ui->Name->setText(name);
            this->ui->Plants_energy->setText(QString::number(plants_energy));
            this->ui->Meat_energy->setText(QString::number(meat_energy));
            this->ui->Speed->setValue(Parameters.speed);
            this->ui->Tree_propagation_speed->setValue(tree_propagation_speed);
            this->ui->Name->setText(name);
            this->ui->Plants_energy->setText(QString::number(plants_energy));
            this->ui->Meat_energy->setText(QString::number(meat_energy));
            this->ui->Speed->setValue(this->speed);
            this->ui->Tree_propagation_speed->setValue(tree_propagation_speed);
            ui->number_of_gens->setText(QString::number(this->number_of_gens_of_action));
            ui->number_of_live->setText(QString::number(this->number_of_live_cells));
            ui->number_of_plant->setText(QString::number(this->number_of_plants));
            ui->initial_live->setText(QString::number(this->initial_live_cell_energy));
            ui->min_energy->setText(QString::number(this->min_energy_for_division));
            ui->max_live->setText(QString::number(this->max_energy));
            is_action=true;
        }
        else{
            QMessageBox::critical(this,"","Something went wrong");
            is_action = false;
        }
        if(is_action){
            for(int i=1;i<49;i++){
                for(int j=1;j<49;j++){
                    changed.push_back({i,j});
                }
            }
            is_action=false;
            make_start_elements();
            form_scene();
            scene->update();
            ui->graphicsView->update();
            ui->play->setVisible(true);
            ui->update->setVisible(true);
            ui->parameters->setVisible(true);
            ui->turns_text->setVisible(true);
            ui->Turns_counter->setVisible(true);
            ui->statistic_information->setVisible(true);
            ui->without_changes_2->setVisible(true);
        }
    }
}

void MainWindow::update_scene(){
    if(is_action){
        int number_of_new_trees=0;
        if(tree_propagation_speed==1){
            number_of_new_trees=5;
        }
        else if(tree_propagation_speed==2){
            number_of_new_trees=15;
        }
        else if(tree_propagation_speed==3){
            number_of_new_trees=30;
        }
        else if(tree_propagation_speed==4){
            number_of_new_trees=45;
        }
        else if(tree_propagation_speed==5){
            number_of_new_trees=60;
        }
        else if(tree_propagation_speed==6){
            number_of_new_trees=85;
        }
        else if(tree_propagation_speed==7){
            number_of_new_trees=120;
        }
        else if(tree_propagation_speed==8){
            number_of_new_trees=200;
        }
        else if(tree_propagation_speed==9){
            number_of_new_trees=350;
        }
        else{
            number_of_new_trees=500;
        }
        for(int i=0;i<number_of_new_trees;i++){
            int posX=1+mersenne()%49;
            int posY=1+mersenne()%49;
            if(elements[posX][posY]==1){
                elements[posX][posY]=3;
                trees_counter++;
                changed.push_back({posX,posY});
            }
        }
        for(size_t i=0;i<bots.size();i++){
            if(bots[i].alive==true){
                bots[i].age++;
                bots[i].energy--;
                if(bots[i].energy<1){
                    bots[i].alive=false;
                    elements[bots[i].posX][bots[i].posY]=2;
                    changed.push_back({bots[i].posX,bots[i].posY});
                    if(bots[i].color == 1){
                        red_counter--;
                    }
                    else if(bots[i].color == 2){
                        yellow_counter--;
                    }
                    else if(bots[i].color == 3){
                        violet_counter--;
                    }
                    else if(bots[i].color == 4){
                        orange_counter--;
                    }
                    else if(bots[i].color == 5){
                        blue_counter--;
                    }
                    else if(bots[i].color == 6){
                        green_counter--;
                    }
                    bots.erase(bots.begin()+i);
                    i--;
                }
                else{
                    bool go=false;
                    bots[i].view=mersenne()%8;
                    int what_is_ahead;
                    coordinates ahead=get_ahead(what_is_ahead,bots[i]);
                    if(bots.size()<1000 && bots[i].energy>bots[i].min_energy_for_division-1 && what_is_ahead==1){
                        bots_counter++;
                        bots[i].energy/=2;
                        bots.push_back(bots[i]);
                        if(bots[bots.size()-1].color == 1){
                            red_counter++;
                        }
                        else if(bots[bots.size()-1].color == 2){
                            yellow_counter++;
                        }
                        else if(bots[bots.size()-1].color == 3){
                            violet_counter++;
                        }
                        else if(bots[bots.size()-1].color == 4){
                            orange_counter++;
                        }
                        else if(bots[bots.size()-1].color == 5){
                            blue_counter++;
                        }
                        else if(bots[bots.size()-1].color == 6){
                            green_counter++;
                        }
                        changed.push_back({bots[i].posX,bots[i].posY});
                        go=true;
                    }
                    else{
                        int action;
                        int attack_fall;
                        if(bots[i].irritation!=10){
                            if(what_is_ahead/10==0){
                                action=bots[i].gens_of_irritation[bots[i].irritation][what_is_ahead-1];
                                attack_fall=bots[i].gens_of_irritation[bots[i].irritation][6];
                            }
                            else if(what_is_ahead/10==bots[i].color || what_is_ahead/10==6){
                                if(bots[i].superpower==5){
                                    for(size_t j=0;j<bots.size();j++){
                                        if(bots[j].posX==ahead.x && bots[j].posY==ahead.y){
                                            int energy=(bots[i].energy+bots[j].energy)/2;
                                            bots[i].energy=energy;
                                            bots[j].energy=energy;
                                        }
                                    }
                                }
                                action=bots[i].gens_of_irritation[bots[i].irritation][4];
                                attack_fall=bots[i].gens_of_irritation[bots[i].irritation][6];
                            }
                            else{
                                action=bots[i].gens_of_irritation[bots[i].irritation][5];
                                attack_fall=bots[i].gens_of_irritation[bots[i].irritation][6];
                            }
                            bots[i].irritation=10;
                        }
                        else{
                            if(what_is_ahead/10==0){
                                action=bots[i].gens_of_action[bots[i].counter][what_is_ahead-1];
                                attack_fall=bots[i].gens_of_action[bots[i].counter][6];
                            }
                            else if(what_is_ahead/10==bots[i].color || what_is_ahead/10==6){
                                action=bots[i].gens_of_action[bots[i].counter][4];
                                attack_fall=bots[i].gens_of_action[bots[i].counter][6];
                                if(bots[i].superpower==5){
                                    for(size_t j=0;j<bots.size();j++){
                                        if(bots[j].posX==ahead.x && bots[j].posY==ahead.y){
                                            int energy=(bots[i].energy+bots[j].energy)/2;
                                            bots[i].energy=energy;
                                            bots[j].energy=energy;
                                        }
                                    }
                                }
                            }
                            else{
                                action=bots[i].gens_of_action[bots[i].counter][5];
                                attack_fall=bots[i].gens_of_action[bots[i].counter][6];
                            }
                            bots[i].counter=(bots[i].counter+1)%bots[i].number_of_gens_of_action;
                        }
                        if(action==9){
                            if(what_is_ahead==1){
                                action=0;
                                go=true;
                            }
                            else if(what_is_ahead==2){
                                bots[i].energy+=meat_energy;
                                if(bots[i].superpower==3){
                                    bots[i].energy+=meat_energy/5;
                                }
                                if(bots[i].energy > max_energy){
                                    bots[i].energy = max_energy;
                                }
                                go=true;
                            }
                            else if(what_is_ahead==3){
                                bots[i].energy+=plants_energy;
                                if(bots[i].superpower==2){
                                    bots[i].energy+=plants_energy/5;
                                }
                                if(bots[i].energy > max_energy){
                                    bots[i].energy = max_energy;
                                }
                                go=true;
                            }
                            else if(what_is_ahead==4){
                                continue;
                            }
                            else{
                                for(size_t j=0;j<bots.size();j++){
                                    if(bots[j].posX==ahead.x && bots[j].posY==ahead.y){
                                        if(bots[i].superpower!=4){
                                                if(bots[i].energy-bots[j].energy>bots[i].condition_for_attack-1){
                                                    bots[j].energy-=bots[i].condition_for_attack;
                                                    bots[i].energy+=bots[i].condition_for_attack;
                                                    if(bots[i].energy > max_energy){
                                                        bots[i].energy = max_energy;
                                                    }
                                                    if(bots[j].posX<bots[i].posX){
                                                        if(bots[j].posY<bots[i].posY){
                                                            bots[j].irritation=3;
                                                        }
                                                        else if(bots[j].posY==bots[i].posY){
                                                            bots[j].irritation=2;
                                                        }
                                                        else{
                                                            bots[j].irritation=1;
                                                        }
                                                    }
                                                    else if(bots[j].posX>bots[i].posX){
                                                        if(bots[j].posY<bots[i].posY){
                                                            bots[j].irritation=5;
                                                        }
                                                        else if(bots[j].posY==bots[i].posY){
                                                            bots[j].irritation=6;
                                                        }
                                                        else{
                                                            bots[j].irritation=7;
                                                        }
                                                    }
                                                    else{
                                                        if(bots[j].posY<bots[i].posY){
                                                            bots[j].irritation=4;
                                                        }
                                                        else{
                                                            bots[j].irritation=0;
                                                        }
                                                    }

                                                    if(bots[j].energy<1 && bots[j].superpower==1 && bots[i].color!=bots[j].color){
                                                        bots[i].energy=0;
                                                    }
                                                }
                                                else{
                                                    action=attack_fall;
                                                }
                                        }
                                        else{
                                            bots[i].energy-=(bots[i].condition_for_attack/5);
                                            bots[j].energy=0;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                        if(action==8){
                            continue;
                        }
                        if(action>-1 && action<8) {
                            bots[i].view=(bots[i].view+action)%8;
                            ahead=get_ahead(what_is_ahead,bots[i]);
                            if(what_is_ahead==1){
                                 go=true;
                            }
                        }
                        if(!(action>-1&&action<10)){
                            std::cout<<"Error";
                        }
                    }
                    if(go){
                        int buff=elements[bots[i].posX][bots[i].posY];
                        elements[bots[i].posX][bots[i].posY]=1;
                        changed.push_back({bots[i].posX,bots[i].posY});
                        if(bots[i].view==0){
                            bots[i].posY--;
                        }
                        else if(bots[i].view==1){
                            bots[i].posX++;
                            bots[i].posY--;
                        }
                        else if(bots[i].view==2){
                            bots[i].posX++;
                        }
                        else if(bots[i].view==3){
                            bots[i].posX++;
                            bots[i].posY++;
                        }
                        else if(bots[i].view==4){
                            bots[i].posY++;
                        }
                        else if(bots[i].view==5){
                            bots[i].posX--;
                            bots[i].posY++;
                        }
                        else if(bots[i].view==6){
                            bots[i].posX--;
                        }
                        else {
                            bots[i].posX--;
                            bots[i].posY--;
                        }
                        elements[bots[i].posX][bots[i].posY]=buff;
                    }
                    changed.push_back({bots[i].posX,bots[i].posY});
                    elements[bots[i].posX][bots[i].posY]=bots[i].color*10+bots[i].view;
                }
            }
            else{
                elements[bots[i].posX][bots[i].posY]=2;
                changed.push_back({bots[i].posX,bots[i].posY});
                if(bots[i].color == 1){
                    red_counter--;
                }
                else if(bots[i].color == 2){
                    yellow_counter--;
                }
                else if(bots[i].color == 3){
                    violet_counter--;
                }
                else if(bots[i].color == 4){
                    orange_counter--;
                }
                else if(bots[i].color == 5){
                    blue_counter--;
                }
                else if(bots[i].color == 6){
                    green_counter--;
                }
                bots.erase(bots.begin()+i);
                i--;
            }
        }
        turns++;
        ui->Turns_counter->setText(QString::number(turns));
        ui->counter_red->setText(QString::number(red_counter));
        ui->counter_blue->setText(QString::number(blue_counter));
        ui->counter_orange->setText(QString::number(orange_counter));
        ui->counter_violet->setText(QString::number(violet_counter));
        ui->counter_yellow->setText(QString::number(yellow_counter));
        ui->counter_green->setText(QString::number(green_counter));
        ui->Tree_counter->setText(QString::number(this->trees_counter));
        ui->Bots_counter->setText(QString::number(this->bots_counter));
        form_scene();
        scene->update();
        ui->graphicsView->update();
    }
}

void MainWindow::form_scene(){
    if(changed.size()>0){
        int i;
        int j;
        for(auto k:changed){
                i=k.x;
                j=k.y;
                switch(elements[i][j]){
                case 1:
                    items[i][j]->setPixmap(Empty);
                    break;
                case 2:
                    items[i][j]->setPixmap(Meat);
                    break;
                case 3:
                    items[i][j]->setPixmap(Salad);
                    break;
                case 10:
                    items[i][j]->setPixmap(RedT);
                    break;
                case 11:
                    items[i][j]->setPixmap(RedTR);
                    break;
                case 12:
                    items[i][j]->setPixmap(RedR);
                    break;
                case 13:
                    items[i][j]->setPixmap(RedDR);
                    break;
                case 14:
                    items[i][j]->setPixmap(RedD);
                    break;
                case 15:
                    items[i][j]->setPixmap(RedDL);
                    break;
                case 16:
                    items[i][j]->setPixmap(RedL);
                    break;
                case 17:
                    items[i][j]->setPixmap(RedTL);
                    break;
                case 20:
                    items[i][j]->setPixmap(YellowT);
                    break;
                case 21:
                    items[i][j]->setPixmap(YellowTR);
                    break;
                case 22:
                    items[i][j]->setPixmap(YellowR);
                    break;
                case 23:
                    items[i][j]->setPixmap(YellowDR);
                    break;
                case 24:
                    items[i][j]->setPixmap(YellowD);
                    break;
                case 25:
                    items[i][j]->setPixmap(YellowDL);
                    break;
                case 26:
                    items[i][j]->setPixmap(YellowL);
                    break;
                case 27:
                    items[i][j]->setPixmap(YellowTL);
                    break;
                case 30:
                    items[i][j]->setPixmap(VioletT);
                    break;
                case 31:
                    items[i][j]->setPixmap(VioletTR);
                    break;
                case 32:
                    items[i][j]->setPixmap(VioletR);
                    break;
                case 33:
                    items[i][j]->setPixmap(VioletDR);
                    break;
                case 34:
                    items[i][j]->setPixmap(VioletD);
                    break;
                case 35:
                    items[i][j]->setPixmap(VioletDL);
                    break;
                case 36:
                    items[i][j]->setPixmap(VioletL);
                    break;
                case 37:
                    items[i][j]->setPixmap(VioletTL);
                    break;
                case 40:
                    items[i][j]->setPixmap(OrangeT);
                    break;
                case 41:
                    items[i][j]->setPixmap(OrangeTR);
                    break;
                case 42:
                    items[i][j]->setPixmap(OrangeR);
                    break;
                case 43:
                    items[i][j]->setPixmap(OrangeDR);
                    break;
                case 44:
                    items[i][j]->setPixmap(OrangeD);
                    break;
                case 45:
                    items[i][j]->setPixmap(OrangeDL);
                    break;
                case 46:
                    items[i][j]->setPixmap(OrangeL);
                    break;
                case 47:
                    items[i][j]->setPixmap(OrangeTL);
                    break;
                case 50:
                    items[i][j]->setPixmap(BlueT);
                    break;
                case 51:
                    items[i][j]->setPixmap(BlueTR);
                    break;
                case 52:
                    items[i][j]->setPixmap(BlueR);
                    break;
                case 53:
                    items[i][j]->setPixmap(BlueDR);
                    break;
                case 54:
                    items[i][j]->setPixmap(BlueD);
                    break;
                case 55:
                    items[i][j]->setPixmap(BlueDL);
                    break;
                case 56:
                    items[i][j]->setPixmap(BlueL);
                    break;
                case 57:
                    items[i][j]->setPixmap(BlueTL);
                    break;
                case 60:
                    items[i][j]->setPixmap(GreenT);
                    break;
                case 61:
                    items[i][j]->setPixmap(GreenTR);
                    break;
                case 62:
                    items[i][j]->setPixmap(GreenR);
                    break;
                case 63:
                    items[i][j]->setPixmap(GreenDR);
                    break;
                case 64:
                    items[i][j]->setPixmap(GreenD);
                    break;
                case 65:
                    items[i][j]->setPixmap(GreenDL);
                    break;
                case 66:
                    items[i][j]->setPixmap(GreenL);
                    break;
                case 67:
                    items[i][j]->setPixmap(GreenTL);
                    break;
                }
          }
    }
    changed.clear();
}

void MainWindow::make_start_elements(){    
    if((number_of_live_cells+number_of_plants)>2304){
        number_of_live_cells=2304*double(number_of_live_cells)/(number_of_live_cells+number_of_plants);
        number_of_plants=2304-number_of_live_cells;
    }

    int number_empty=2304-number_of_live_cells-number_of_plants;

    int mins=1;
    if(number_of_live_cells<=number_of_plants && number_of_live_cells<=number_empty){
        if(number_of_plants<=number_empty){
            mins=1;
        }
        else{
            mins=2;
        }
    }
    else if(number_of_plants<= number_of_live_cells && number_of_plants<=number_empty){
        if(number_of_live_cells<=number_empty){
            mins=3;
        }
        else{
            mins=4;
        }
    }
    else{
        if(number_of_live_cells<=number_of_plants){
            mins=5;
        }
        else{
            mins=6;
        }
    }
    if(mins==1){
        for(int k=0;k<number_of_live_cells;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{

                Bot to_add(initial_live_cell_energy,number_of_gens_of_action,min_energy_for_division);

                if(to_add.color == 1){
                    red_counter++;
                }
                else if(to_add.color == 2){
                    yellow_counter++;
                }
                else if(to_add.color == 3){
                    violet_counter++;
                }
                else if(to_add.color == 4){
                    orange_counter++;
                }
                else if(to_add.color == 5){
                    blue_counter++;
                }
                else if(to_add.color == 6){
                    green_counter++;
                }

                to_add.posX=i;
                to_add.posY=j;
                bots.push_back(to_add);

                elements[i][j]=to_add.color*10+to_add.view;

            }
        }
        for(int k=0;k<number_of_plants;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                elements[i][j]=3;
            }
        }
        for(int i=1;i<50;i++){
            for(int j=1;j<50;j++){
                if(elements[i][j]==0){
                    elements[i][j]=1;
                }
            }
        }
    }
    else if(mins==2){
        for(int k=0;k<number_of_live_cells;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                Bot to_add(initial_live_cell_energy,number_of_gens_of_action,min_energy_for_division);

                if(to_add.color == 1){
                    red_counter++;
                }
                else if(to_add.color == 2){
                    yellow_counter++;
                }
                else if(to_add.color == 3){
                    violet_counter++;
                }
                else if(to_add.color == 4){
                    orange_counter++;
                }
                else if(to_add.color == 5){
                    blue_counter++;
                }
                else if(to_add.color == 6){
                    green_counter++;
                }

                to_add.posX=i;
                to_add.posY=j;
                bots.push_back(to_add);

                elements[i][j]=to_add.color*10+to_add.view;
            }
        }
        for(int k=0;k<number_empty;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                elements[i][j]=1;
            }
        }
        for(int i=1;i<50;i++){
            for(int j=1;j<50;j++){
                if(elements[i][j]==0){
                    elements[i][j]=3;
                }
            }
        }
    }
    else if(mins==3){
        for(int k=0;k<number_of_plants;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                elements[i][j]=3;
            }
        }
        for(int k=0;k<number_of_live_cells;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                Bot to_add(initial_live_cell_energy,number_of_gens_of_action,min_energy_for_division);

                if(to_add.color == 1){
                    red_counter++;
                }
                else if(to_add.color == 2){
                    yellow_counter++;
                }
                else if(to_add.color == 3){
                    violet_counter++;
                }
                else if(to_add.color == 4){
                    orange_counter++;
                }
                else if(to_add.color == 5){
                    blue_counter++;
                }
                else if(to_add.color == 6){
                    green_counter++;
                }

                to_add.posX=i;
                to_add.posY=j;
                bots.push_back(to_add);

                elements[i][j]=to_add.color*10+to_add.view;
            }
        }
        for(int i=1;i<50;i++){
            for(int j=1;j<50;j++){
                if(elements[i][j]==0){
                    elements[i][j]=1;
                }
            }
        }
    }
    else if(mins==4){
        for(int k=0;k<number_of_plants;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                elements[i][j]=3;
            }
        }
        for(int k=0;k<number_empty;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                elements[i][j]=1;
            }
        }
        for(int i=1;i<50;i++){
            for(int j=1;j<50;j++){
                if(elements[i][j]==0){

                    Bot to_add(initial_live_cell_energy,number_of_gens_of_action,min_energy_for_division);

                    if(to_add.color == 1){
                        red_counter++;
                    }
                    else if(to_add.color == 2){
                        yellow_counter++;
                    }
                    else if(to_add.color == 3){
                        violet_counter++;
                    }
                    else if(to_add.color == 4){
                        orange_counter++;
                    }
                    else if(to_add.color == 5){
                        blue_counter++;
                    }
                    else if(to_add.color == 6){
                        green_counter++;
                    }

                    to_add.posX=i;
                    to_add.posY=j;
                    bots.push_back(to_add);

                    elements[i][j]=to_add.color*10+to_add.view;
                }
            }
        }
    }
    else if(mins==5){
        for(int k=0;k<number_empty;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                elements[i][j]=1;
            }
        }
        for(int k=0;k<number_of_live_cells;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{

                Bot to_add(initial_live_cell_energy,number_of_gens_of_action,min_energy_for_division);

                if(to_add.color == 1){
                    red_counter++;
                }
                else if(to_add.color == 2){
                    yellow_counter++;
                }
                else if(to_add.color == 3){
                    violet_counter++;
                }
                else if(to_add.color == 4){
                    orange_counter++;
                }
                else if(to_add.color == 5){
                    blue_counter++;
                }
                else if(to_add.color == 6){
                    green_counter++;
                }

                to_add.posX=i;
                to_add.posY=j;
                bots.push_back(to_add);

                elements[i][j]=to_add.color*10+to_add.view;
            }
        }
        for(int i=1;i<50;i++){
            for(int j=1;j<50;j++){
                if(elements[i][j]==0){
                    elements[i][j]=3;
                }
            }
        }
    }
    else {
        for(int k=0;k<number_empty;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                elements[i][j]=1;
            }
        }
        for(int k=0;k<number_of_plants;k++){
            int i=1+mersenne()%49;
            int j=1+mersenne()%49;
            if(elements[i][j]!=0){
                k--;
            }
            else{
                elements[i][j]=3;
            }
        }
        for(int i=1;i<50;i++){
            for(int j=1;j<50;j++){
                if(elements[i][j]==0){

                    Bot to_add(initial_live_cell_energy,number_of_gens_of_action,min_energy_for_division);

                    if(to_add.color == 1){
                        red_counter++;
                    }
                    else if(to_add.color == 2){
                        yellow_counter++;
                    }
                    else if(to_add.color == 3){
                        violet_counter++;
                    }
                    else if(to_add.color == 4){
                        orange_counter++;
                    }
                    else if(to_add.color == 5){
                        blue_counter++;
                    }
                    else if(to_add.color == 6){
                        green_counter++;
                    }

                    to_add.posX=i;
                    to_add.posY=j;
                    bots.push_back(to_add);

                    elements[i][j]=to_add.color*10+to_add.view;
                }
            }
        }
    }
}

void MainWindow::on_play_clicked()
{
    if(is_action){
        is_action=false;
        m_timer->stop();
    }
    else{
        is_action=true;
        m_timer->start(delay);
    }
}

void MainWindow::on_Meat_energy_textChanged(const QString &arg1)
{
    bool enabled = ui->Meat_energy->hasAcceptableInput();
    ui->update->setEnabled(enabled);
    if(!enabled){
        ui->Meat_energy->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Meat_energy->setStyleSheet("color: black;  background-color: white");
    }
}

void MainWindow::on_Plants_energy_textChanged(const QString &arg1)
{
    bool enabled = ui->Plants_energy->hasAcceptableInput();
    ui->update->setEnabled(enabled);
    if(!enabled){
        ui->Plants_energy->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Plants_energy->setStyleSheet("color: black;  background-color: white");
    }
}

void MainWindow::on_Name_textChanged(const QString &arg1)
{
    bool enabled = false;
    if(ui->Name->text() != ""){
        enabled = true;
    }
    ui->update->setEnabled(enabled);
    if(!enabled){
        ui->Name->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Name->setStyleSheet("color: black;  background-color: white");
    }
}

void MainWindow::on_update_clicked()
{
    this->name = ui->Name->text();
    this->plants_energy = ui->Plants_energy->text().toInt();
    this->meat_energy = ui->Meat_energy->text().toInt();
    this->speed=ui->Speed->value();
    this->delay = (11-this->speed)*100;
    this->tree_propagation_speed=ui->Tree_propagation_speed->value();
    this->on_play_clicked();
    this->on_play_clicked();
}

void MainWindow::select(){
    bool act = is_action;
    if(act){
        on_play_clicked();
    }
        if(scene->selectedItems().size()>0){
            int x = scene->selectedItems().first()->x()/18;
            int y = scene->selectedItems().first()->y()/18;
            for(auto& i:bots){
                if(i.posX==x && i.posY==y){
                    Bot& current_bot=i;
                    botInfo info(current_bot);
                    info.setModal(true);
                    info.exec();
                    break;
                }
            }
            scene->selectedItems().clear();
        }
        if(act){
            on_play_clicked();
        }
}
