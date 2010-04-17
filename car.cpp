#include "car.hpp"

#include <iostream>
#include <sstream>
#include "track.hpp"

Car::Car(b2World &world,float _x,float _y,sf::Image *car_image,sf::Image *wheel_image,sf::Image *_boom_image)
  : main_body(world,x,y,8,16,0.0,sf::Color::Red, car_image,0.2*4,false,0.3*0,0.2*0,1.0),
    frontR_wheel(world,x+3,y-5,2,4,0.0,sf::Color::Green,wheel_image,0.2,true),
    frontL_wheel(world,x-3,y-5,2,4,0.0,sf::Color::Green,wheel_image,0.2,true),
    rearR_wheel(world,x+3,y+5,2,4,0.0,sf::Color::Green,wheel_image,0.2,true),
    rearL_wheel(world,x-3,y+5,2,4,0.0,sf::Color::Green,wheel_image,0.2,true),
    x(_x),y(_y),index_trajectory_point_target(0),next_checkpoint_index(0),h(16),w(8),lap_time(0),last_lap_time(0),
    nbr_checkpoints(0),time_last_checkpoint_in_lap(0),rank(0),boom_image(_boom_image),damage(0)
{
	MAX_STEER_ANGLE = 0.3;
	STEER_SPEED = 1.5*4;
	SIDEWAYS_FRICTION_FORCE = 10;
	HORSEPOWERS = 1000*1.8;
	engineSpeed =0;
	steeringAngle = 0;
	
	//joints
	b2RevoluteJointDef frontJointDef;
	frontJointDef.Initialize(main_body.body, frontR_wheel.body, frontR_wheel.body->GetWorldCenter());
	frontJointDef.enableMotor = true;
	frontJointDef.maxMotorTorque = 100;
	frontRJoint = (b2RevoluteJoint*) world.CreateJoint(&frontJointDef);

	frontJointDef.Initialize(main_body.body, frontL_wheel.body, frontL_wheel.body->GetWorldCenter());
	frontJointDef.enableMotor = true;
	frontJointDef.maxMotorTorque = 100;
	frontLJoint = (b2RevoluteJoint*) world.CreateJoint(&frontJointDef);

	b2PrismaticJointDef rearRJointDef;
	b2Vec2 worldAxis(1.0f, 0.0f);
	rearRJointDef.Initialize(main_body.body, rearR_wheel.body, rearR_wheel.body->GetWorldCenter(), worldAxis);
	rearRJointDef.enableLimit = true;
	rearRJointDef.lowerTranslation = 0.0;
	rearRJointDef.upperTranslation = 0.0;
	world.CreateJoint(&rearRJointDef);

	b2PrismaticJointDef rearLJointDef;
	rearLJointDef.Initialize(main_body.body, rearL_wheel.body, rearL_wheel.body->GetWorldCenter(), worldAxis);
	rearLJointDef.enableLimit = true;
	rearLJointDef.lowerTranslation = 0.0;
	rearLJointDef.upperTranslation = 0.0;
	world.CreateJoint(&rearLJointDef);

	//link between main_body.body and the car
	main_body.body->SetUserData( (void *)this );
}


Car::~Car()
{
	//delete body;
}


//return true if wheel skids (more than threshold)
bool Car::killOrthogonalVelocity(b2Body* targetBody,float threshold)
{
  bool skids=false;

  b2Vec2 localPoint(0,0);
  b2Vec2 velocity = targetBody->GetLinearVelocityFromLocalPoint(localPoint);
  b2Vec2 sidewaysAxis = targetBody->GetXForm().R.col2;

  b2Vec2 otherAxis = targetBody->GetXForm().R.col1;

  //std::cout<<b2Dot(velocity,otherAxis)<<std::endl;

  if ( fabs(b2Dot(velocity,otherAxis)) > threshold) skids=true;

  sidewaysAxis*=(b2Dot(velocity,sidewaysAxis));
  //print sidewaysAxis,"\n"
  targetBody->SetLinearVelocity(sidewaysAxis);//targetBody.GetWorldPoint(localPoint));

  return skids;
}


