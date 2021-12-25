#ifndef WORLDPARAMETERS_H
#define WORLDPARAMETERS_H

#include <QDialog>
#include <QValidator>
#include <QString>

namespace Ui {
class WorldParameters;
}

class WorldParameters : public QDialog
{
    Q_OBJECT

public:
    explicit WorldParameters(QWidget *parent = nullptr);
    ~WorldParameters();


    bool correct;


    QString name;
    int number_of_live_cells;
    int initial_live_cell_energy;
    int number_of_gens_of_action;
    int min_energy_for_division;
    int number_of_plants;
    int plants_energy;
    int meat_energy;
    int tree_propagation_speed;
    int speed;
    int max_energy;

    QIntValidator *validator1;
    QIntValidator *validator3;
    QIntValidator *validator4;
    QIntValidator *validator6;
    QIntValidator *validator7;

private slots:
    void on_Number_of_live_cells_textChanged(const QString &arg1);

    void on_Initial_live_cell_energy_textChanged(const QString &arg1);

    void on_Max_live_cell_energy_textChanged(const QString &arg1);

    void on_Number_of_gens_of_action_textChanged(const QString &arg1);

    void on_Min_energy_for_division_textChanged(const QString &arg1);

    void on_Number_of_plants_textChanged(const QString &arg1);

    void on_Plants_energy_textChanged(const QString &arg1);

    void on_Meat_energy_textChanged(const QString &arg1);

    void on_Start_clicked();

    void on_Name_textChanged(const QString &arg1);

private:
    Ui::WorldParameters *ui;
};

#endif // WORLDPARAMETERS_H
