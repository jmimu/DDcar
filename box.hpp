#ifndef BOX_H
#define BOX_H

#include <Box2D.h>
#include <SFML/Graphics.hpp>

#define PIXEL_PER_UNIT 10

/**
 * PIXEL_PER_UNIT px = 1 box2d unit ! 
 * */


class Box
{
public:
  Box(b2World &world,float _x,float _y,float _w,float _h,float _angle,sf::Color _c,sf::Image *_image=NULL,float _density=1.0,bool _sensor=false,float _friction=0.3,float _linearDamping=0.0,float _angularDamping=0.0);
  
  ~Box();
  void aff(sf::RenderWindow *_App);
  sf::Shape rect;
  sf::Color coul;
  b2BodyDef *bodyDef;
  b2Body* body;
  sf::Image * image;
  sf::Sprite sprite;
  
private:
  double m_w;
  double m_h;
};


#endif
