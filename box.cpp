#include "box.hpp"


Box::Box(b2World &world,float _x,float _y,float _w,float _h,float _angle,sf::Color _c,sf::Image *_image,float _density,bool _sensor,float _friction,float _linearDamping,float _angularDamping)
  : image(_image),PIXEL_PER_UNIT(10),m_w(_w/2),m_h(_h/2)
{
  if (image != NULL)
    {
      sprite.SetImage(*image);
      sprite.SetCenter(sprite.GetSize().x/2.0, sprite.GetSize().y/2.0);
    }
  coul=_c;
  
  /*
  //body
  bodyDef=new b2BodyDef();
  bodyDef->position.Set(_x, _y);
  bodyDef->angle=_angle;
  
  bodyDef->linearDamping = _linearDamping;
  bodyDef->angularDamping = _angularDamping;
  
  body = world.CreateBody(bodyDef);
  
  //shape
  b2PolygonShape shapeDef;
  shapeDef.SetAsBox(m_w, m_h);
  
  
  shapeDef.density = _density;
  shapeDef.friction = _friction;
  shapeDef.isSensor = _sensor;
  body->CreateShape(&shapeDef);

  body->SetMassFromShapes();
  */
  
  bodyDef=new b2BodyDef();
  
  if (_density>0.0001)
    bodyDef->type = b2_dynamicBody;
  
  bodyDef->position.Set(_x, _y);
  bodyDef->angle=_angle;
  
  bodyDef->linearDamping = _linearDamping;
  bodyDef->angularDamping = _angularDamping;
  body = world.CreateBody(bodyDef);
  
  // Define another box shape for our dynamic body.
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox((float32)m_w,(float32) m_h);
  
  // Define the dynamic body fixture.
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  
  // Set the box density to be non-zero, so it will be dynamic.
  fixtureDef.density = _density;
  fixtureDef.friction = _friction;
  fixtureDef.isSensor = _sensor;

  // Add the shape to the body.
  body->CreateFixture(&fixtureDef);
  
  
}

Box::~Box()
{
	//delete body;
}

void Box::aff(sf::RenderWindow *_App)
{
  //b2Vec2 position = body->GetPosition();
  //float32 angle = body->GetAngle();
	
	if (image == NULL)
	{
		sf::Shape rect =sf::Shape::Rectangle(-m_w, -m_h, m_w, m_h, coul);
		rect.SetPosition (body->GetPosition().x ,body->GetPosition().y);
		rect.Rotate(-body->GetAngle()*180.0/3.14159265359);
		sprite.SetScale(1.0/PIXEL_PER_UNIT,1.0/PIXEL_PER_UNIT);
		_App->Draw(rect);
	}
	else
	{
		sprite.SetPosition (body->GetPosition().x ,body->GetPosition().y );
		sprite.SetRotation(-body->GetAngle()*180.0/3.14159265359);
		sprite.SetScale(1.0/PIXEL_PER_UNIT,1.0/PIXEL_PER_UNIT);
		_App->Draw(sprite);
	}
}
