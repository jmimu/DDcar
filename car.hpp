#ifndef CAR_H
#define CAR_H

#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include <deque>

#include "box.hpp"


struct Car_contact
{
  b2Vec2 point;
  float normal;
  float tangent;
};


class Track;

class Car
{
public:
  Car(b2World &world,float x,float y,std::string image_name);
  ~Car();
  void update(sf::Color ground_FR,sf::Color ground_FL,sf::Color ground_RR,sf::Color ground_RL/*,std::deque <b2Vec2> * tire_marks*/,Track * track);
  void aff(sf::RenderWindow *_App,bool infos=false);
  double get_x(){return x;}
  double get_y(){return y;}
  double get_h(){return h;}
  double get_w(){return w;}
  double get_speed();
  double get_tangent_speed();
  
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
  
  unsigned int index_trajectory_point_target;//index of the point to go to in track->trajectory
  unsigned int next_checkpoint_index;
  long new_lap(){last_lap_time=lap_time;lap_time=0;nbr_laps++;return (last_lap_time);}
  
  //vector of all the contacts (to the main body) for last time step
  std::vector<Car_contact> contact_list;
  
  void set_pos(b2Vec2 pos,float _a){main_body.bodyDef->position=pos;main_body.bodyDef->angle=_a;}
private:
  bool killOrthogonalVelocity(b2Body* targetBody,float threshold);
  double x,y,h,w;

  sf::Shape rect;  

		
  Box main_body;
  Box head;
  Box frontR_wheel;
  Box frontL_wheel;
  Box rearR_wheel;
  Box rearL_wheel;
  
  b2RevoluteJoint* frontRJoint;
  b2RevoluteJoint* frontLJoint;


  //images
  static sf::Image wheel_image;
  static sf::Image head_image;
  static std::map<std::string,sf::Image> main_images;
  static std::vector<sf::Image*> animation_feet;
  static std::vector<sf::Image*> animation_arm;
  static bool images_loaded;
  static bool load_images();
  sf::Image * get_image(std::string image_name); // load the new image if not present in main_images

  float current_image;

//IA
  int nbr_frames_without_tangent_speed;
  bool going_backward;//until next traj point, go backward (to come back from a dead-end)
public:
  void follow(std::vector<b2Vec2> * trajectory);
  void follow(float t_x,float t_y);

  static sf::Image boom_image;

//laps & co.
public:
  long lap_time;//nb of frames
  long last_lap_time;
  long nbr_laps;

  //to order cars
  long nbr_checkpoints;
  long time_last_checkpoint_in_lap;
  
  int rank;
  long damage;
};

bool cmp_Cars( Car *a, Car *b );


#endif
