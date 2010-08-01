#include "car.hpp"

#include <iostream>
#include <sstream>
#include "track.hpp"

sf::Image Car::wheel_image;
sf::Image Car::boom_image;
std::map<std::string,sf::Image> Car::main_images;
std::vector<sf::Image *> Car::animation;
bool Car::images_loaded=false;

bool Car::load_images()
{
  bool res=true;

  res&=wheel_image.LoadFromFile("data/wheel2.png");wheel_image.SetSmooth(false);
  res&=boom_image.LoadFromFile("data/star.png");boom_image.SetSmooth(false);

  /*sf::Image car_image1;
  res&=car_image1.LoadFromFile("data/carA.png");
  main_images.insert( std::make_pair( "data/carA.png",car_image1  ) );
  sf::Image car_image2;
  res&=car_image2.LoadFromFile("data/carB.png");
  main_images.insert( std::make_pair( "data/carB.png",car_image2  ) );*/
  
  sf::Image *img1=new sf::Image();img1->LoadFromFile("data/anim/guy1.png");animation.push_back(img1);img1->SetSmooth(false);
  sf::Image *img2=new sf::Image();img2->LoadFromFile("data/anim/guy2.png");animation.push_back(img2);img2->SetSmooth(false);
  sf::Image *img3=new sf::Image();img3->LoadFromFile("data/anim/guy3.png");animation.push_back(img3);img3->SetSmooth(false);
  sf::Image *img4=new sf::Image();img4->LoadFromFile("data/anim/guy4.png");animation.push_back(img4);img4->SetSmooth(false);
  sf::Image *img5=new sf::Image();img5->LoadFromFile("data/anim/guy5.png");animation.push_back(img5);img5->SetSmooth(false);
  sf::Image *img6=new sf::Image();img6->LoadFromFile("data/anim/guy6.png");animation.push_back(img6);img6->SetSmooth(false);
  sf::Image *img7=new sf::Image();img7->LoadFromFile("data/anim/guy7.png");animation.push_back(img7);img7->SetSmooth(false);
  sf::Image *img8=new sf::Image();img8->LoadFromFile("data/anim/guy8.png");animation.push_back(img8);img8->SetSmooth(false);
  
  images_loaded=true;
  
  if (!res)
    std::cout<<"Error reading car images !"<<std::endl;
  return res;
}



