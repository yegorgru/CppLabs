#include "visualizer.h"
#include "profile.h"

#include <QHeaderView>

Visualizer::Visualizer(Logic& logic):
    m_Logic(logic),
    m_Scene(new QGraphicsScene),
    m_Timer(new QTimer()),
    m_Image{static_cast<int>(m_Scene->width()), static_cast<int>(m_Scene->height()), QImage::Format_ARGB32_Premultiplied},
    m_Item(new QGraphicsPixmapItem),
    m_ActivePart(0)
{
    connect (m_Timer,&QTimer::timeout,this,&Visualizer::Play);
    m_Image.fill(Qt::black);
    m_Item->setPos(0,0);
    m_Scene->addItem(m_Item);
}

void Visualizer::StartWorld(int delay, QSize size, int activePart){
    m_ActivePart = activePart;
    m_Scene->setSceneRect(0,0,size.width()*0.95, size.height()*0.95);
    m_Image = QImage{static_cast<int>(m_Scene->width()), static_cast<int>(m_Scene->height()), QImage::Format_ARGB32_Premultiplied};
    QPainter painter(&m_Image);
    double itemWidth = m_Scene->width()/200;
    double itemHeight = m_Scene->height()/100;
    m_Logic.Start();
    for(auto& change : m_Logic.GetChanged()){
        if(change.first.x/200 != m_ActivePart) continue;
        QColor c;
        switch(change.second){
        case Logic::Item::Type::NONE : {
            c=Qt::black;
            break;
        }
        case Logic::Item::Type::SEED : {
            c=Qt::yellow;
            break;
        }
        case Logic::Item::Type::SPROUT : {
            c=Qt::white;
            break;
        }
        case Logic::Item::Type::WOOD : {
            c=Qt::green;
            break;
        }
        }
        painter.setBrush(c);
        painter.setPen(c);
        painter.drawRect(itemWidth*(change.first.x%200), itemHeight*change.first.y, itemWidth, itemHeight);
    }
    m_Item->setPixmap(QPixmap::fromImage(m_Image));
    m_Scene->update();
    m_Timer->start(delay);
}

void Visualizer::Play(){
    double itemWidth = m_Scene->width()/200;
    double itemHeight = m_Scene->height()/100;
    m_Logic.Play();
    QPainter painter(&m_Image);
    for(auto& change : m_Logic.GetChanged()){
        if(change.first.x/200 != m_ActivePart) continue;
        QColor c;
        switch(change.second){
        case Logic::Item::Type::NONE : {
            c=Qt::black;
            break;
        }
        case Logic::Item::Type::SEED : {
            c=Qt::yellow;
            break;
        }
        case Logic::Item::Type::SPROUT : {
            c=Qt::white;
            break;
        }
        case Logic::Item::Type::WOOD : {
            c=Qt::green;
            break;
        }
        }
        painter.setBrush(c);
        painter.setPen(c);
        painter.drawRect(itemWidth*(change.first.x%200), itemHeight*change.first.y, itemWidth, itemHeight);
    }
    m_Item->setPixmap(QPixmap::fromImage(m_Image));
    m_Scene->update();

}

void Visualizer::UpdateScene(double widthCoef, double heightCoef)
{
    auto oldSceneRect = m_Scene->sceneRect();
    m_Scene->setSceneRect (0,0,widthCoef*oldSceneRect.width(), heightCoef*oldSceneRect.height());
    m_Image = m_Image.scaled(static_cast<int>(m_Scene->width()), static_cast<int>(m_Scene->height()), Qt::KeepAspectRatio);
    m_Scene->update();
}

QGraphicsScene* Visualizer::GetScene() const
{
    return m_Scene;
}

QTimer* Visualizer::GetTimer() const
{
    return m_Timer;
}

void Visualizer::SetActivePart(int value)
{
    m_ActivePart = value;
    double itemWidth = m_Scene->width()/200;
    double itemHeight = m_Scene->height()/100;
    const auto& items = m_Logic.GetItems();
    QPainter painter(&m_Image);
    for(int i = m_ActivePart*200; i < 200*(m_ActivePart+1);i++){
        for(int j=0;j<100;j++){
            QColor c;
            switch(items[i][j]->GetType()){
            case Logic::Item::Type::NONE : {
                c=Qt::black;
                break;
            }
            case Logic::Item::Type::SEED : {
                c=Qt::yellow;
                break;
            }
            case Logic::Item::Type::SPROUT : {
                c=Qt::white;
                break;
            }
            case Logic::Item::Type::WOOD : {
                c=Qt::green;
                break;
            }
            }
            painter.setBrush(c);
            painter.setPen(c);
            painter.drawRect(itemWidth*(i%200), itemHeight*j, itemWidth, itemHeight);
        }
    }
}
