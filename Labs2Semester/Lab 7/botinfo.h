#ifndef BOTINFO_H
#define BOTINFO_H

#include <QDialog>

#include "ui_botinfo.h"

#include <QTableWidgetItem>
#include "Bots.h"

namespace Ui {
class botInfo;
}

class botInfo : public QDialog
{
    Q_OBJECT

public:
    explicit botInfo(Bot& bot, QWidget *parent = nullptr);
    ~botInfo();

private slots:


    void on_Gens_action_table_itemClicked(QTableWidgetItem *item);

    void on_Gens_irritation_table_itemClicked(QTableWidgetItem *item);

private:
    Ui::botInfo *ui;

    Bot* B;
};

#endif // BOTINFO_H