Car::Car(b2World &world,float _x,float _y,std::string image_name)
  : index_trajectory_point_target(0),next_checkpoint_index(0),x(_x),y(_y),h(16),w(8),
    main_body(world,x,y,9,14,0.0,sf::Color::Red,get_image(image_name),0.2*4,false,0.3*0,0.2*0,1.0),
    frontR_wheel(world,x+3.5,y-5,2,4,0.0,sf::Color::Green,&wheel_image,0.2,true),
    frontL_wheel(world,x-3.5,y-5,2,4,0.0,sf::Color::Green,&wheel_image,0.2,true),
    rearR_wheel(world,x+3.5,y+5,2,4,0.0,sf::Color::Green,&wheel_image,0.2,true),
    rearL_wheel(world,x-3.5,y+5,2,4,0.0,sf::Color::Green,&wheel_image,0.2,true),
    current_image(0.0),
    nbr_frames_without_tangent_speed(0),going_backward(false),
    lap_time(0),last_lap_time(0),nbr_laps(-1),
    nbr_checkpoints(0),time_last_checkpoint_in_lap(0),rank(0),damage(0)
{
	main_body.PIXEL_PER_UNIT=4.5;

	MAX_STEER_ANGLE = 0.3;
	STEER_SPEED = 1.5*4;
	SIDEWAYS_FRICTION_FORCE = 10;
	HORSEPOWERS = 1000*1.6;
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

sf::Image * Car::get_image(std::string image_name)
{
  if (!images_loaded) load_images();

  std::map<std::string,sf::Image>::iterator iter = main_images.find(image_name);
  if( iter == main_images.end() ) {
    std::cout<<"Have to load a new image: "<<image_name<<std::endl;
    //...
    sf::Image car_img;
    if (!car_img.LoadFromFile(image_name))
      std::cout<<"Error loading image."<<std::endl;
    main_images.insert( std::make_pair( image_name,car_img ) );
    iter = main_images.find(image_name);
  }
  
  return &(iter->second);

}


//return true if wheel skids (more than threshold)
bool Car::killOrthogonalVelocity(b2Body* targetBody,float threshold)
{
  bool skids=false;

  b2Vec2 localPoint(0,0);
  b2Vec2 velocity = targetBody->GetLinearVelocityFromLocalPoint(localPoint);
  b2Vec2 sidewaysAxis = targetBody->GetTransform().R.col2;

  b2Vec2 otherAxis = targetBody->GetTransform().R.col1;

  //std::cout<<b2Dot(velocity,otherAxis)<<std::endl;

  if ( fabs(b2Dot(velocity,otherAxis)) > threshold) skids=true;

  sidewaysAxis*=(b2Dot(velocity,sidewaysAxis));
  //print sidewaysAxis,"\n"
  targetBody->SetLinearVelocity(sidewaysAxis);//targetBody.GetWorldPoint(localPoint));

  return skids;
}
void Car::follow(std::vector<b2Vec2> * trajectory)
{
  follow(trajectory->at(index_trajectory_point_target).x,trajectory->at(index_trajectory_point_target).y);
}
void Car::follow(float t_x,float t_y) //AI
{
	b2Vec2 car_to_target;
	car_to_target.x=t_x-main_body.body->GetPosition().x;
	car_to_target.y=t_y-main_body.body->GetPosition().y;
	
	float dist_to_target=sqrt(car_to_target.x*car_to_target.x+car_to_target.y*car_to_target.y);
	
	/*	if (dist_to_target<30)
	{
		index_trajectory_point_target++;
		going_backward=false;//once at the target, no need to continue backwards
		//std::cout<<"Next point"<<std::endl;
		return;
		}*/
	
	
	b2Vec2 orientation = main_body.body->GetTransform().R.col2;
	//std::cout<<"car_to_target ("<<car_to_target.x<<","<<car_to_target.y<<") orientation ("<<orientation.x<<","<<orientation.y<<")"<<std::endl;
	
	b2Vec2 car_to_target_colin=orientation;
	car_to_target_colin*=(b2Dot(orientation,car_to_target));//colinear part
	b2Vec2 car_to_target_normal;//normal part
	car_to_target_normal.x=car_to_target.x-car_to_target_colin.x;
	car_to_target_normal.y=car_to_target.y-car_to_target_colin.y;
	//std::cout<<"car_to_target_colin  ("<<car_to_target_colin.x<<","<<car_to_target_colin.y<<")"<<std::endl;
	//std::cout<<"car_to_target_normal ("<<car_to_target_normal.x<<","<<car_to_target_normal.y<<")"<<std::endl;
	
	float dist_normal=sqrt(car_to_target_normal.x*car_to_target_normal.x+car_to_target_normal.y*car_to_target_normal.y);
	
	if (dist_to_target>30)
	{
		if (b2Dot(orientation,car_to_target)>0)
		{
			engineSpeed = HORSEPOWERS;
			//steeringAngle = -MAX_STEER_ANGLE;
			//return;
		}else{
			engineSpeed = -HORSEPOWERS;
		}
	}/*else{
		engineSpeed=0;
		//point reached => next trajectory point
		index_trajectory_point_target++;
		
	}*/

	if (dist_normal>10)
	{
		if (car_to_target_normal.x*car_to_target_colin.y-car_to_target_colin.x*car_to_target_normal.y>0)
			steeringAngle = -MAX_STEER_ANGLE;
		else
			steeringAngle = MAX_STEER_ANGLE;
	}else 
		steeringAngle = 0;

	//test if need to go backwards
	double tangent_speed=get_tangent_speed();
	if (tangent_speed<0.2)
	  {
	    nbr_frames_without_tangent_speed++;
	    if (nbr_frames_without_tangent_speed>5)
	      {
		going_backward=!going_backward;
		nbr_frames_without_tangent_speed=0;
	      }
	  }
	else
	  {
	    nbr_frames_without_tangent_speed=0;
	  }

	if (going_backward)
	  {
	    steeringAngle*=-1;
	    engineSpeed*=-1;
	  }

	//std::cout<<tangent_speed<<" "<<nbr_frames_without_tangent_speed<<" "<<going_backward<<" "<<engineSpeed<<std::endl;

}

double Car::get_speed()
{
	b2Vec2 localPoint(0,0);
	b2Vec2 velocity = main_body.body->GetLinearVelocityFromLocalPoint(localPoint);
	return sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
}

double Car::get_tangent_speed()
{
	b2Vec2 localPoint(0,0);
	b2Vec2 velocity = main_body.body->GetLinearVelocityFromLocalPoint(localPoint);
	b2Vec2 sidewaysAxis = main_body.body->GetTransform().R.col2;
	sidewaysAxis*=(b2Dot(velocity,sidewaysAxis));
	return sqrt(sidewaysAxis.x*sidewaysAxis.x + sidewaysAxis.y*sidewaysAxis.y);
}

void Car::update(sf::Color ground_FR,sf::Color ground_FL,sf::Color ground_RR,sf::Color ground_RL/*,std::deque <b2Vec2> * tire_marks*/,Track * track)
{
	//treat contacts !
	for (unsigned int i=0;i<contact_list.size();i++)
	{
		damage+=contact_list.at(i).normal/100;
		/*std::cout<<"=== "<<contact_list.at(i)->normalImpulse
		<<" "<<contact_list.at(i)->tangentImpulse
		<<" "<<contact_list.at(i)->shape1->GetBody()->GetUserData()
		<<" "<<contact_list.at(i)->shape2->GetBody()->GetUserData()
		<<" "<<contact_list.at(i)->position.x<<","<<contact_list.at(i)->position.y
		<<" "<<contact_list.at(i)->normal.x<<","<<contact_list.at(i)->normal.y
		<<" "<<std::endl;*/
       }

	//where are we on trajectory ?
	b2Vec2 car_to_target;
	car_to_target.x=track->trajectory.at(index_trajectory_point_target).x-main_body.body->GetPosition().x;
	car_to_target.y=track->trajectory.at(index_trajectory_point_target).y-main_body.body->GetPosition().y;
	
	float dist_to_target=sqrt(car_to_target.x*car_to_target.x+car_to_target.y*car_to_target.y);
	
	if (dist_to_target<30)
	{
		index_trajectory_point_target++;
		if (index_trajectory_point_target >= track->trajectory.size())
		  index_trajectory_point_target =0;
		going_backward=false;//once at the target, no need to continue backwards
		//std::cout<<"Next point"<<std::endl;
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

	    track->add_pixel(frontR_wheel.body->GetPosition().x-0.5,frontR_wheel.body->GetPosition().y,coul);
	    track->add_pixel(frontR_wheel.body->GetPosition().x+0.5,frontR_wheel.body->GetPosition().y,coul);
	    track->add_pixel(frontR_wheel.body->GetPosition().x,frontR_wheel.body->GetPosition().y-0.5,coul);
	    track->add_pixel(frontR_wheel.body->GetPosition().x,frontR_wheel.body->GetPosition().y+0.5,coul);
/*	    tire_marks->push_back(frontR_wheel.body->GetPosition());
	    if (tire_marks->size()>MAX_TIRE_MARKS)
	      tire_marks->pop_front();*/
	  }
	if (killOrthogonalVelocity(frontL_wheel.body,15))
	  {
	    //add a tire mark
		sf::Color coul(0,0,0,255);
	    track->add_pixel(frontL_wheel.body->GetPosition().x,frontL_wheel.body->GetPosition().y,coul);

	    track->add_pixel(frontL_wheel.body->GetPosition().x-0.5,frontL_wheel.body->GetPosition().y,coul);
	    track->add_pixel(frontL_wheel.body->GetPosition().x+0.5,frontL_wheel.body->GetPosition().y,coul);
	    track->add_pixel(frontL_wheel.body->GetPosition().x,frontL_wheel.body->GetPosition().y-0.5,coul);
	    track->add_pixel(frontL_wheel.body->GetPosition().x,frontL_wheel.body->GetPosition().y+0.5,coul);
/*	    tire_marks->push_back(frontL_wheel.body->GetPosition());
	    if (tire_marks->size()>MAX_TIRE_MARKS)
	      tire_marks->pop_front();*/
	  }
	if (killOrthogonalVelocity(rearR_wheel.body,15))
	  {
	    //add a tire mark
		sf::Color coul(0,0,0,255);
	    track->add_pixel(rearR_wheel.body->GetPosition().x,rearR_wheel.body->GetPosition().y,coul);

	    track->add_pixel(rearR_wheel.body->GetPosition().x-0.5,rearR_wheel.body->GetPosition().y,coul);
	    track->add_pixel(rearR_wheel.body->GetPosition().x+0.5,rearR_wheel.body->GetPosition().y,coul);
	    track->add_pixel(rearR_wheel.body->GetPosition().x,rearR_wheel.body->GetPosition().y-0.5,coul);
	    track->add_pixel(rearR_wheel.body->GetPosition().x,rearR_wheel.body->GetPosition().y+0.5,coul);
/*	    tire_marks->push_back(rearR_wheel.body->GetPosition());
	    if (tire_marks->size()>MAX_TIRE_MARKS)
	      tire_marks->pop_front();*/
	  }
	if (killOrthogonalVelocity(rearL_wheel.body,15))
	  {
	    //add a tire mark
		sf::Color coul(0,0,0,255);
	    track->add_pixel(rearL_wheel.body->GetPosition().x,rearL_wheel.body->GetPosition().y,coul);

	    track->add_pixel(rearL_wheel.body->GetPosition().x-0.5,rearL_wheel.body->GetPosition().y,coul);
	    track->add_pixel(rearL_wheel.body->GetPosition().x+0.5,rearL_wheel.body->GetPosition().y,coul);
	    track->add_pixel(rearL_wheel.body->GetPosition().x,rearL_wheel.body->GetPosition().y-0.5,coul);
	    track->add_pixel(rearL_wheel.body->GetPosition().x,rearL_wheel.body->GetPosition().y+0.5,coul);
/*	    tire_marks->push_back(rearL_wheel.body->GetPosition());
	    if (tire_marks->size()>MAX_TIRE_MARKS)
	      tire_marks->pop_front();*/
	  }


	//Driving
	b2Vec2 direction = frontR_wheel.body->GetTransform().R.col2;
	direction*=engineSpeed;
	frontR_wheel.body->ApplyForce(direction, frontR_wheel.body->GetPosition());

	direction = frontL_wheel.body->GetTransform().R.col2;
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
  current_image+=get_speed()/200.0;
  if ((unsigned int)current_image>=animation.size())
    current_image=0.0;
  main_body.sprite.SetImage(*animation.at((unsigned int)current_image));
  main_body.aff(_App);
  frontR_wheel.aff(_App);
  frontL_wheel.aff(_App);
  rearR_wheel.aff(_App);
  rearL_wheel.aff(_App);
  


 //treat contacts !
  for (unsigned int i=0;i<contact_list.size();i++)
  {
    //std::cout<<"!!"<<std::endl;
    sf::Sprite spr(boom_image);
    spr.SetCenter(boom_image.GetWidth()/2,boom_image.GetHeight()/2);
    spr.SetPosition (contact_list.at(i).point.x ,contact_list.at(i).point.y);
    spr.SetScale(contact_list.at(i).normal/4000,contact_list.at(i).normal/4000);
    _App->Draw(spr);
    //std::cout<<"!!?"<<std::endl;
  }

  //contacts treated
  contact_list.clear();


  if (infos)
  {
    //draw infromation
    std::ostringstream oss;
    oss<<rank<<"  "<<(last_lap_time/6)/10.0<<"\n"<<damage<<"  "<<nbr_laps;
    sf::String Hello;
    Hello.SetText(oss.str());
    Hello.SetColor(sf::Color(200, 200, 10,100));
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

