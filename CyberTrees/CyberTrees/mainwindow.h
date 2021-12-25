#pragma once

#include <QMainWindow>
#include <QResizeEvent>

#include "visualizer.h"
#include "logic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void resizeEvent(QResizeEvent* event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pause_clicked();

    void on_delay_sliderMoved(int position);

    void on_activePart_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    Logic m_Logic;
    Visualizer m_Visualizer;
    bool m_Initiated;
};
