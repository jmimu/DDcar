#ifndef GRAPH_UT_H
#define GRAPH_UT_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <string>

#include "traj_el.h"

class Graph_Ut: public QGraphicsScene
{
public:
    Graph_Ut();
    ~Graph_Ut();
    bool load_background(std::string backgound_filename);
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
protected:
    QPixmap *m_track_img;
    QGraphicsItem * m_track_item;

    QPixmap *m_traj_img;
    std::vector<Traj_El *> m_traj_items;
    std::vector<QGraphicsLineItem *> m_traj_line_items;
};

#endif // GRAPH_UT_H
