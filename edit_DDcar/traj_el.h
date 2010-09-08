#ifndef TRAJ_EL_H
#define TRAJ_EL_H

#include <QGraphicsScene>
#include <QGraphicsItem>

class Traj_El
{
public:
    Traj_El(double x, double y, QGraphicsScene* scene, QPixmap* traj_img);
    double pos_x();
    double pos_y();
protected:
    QGraphicsItem* m_item;
    double m_x, m_y;
};

#endif // TRAJ_EL_H
