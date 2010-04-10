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
  void update(sf::Color ground_FR,sf::Color ground_FL,sf::Color ground_RR,sf::Color ground_RL);
  void aff(sf::RenderWindow *_App,bool infos=false);
  double get_x(){return x;}
  double get_y(){return y;}
  double get_h(){return h;}
  double get_w(){return w;}
  double get_speed();
  void follow(float t_x,float t_y);
  
  double MAX_STEER_ANGLE;
  double STEER_SPEED;
  double SIDEWAYS_FRICTION_FORCE;
  double HORSEPOWERS;
  double engineSpeed;
  double steeringAngle;
  
  Box* get_main_body(){return &main_body;}
  Box* get_frontR_wheel(){return &frontR_wheel;}
  Box* get_frontL_wheel(){return &frontL_wheel;}
  Box* get_rearR_wheel(){return &rearR_wheel;}
  Box* get_rearL_wheel(){return &rearL_wheel;}
  
  int index_trajectory_point_target;//index of the point to go to in track->trajectory
  int next_checkpoint_index;
  long new_lap(){last_lap_time=lap_time;lap_time=0;return (last_lap_time);}
  
  //map of all the contacts (to the main body)
  std::map<int, b2ContactPoint *> contact_list;
private:
  void killOrthogonalVelocity(b2Body* targetBody);
  double x,y,h,w;

  sf::Shape rect;  

		
  Box main_body;
  Box frontR_wheel;
  Box frontL_wheel;
  Box rearR_wheel;
  Box rearL_wheel;
  
  b2RevoluteJoint* frontRJoint;
  b2RevoluteJoint* frontLJoint;
  
public:
  long last_lap_time;
  long lap_time;//nb of frames

  //to order cars
  long nbr_checkpoints;
  long time_last_checkpoint_in_lap;
  
  int rank;
};

bool cmp_Cars( Car *a, Car *b );


#endif
