#include "traj_el.h"

Traj_El::Traj_El(double x, double y, QGraphicsScene* scene, QPixmap* traj_img)
    : m_x(x), m_y(y)
{
    m_item=scene->addPixmap(* traj_img);
    m_item->setPos(m_x-traj_img->width()/2, m_y-traj_img->height()/2);
    m_item->setZValue(0);
}

double Traj_El::pos_x()
{
    return m_x;
}

double Traj_El::pos_y()
{
    return m_y;
}
