#ifndef CHOOSE_GEN_H
#define CHOOSE_GEN_H


#include <QGraphicsPixmapItem>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTableWidgetItem>
#include "Bots.h"

namespace Ui {
class choose_gen;
}

class choose_gen : public QDialog
{
    Q_OBJECT

public:
    explicit choose_gen(int& v, QTableWidgetItem *item, QWidget *parent = nullptr);
    ~choose_gen();

private:
    Ui::choose_gen *ui;


    QGraphicsPixmapItem* items[10];
    QGraphicsScene *scene;

    int* value;
    QTableWidgetItem *it;
private slots:
    void select();
};

#endif // CHOOSE_GEN_H
