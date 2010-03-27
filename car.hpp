#ifndef CAR_H
#define CAR_H

#include <Box2D.h>
#include <SFML/Graphics.hpp>

#include "box.hpp"


class Car
{
public:
  Car(b2World &world,float x,float y,sf::Image *car_image=NULL,sf::Image *wheel_image=NULL);
  ~Car();
  void update();
  void aff(sf::RenderWindow *_App);
  double get_x(){return x;}
  double get_y(){return y;}
  double get_speed();
  
  
  double MAX_STEER_ANGLE;
  double STEER_SPEED;
  double SIDEWAYS_FRICTION_FORCE;
  double HORSEPOWERS;
  double engineSpeed;
  double steeringAngle;
  
private:
  void killOrthogonalVelocity(b2Body* targetBody);
  double x,y;

  sf::Shape rect;  

		
  Box main_body;
  Box frontR_wheel;
  Box frontL_wheel;
  Box rearR_wheel;
  Box rearL_wheel;
  
  b2RevoluteJoint* frontRJoint;
  b2RevoluteJoint* frontLJoint;


};


#endif
