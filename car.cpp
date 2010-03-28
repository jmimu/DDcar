#include "car.hpp"


Car::Car(b2World &world,float x,float y,sf::Image *car_image,sf::Image *wheel_image)
  : main_body(world,x,y,10,16,0.0,sf::Color::Red, car_image,0.2*4,false,0.3,1.0,1.0),
    frontR_wheel(world,x+3,y-5,2,4,0.0,sf::Color::Green,wheel_image,0.2,true),
    frontL_wheel(world,x-3,y-5,2,4,0.0,sf::Color::Green,wheel_image,0.2,true),
    rearR_wheel(world,x+3,y+5,2,4,0.0,sf::Color::Green,wheel_image,0.2,true),
    rearL_wheel(world,x-3,y+5,2,4,0.0,sf::Color::Green,wheel_image,0.2,true)
{
	MAX_STEER_ANGLE = 0.3;
	STEER_SPEED = 1.5*4;
	SIDEWAYS_FRICTION_FORCE = 10;
	HORSEPOWERS = 1000*2;
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

}

Car::~Car()
{
	//delete body;
}

void Car::killOrthogonalVelocity(b2Body* targetBody)
{
  b2Vec2 localPoint(0,0);
  b2Vec2 velocity = targetBody->GetLinearVelocityFromLocalPoint(localPoint);
  b2Vec2 sidewaysAxis = targetBody->GetXForm().R.col2;
  //print "! ",velocity," ",sidewaysAxis," ",b2Dot(velocity,sidewaysAxis),"\n"
  sidewaysAxis*=(b2Dot(velocity,sidewaysAxis));
  //print sidewaysAxis,"\n"
  targetBody->SetLinearVelocity(sidewaysAxis);//targetBody.GetWorldPoint(localPoint));
}

double Car::get_speed()
{
	b2Vec2 localPoint(0,0);
	b2Vec2 velocity = main_body.body->GetLinearVelocityFromLocalPoint(localPoint);
	return sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
}

void Car::update()
{
	killOrthogonalVelocity(frontR_wheel.body);
	killOrthogonalVelocity(frontL_wheel.body);
	killOrthogonalVelocity(rearR_wheel.body);
	killOrthogonalVelocity(rearL_wheel.body);

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
}

void Car::aff(sf::RenderWindow *_App)
{

  main_body.aff(_App);
  frontR_wheel.aff(_App);
  frontL_wheel.aff(_App);
  rearR_wheel.aff(_App);
  rearL_wheel.aff(_App);
}
