#include "worldparameters.h"
#include "ui_worldparameters.h"

WorldParameters::WorldParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorldParameters)
{
    ui->setupUi(this);

    correct=false;

    name="";
    number_of_live_cells=0;
    initial_live_cell_energy=0;
    number_of_gens_of_action=0;
    min_energy_for_division=0;
    number_of_plants=0;
    plants_energy=0;
    meat_energy=0;
    max_energy=0;

    validator1 = new QIntValidator(1,1000,this);
    ui->Number_of_live_cells->setValidator(validator1);
    ui->Initial_live_cell_energy->setValidator(validator1);
    ui->Max_live_cell_energy->setValidator(validator1);
    validator3 = new QIntValidator(2,10,this);
    ui->Number_of_gens_of_action->setValidator(validator3);
    validator4 = new QIntValidator(1,600,this);
    ui->Min_energy_for_division->setValidator(validator4);
    ui->Number_of_plants->setValidator(validator1);
    validator6 = new QIntValidator(1,200,this);
    ui->Plants_energy->setValidator(validator6);
    validator7 = new QIntValidator(1,300,this);
    ui->Meat_energy->setValidator(validator7);
}

WorldParameters::~WorldParameters()
{
    delete validator1;
    delete validator3;
    delete validator4;
    delete validator6;
    delete validator7;
    delete ui;
}

void WorldParameters::on_Number_of_live_cells_textChanged(const QString &arg1)
{
    bool enabled = ui->Number_of_live_cells->hasAcceptableInput();
    ui->Start->setEnabled(enabled);
    if(!enabled){
        ui->Number_of_live_cells->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Number_of_live_cells->setStyleSheet("color: black;  background-color: white");
    }
}

void WorldParameters::on_Initial_live_cell_energy_textChanged(const QString &arg1)
{
    bool enabled = ui->Initial_live_cell_energy->hasAcceptableInput();
    ui->Start->setEnabled(enabled);
    if(!enabled){
        ui->Initial_live_cell_energy->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Initial_live_cell_energy->setStyleSheet("color: black;  background-color: white");
    }
}

void WorldParameters::on_Max_live_cell_energy_textChanged(const QString &arg1)
{
    bool enabled = ui->Max_live_cell_energy->hasAcceptableInput();
    ui->Start->setEnabled(enabled);
    if(!enabled){
        ui->Max_live_cell_energy->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Max_live_cell_energy->setStyleSheet("color: black;  background-color: white");
    }
}

void WorldParameters::on_Number_of_gens_of_action_textChanged(const QString &arg1)
{
    bool enabled = ui->Number_of_gens_of_action->hasAcceptableInput();
    ui->Start->setEnabled(enabled);
    if(!enabled){
        ui->Number_of_gens_of_action->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Number_of_gens_of_action->setStyleSheet("color: black;  background-color: white");
    }
}

void WorldParameters::on_Min_energy_for_division_textChanged(const QString &arg1)
{
    bool enabled = ui->Min_energy_for_division->hasAcceptableInput();
    ui->Start->setEnabled(enabled);
    if(!enabled){
        ui->Min_energy_for_division->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Min_energy_for_division->setStyleSheet("color: black;  background-color: white");
    }
}

void WorldParameters::on_Number_of_plants_textChanged(const QString &arg1)
{
    bool enabled = ui->Number_of_plants->hasAcceptableInput();
    ui->Start->setEnabled(enabled);
    if(!enabled){
        ui->Number_of_plants->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Number_of_plants->setStyleSheet("color: black;  background-color: white");
    }
}

void WorldParameters::on_Plants_energy_textChanged(const QString &arg1)
{
    bool enabled = ui->Plants_energy->hasAcceptableInput();
    ui->Start->setEnabled(enabled);
    if(!enabled){
        ui->Plants_energy->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Plants_energy->setStyleSheet("color: black;  background-color: white");
    }
}

void WorldParameters::on_Meat_energy_textChanged(const QString &arg1)
{
    bool enabled = ui->Meat_energy->hasAcceptableInput();
    ui->Start->setEnabled(enabled);
    if(!enabled){
        ui->Meat_energy->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Meat_energy->setStyleSheet("color: black;  background-color: white");
    }
}

void WorldParameters::on_Start_clicked()
{
    this->correct=true;

    this->name=ui->Name->text();
    this->number_of_live_cells=ui->Number_of_live_cells->text().toInt();
    this->initial_live_cell_energy=ui->Initial_live_cell_energy->text().toInt();
    this->number_of_gens_of_action=ui->Number_of_gens_of_action->text().toInt();
    this->min_energy_for_division=ui->Min_energy_for_division->text().toInt();
    this->number_of_plants=ui->Number_of_plants->text().toInt();
    this->plants_energy=ui->Plants_energy->text().toInt();
    this->meat_energy=ui->Meat_energy->text().toInt();
    this->speed=ui->Speed->value();
    this->tree_propagation_speed=ui->Tree_propagation_speed->value();
    this->max_energy=ui->Max_live_cell_energy->text().toInt();
    this->close();
}

void WorldParameters::on_Name_textChanged(const QString &arg1)
{
    bool enabled = false;
    if(ui->Name->text() != ""){
        enabled = true;
    }
    ui->Start->setEnabled(enabled);
    if(!enabled){
        ui->Name->setStyleSheet("color: white;  background-color: red");
    }
    else{
        ui->Name->setStyleSheet("color: black;  background-color: white");
    }
}
