#pragma once

#include <array>

#include <QGraphicsView>
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QColor>
#include <QPixmap>

#include "logic.h"

class Visualizer : public QObject
{
    Q_OBJECT

public:
    Visualizer(Logic& logic);

    void UpdateScene(double widthCoef, double heightCoef);

    QGraphicsScene* GetScene() const;

    void Play();

    void StartWorld(int delay, QSize size, int activePart);

    QTimer* GetTimer() const;

    void SetActivePart(int value);

private:
    Logic& m_Logic;
    QGraphicsScene* m_Scene;
    QTimer *m_Timer;
    QImage m_Image;
    QGraphicsPixmapItem* m_Item;
    int m_ActivePart;
};
