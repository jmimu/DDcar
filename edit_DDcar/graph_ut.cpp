#include "graph_ut.h"
#include <iostream>


Graph_Ut::Graph_Ut()
{
    m_traj_img=new QPixmap();
    bool img_ok=m_traj_img->load("star.png");
    if (!img_ok)
        std::cout<<"Pb reading image star.png"<<std::endl;
    else
        std::cout<<"OK reading image star.png"<<std::endl;
}

Graph_Ut::~Graph_Ut()
{
    delete m_traj_img;
    delete m_track_img;
}

bool Graph_Ut::load_background(std::string backgound_filename)
{
    m_track_img=new QPixmap();
    bool img_ok=m_track_img->load(backgound_filename.c_str());
    if (!img_ok)
        std::cout<<"Pb reading image"<<std::endl;
    else
    {
        std::cout<<"OK reading image"<<std::endl;

        m_track_item=this->addPixmap(*m_track_img);
        m_track_item->setZValue(-10);
        /*m_track_item->setScale(0.05);
        m_track_item->setPos(15,7);
        m_track_item->setRotation(10);*/
    }

    return img_ok;
}

void Graph_Ut::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    std::cout<<"Mouse : "<<mouseEvent->scenePos().x()<<" "<<mouseEvent->scenePos().y()<<std::endl;

    double x=mouseEvent->scenePos().x();
    double y=mouseEvent->scenePos().y();

    m_traj_items.push_back(new Traj_El(x, y, this, m_traj_img ));

    if (m_traj_items.size()>1)
    {
        float x1=m_traj_items.at(m_traj_items.size()-2)->pos_x();
        float y1=m_traj_items.at(m_traj_items.size()-2)->pos_y();
        float x2=m_traj_items.at(m_traj_items.size()-1)->pos_x();
        float y2=m_traj_items.at(m_traj_items.size()-1)->pos_y();
        QGraphicsLineItem *traj_line_item=this->addLine(x1,y1,x2,y2,QPen(QBrush(Qt::darkYellow),10));
        traj_line_item->setZValue(1);
        m_traj_line_items.push_back(traj_line_item);
    }


}
