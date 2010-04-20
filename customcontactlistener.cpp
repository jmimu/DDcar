//      gameobject.cpp
//      
//      Copyright 2010  <jmmuller@myhost>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include "customcontactlistener.hpp"

#include "car.hpp"

#include <map>
#include <iostream>

CustomContactListener::CustomContactListener()
{
	std::cout<<"CustomContactListener !! "<<this<<std::endl;
}

//void CustomContactListener::Add(const b2ContactPoint *point)
//{
  //std::cout<<"Boum !!"<<std::endl;
	/*Car *gameobject1 = static_cast<Car *> ( point->shape1->GetBody()->GetUserData() );
	Car *gameobject2 = static_cast<Car *> ( point->shape2->GetBody()->GetUserData() );

	gameobject1->contact_list[point->id.key] = new b2ContactPoint(*point); // copy constructor
	gameobject2->contact_list[point->id.key] = new b2ContactPoint(*point); // copy constructor again
	*/
//}

//void CustomContactListener::Persist(const b2ContactPoint* point)
//{
	//std::cout<<"mp."<<std::endl;
//}

//void CustomContactListener::Remove(const b2ContactPoint *point)
//{
	//std::cout<<"ak."<<std::endl;
	/*Car *p1 = static_cast<Car *> ( point->shape1->GetBody()->GetUserData() );
	Car *p2 = static_cast<Car *> ( point->shape2->GetBody()->GetUserData() );
 
	std::map<int, b2ContactPoint *>::iterator iter;
 
	iter = p1->contact_list.find(point->id.key);
	if(iter != p1->contact_list.end() ) {
		delete (*iter).second; //necessary since we called new on it
		p1->contact_list.erase(iter);
	}
 
	iter = p2->contact_list.find(point->id.key);
	if(iter != p2->contact_list.end() ) {
		delete (*iter).second;
		p2->contact_list.erase(iter);
	}*/
//}

/*void CustomContactListener::Result(const b2ContactResult* point)
{
  if (fabs(point->normalImpulse)>100)
    {
      Car *car1 = static_cast<Car *> ( point->shape1->GetBody()->GetUserData() );
      Car *car2 = static_cast<Car *> ( point->shape2->GetBody()->GetUserData() );
      if (car1!=NULL)
	car1->contact_list.push_back(new b2ContactResult(*point));
      if (car2!=NULL)
	car2->contact_list.push_back(new b2ContactResult(*point));
    }
}*/

void CustomContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	int32 count = contact->GetManifold()->pointCount;

	float32 maxImpulse = 0.0f;
	b2Vec2 contactPoint;
	for (int32 i = 0; i < count; ++i)
	{
		if (impulse->normalImpulses[i]>maxImpulse)
		{
			contactPoint=contact->GetManifold()->points[i].localPoint;
			maxImpulse = impulse->normalImpulses[i];
		}
	}
	
	if (maxImpulse<100) return;

	std::cout<<"Boom! "<<maxImpulse<<std::endl;

	//get the two cars
	Car *car1 = static_cast<Car *> ( contact->GetFixtureA()->GetBody()->GetUserData() );
	Car *car2 = static_cast<Car *> ( contact->GetFixtureB()->GetBody()->GetUserData() );
	
	/*if (car1!=NULL)
		car1->contact_list.push_back(new b2ContactResult(*point));
	if (car2!=NULL)
		car2->contact_list.push_back(new b2ContactResult(*point));*/
}