void Car::follow(float t_x,float t_y) //AI
{
	b2Vec2 car_to_target;
	car_to_target.x=t_x-main_body.body->GetPosition().x;
	car_to_target.y=t_y-main_body.body->GetPosition().y;
	
	float dist_to_target=sqrt(car_to_target.x*car_to_target.x+car_to_target.y*car_to_target.y);
	
	if (dist_to_target<30)
	{
		index_trajectory_point_target++;
		return;
	}
	
	
	b2Vec2 orientation = main_body.body->GetXForm().R.col2;
	//std::cout<<"car_to_target ("<<car_to_target.x<<","<<car_to_target.y<<") orientation ("<<orientation.x<<","<<orientation.y<<")"<<std::endl;
	
	b2Vec2 car_to_target_colin=orientation;
	car_to_target_colin*=(b2Dot(orientation,car_to_target));//colinear part
	b2Vec2 car_to_target_normal;//normal part
	car_to_target_normal.x=car_to_target.x-car_to_target_colin.x;
	car_to_target_normal.y=car_to_target.y-car_to_target_colin.y;
	//std::cout<<"car_to_target_colin  ("<<car_to_target_colin.x<<","<<car_to_target_colin.y<<")"<<std::endl;
	//std::cout<<"car_to_target_normal ("<<car_to_target_normal.x<<","<<car_to_target_normal.y<<")"<<std::endl;
	
	float dist_normal=sqrt(car_to_target_normal.x*car_to_target_normal.x+car_to_target_normal.y*car_to_target_normal.y);
	
	if (dist_to_target>10)
	{
		if (b2Dot(orientation,car_to_target)>0)
		{
			engineSpeed = -HORSEPOWERS;
			steeringAngle = -MAX_STEER_ANGLE;
			return;
		}else{
			engineSpeed = -HORSEPOWERS;
		}
	}else{
		engineSpeed=0;
		//point reached => next trajectory point
		index_trajectory_point_target++;
		
	}
	if (dist_normal>10)
	{
		if (car_to_target_normal.x*car_to_target_colin.y-car_to_target_colin.x*car_to_target_normal.y>0)
			steeringAngle = -MAX_STEER_ANGLE;
		else
			steeringAngle = MAX_STEER_ANGLE;
	}else 
		steeringAngle = 0;
	
}

double Car::get_speed()
{
	b2Vec2 localPoint(0,0);
	b2Vec2 velocity = main_body.body->GetLinearVelocityFromLocalPoint(localPoint);
	return sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
}

