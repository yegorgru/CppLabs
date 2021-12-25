/**
\file
\brief .h file with definition of MainWindow class
*/

#pragma once

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QSound>

#include <map>

#include "philisophersrunner.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
\brief class definition of MainWindow
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
    \brief MainWindow ctor

    \param parent parent QObject of MainWindow2
    */
    MainWindow(QWidget *parent = nullptr);

    /**
    \brief MainWindow вtor
    */
    ~MainWindow();

private slots:

    /**
    \brief slot for philosophers playing

    \note invoked after run button clicked
    */
    void on_run_button_clicked();

private:

    void PlayChanges();

    void updateScene();

    Ui::MainWindow *ui;

    QTimer *m_Timer;
    QTimer *m_SingleShotTimer;

    QPixmap m_TablePixmap;
    QPixmap m_ForkPixmap;
    QPixmap m_PhilosopherPixmap;
    QPixmap m_PhilosopherEatPixmap;
    QPixmap m_PhilosopherSpeakPixmap;
    QPixmap m_PhilosopherWaitPixmap;

    QGraphicsScene* m_Scene;
    std::vector<QGraphicsPixmapItem*>m_Items;

    QGraphicsPixmapItem* m_TableItem;

    PhilosophersRunner m_Runner;

    size_t m_CurPos;
    std::vector<std::pair<int, PhilosophersRunner::TYPE>>m_Changes;
    std::map<int, PhilosophersRunner::TYPE>m_States;
};
