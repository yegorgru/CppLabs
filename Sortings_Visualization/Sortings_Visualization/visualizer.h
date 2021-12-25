/**
\file
\brief .h file with definition of Visualizer class
*/

#pragma once

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QLineEdit>

#include <vector>
#include <optional>

#include "Sorting.h"

/**
\brief template class-implementation of sorting proxy

\note inheritant of QObject and Sortins::DefaultVisualizer<uint32_t>
*/
class Visualizer : public QObject, public Sortings::DefaultVisualizer<std::vector<uint32_t>>
{
    Q_OBJECT

public:

    /**
    \brief Visualizer ctor

    \param data reference to std::vector of sorted data
    */
    Visualizer(std::vector<uint32_t>& data);

    /**
    \brief overrided method of DefaultVisualizer
    */
    bool Visualize(Sortings::Operation operation, std::vector<uint32_t>::iterator first, std::optional<std::vector<uint32_t>::iterator> second = std::nullopt) override;

    /**
    \brief forms new items that depends on sorted data

    \param size current size of graphics view
    */
    void FormScene(const QSize& size);

    /**
    \brief updates scene after window resizing

    \param widthCoef new width / old width of graphics view
    \param heightCoef new height / old height of graphics view
    */
    void UpdateScene(double widthCoef, double heightCoef);

    /**
    \brief sets new max item (number)

    \param value new max item
    */
    void SetMaxValue(uint32_t value);

    /**
    \brief sets line edit for counting comparisons

    \param item point on line edit of comparisons
    */
    void SetComparisonsItem(QLineEdit* item);

    /**
    \brief sets line edit for counting changes

    \param item point on line edit of changes
    */
    void SetChangesItem(QLineEdit* item);

    /**
    \brief sets line edit for counting accesses

    \param item point on line edit of accesses
    */
    void SetAccessesItem(QLineEdit* item);

    /**
    \brief starts visualization

    \param speedOfVisualization speed of visualization
    */
    void Play(int speedOfVisualization);

    /**
    \brief plays single item of visualization
    */
    void PlayItem();

    /**
    \brief clears queue of visualization
    */
    void ClearQueue();

    /**
    \brief pause or continue of visualization
    */
    void PauseOrContinue();

    /**
    \brief clears graphics view and items
    */
    void Clear();

    /**
    \brief graphics scene getter

    \return scene
    */
    QGraphicsScene* GetScene();

    /**
    \brief timer getter

    \return timer
    */
    QTimer* GetTimer();

signals:

    /**
    \brief signal emited after last item of visualization played
    */
    void Sorted();
private:
    struct VisualizeItem{
        Sortings::Operation operation;
        size_t first;
        size_t second;
        double firstHeightCoef;
        double secondHeightCoef;
    };

    QGraphicsScene* m_Scene;
    std::vector<QGraphicsRectItem*>m_Rects;
    std::vector<uint32_t>&m_Data;
    uint32_t m_MaxValue;
    double m_Width;
    size_t m_CurPos;

    bool m_CanRun;

    std::vector<VisualizeItem>m_VisualizeQueue;
    QTimer *m_Timer;

    QLineEdit* m_Comparisons;
    QLineEdit* m_Changes;
    QLineEdit* m_Accesses;
};