void Car::update(sf::Color ground_FR,sf::Color ground_FL,sf::Color ground_RR,sf::Color ground_RL/*,std::deque <b2Vec2> * tire_marks*/,Track * track)
{
  //treat contacts !
  for (unsigned int i=0;i<contact_list.size();i++)
  {
	damage+=contact_list.at(i)->normalImpulse/100;
    /*std::cout<<"=== "<<contact_list.at(i)->normalImpulse
	   <<" "<<contact_list.at(i)->tangentImpulse
	   <<" "<<contact_list.at(i)->shape1->GetBody()->GetUserData()
	   <<" "<<contact_list.at(i)->shape2->GetBody()->GetUserData()
	   <<" "<<contact_list.at(i)->position.x<<","<<contact_list.at(i)->position.y
	   <<" "<<contact_list.at(i)->normal.x<<","<<contact_list.at(i)->normal.y
	   <<" "<<std::endl;*/
	   }

  //contacts treated (contact_list is cleared in aff())


	float frontR_wheel_linearDamping=(255-ground_FR.r)/255.0;
	float frontL_wheel_linearDamping=(255-ground_FL.r)/255.0;
	float rearR_wheel_linearDamping= (255-ground_RR.r)/255.0;
	float rearL_wheel_linearDamping= (255-ground_RL.r)/255.0;
	
	b2Vec2 frontR_wheel_velocity=frontR_wheel.body->GetLinearVelocity();
	frontR_wheel_velocity.x-=frontR_wheel_velocity.x*frontR_wheel_linearDamping;
	frontR_wheel_velocity.y-=frontR_wheel_velocity.y*frontR_wheel_linearDamping;
	frontR_wheel.body->SetLinearVelocity(frontR_wheel_velocity);
	
	b2Vec2 frontL_wheel_velocity=frontL_wheel.body->GetLinearVelocity();
	frontL_wheel_velocity.x-=frontL_wheel_velocity.x*frontL_wheel_linearDamping;
	frontL_wheel_velocity.y-=frontL_wheel_velocity.y*frontL_wheel_linearDamping;
	frontL_wheel.body->SetLinearVelocity(frontL_wheel_velocity);
	
	b2Vec2 rearR_wheel_velocity=rearR_wheel.body->GetLinearVelocity();
	rearR_wheel_velocity.x-=rearR_wheel_velocity.x*rearR_wheel_linearDamping;
	rearR_wheel_velocity.y-=rearR_wheel_velocity.y*rearR_wheel_linearDamping;
	rearR_wheel.body->SetLinearVelocity(rearR_wheel_velocity);
	
	b2Vec2 rearL_wheel_velocity=rearL_wheel.body->GetLinearVelocity();
	rearL_wheel_velocity.x-=rearL_wheel_velocity.x*rearL_wheel_linearDamping;
	rearL_wheel_velocity.y-=rearL_wheel_velocity.y*rearL_wheel_linearDamping;
	rearL_wheel.body->SetLinearVelocity(rearL_wheel_velocity);
	
	
	if (killOrthogonalVelocity(frontR_wheel.body,15))
	  {
	    //add a tire mark
		sf::Color coul(0,0,0,255);
	    track->add_pixel(frontR_wheel.body->GetPosition().x,frontR_wheel.body->GetPosition().y,coul);
/*	    tire_marks->push_back(frontR_wheel.body->GetPosition());
	    if (tire_marks->size()>MAX_TIRE_MARKS)
	      tire_marks->pop_front();*/
	  }
	if (killOrthogonalVelocity(frontL_wheel.body,15))
	  {
	    //add a tire mark
		sf::Color coul(0,0,0,255);
	    track->add_pixel(frontL_wheel.body->GetPosition().x,frontL_wheel.body->GetPosition().y,coul);
/*	    tire_marks->push_back(frontL_wheel.body->GetPosition());
	    if (tire_marks->size()>MAX_TIRE_MARKS)
	      tire_marks->pop_front();*/
	  }
	if (killOrthogonalVelocity(rearR_wheel.body,15))
	  {
	    //add a tire mark
		sf::Color coul(0,0,0,255);
	    track->add_pixel(rearR_wheel.body->GetPosition().x,rearR_wheel.body->GetPosition().y,coul);
/*	    tire_marks->push_back(rearR_wheel.body->GetPosition());
	    if (tire_marks->size()>MAX_TIRE_MARKS)
	      tire_marks->pop_front();*/
	  }
	if (killOrthogonalVelocity(rearL_wheel.body,15))
	  {
	    //add a tire mark
		sf::Color coul(0,0,0,255);
	    track->add_pixel(rearL_wheel.body->GetPosition().x,rearL_wheel.body->GetPosition().y,coul);
/*	    tire_marks->push_back(rearL_wheel.body->GetPosition());
	    if (tire_marks->size()>MAX_TIRE_MARKS)
	      tire_marks->pop_front();*/
	  }


	//Driving
	b2Vec2 direction = frontR_wheel.body->GetXForm().R.col2;
	direction*=engineSpeed;
	frontR_wheel.body->ApplyForce(direction, frontR_wheel.body->GetPosition());

	direction = frontL_wheel.body->GetXForm().R.col2;
	direction*=engineSpeed;
	frontL_wheel.body->ApplyForce(direction, frontL_wheel.body->GetPosition());

	//Steering
	double mspeed = steeringAngle - frontRJoint->GetJointAngle();
	frontRJoint->SetMotorSpeed(mspeed * STEER_SPEED);

	mspeed = steeringAngle - frontLJoint->GetJointAngle();
	frontLJoint->SetMotorSpeed(mspeed * STEER_SPEED);
    
    x=main_body.body->GetPosition().x;
    y=main_body.body->GetPosition().y;
    
    lap_time++;
}

void Car::aff(sf::RenderWindow *_App,bool infos)
{

  frontR_wheel.aff(_App);
  frontL_wheel.aff(_App);
  rearR_wheel.aff(_App);
  rearL_wheel.aff(_App);
  main_body.aff(_App);
  


 //treat contacts !
  for (unsigned int i=0;i<contact_list.size();i++)
  {
    //std::cout<<"!!"<<std::endl;
    sf::Sprite spr(*boom_image);
    spr.SetCenter(boom_image->GetWidth()/2,boom_image->GetHeight()/2);
    spr.SetPosition (contact_list.at(i)->position.x ,contact_list.at(i)->position.y);
    spr.SetScale(contact_list.at(i)->normalImpulse/4000,contact_list.at(i)->normalImpulse/4000);
    _App->Draw(spr);
    //std::cout<<"!!?"<<std::endl;
  }

  //contacts treated
  contact_list.clear();


  if (infos)
  {
    //draw infromation
    std::ostringstream oss;
    oss<<rank<<"  "<<(last_lap_time/6)/10.0<<"\n"<<damage;
    sf::String Hello;
    Hello.SetText(oss.str());
    Hello.SetColor(sf::Color(0, 128, 128));
    Hello.SetPosition(x-10, y-5);
    Hello.SetRotation(15.f);
    Hello.SetSize(10.f);
    _App->Draw(Hello);
  }
}

bool cmp_Cars( Car *a, Car *b ) {
	bool a_head=true;
	if (b->nbr_checkpoints > a->nbr_checkpoints)
		a_head=false;
	else if (b->nbr_checkpoints == a->nbr_checkpoints)
	{
		if (b->lap_time-b->time_last_checkpoint_in_lap > a->lap_time-a->time_last_checkpoint_in_lap)
			a_head=false;
	}
	
	return a_head;
}

