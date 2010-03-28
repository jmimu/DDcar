//      universe.cpp
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


#include "universe.hpp"

#include <iostream>

Universe::Universe(sf::RenderWindow *_App)
 : player1(NULL),camera(),App(_App)
{
	//create box2d world
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-1000.0f, -1000.0f);
	worldAABB.upperBound.Set(10000.0f, 10000.0f);
	b2Vec2 gravity(0.0f, -10.0f*0);
	bool doSleep = true;
	world=new b2World(worldAABB, gravity, doSleep);
	
	track=new Track(*world,"data/track.png",32);
	
	//images
	car_image.LoadFromFile("data/car.png");
	wheel_image.LoadFromFile("data/wheel.png");
	//cars
	cars.push_back(new Car(*world,0,0,&car_image,&wheel_image));
	cars.push_back(new Car(*world,20,20,&car_image,&wheel_image));
	player1=cars.at(0);
	
	//camera
	App->SetView(*camera.get_view());
}

void Universe::step()
{
	world->Step(B2_TIMESTEP, B2_ITERATIONS);
	for (int i=0;i<cars.size();i++)
		cars.at(i)->update();
}

void Universe::render()
{
	float point_before_player_x=player1->get_x()+sin(player1->get_main_body()->body->GetAngle())*player1->get_speed();
	float point_before_player_y=player1->get_y()-cos(player1->get_main_body()->body->GetAngle())*player1->get_speed();
	//std::cout<<"Speed: "<<player1->get_speed()<<std::endl;
	camera.set_target(point_before_player_x,point_before_player_y,player1->get_speed()/10);

	track->aff(App);

	for (int i=0;i<track->walls.size();i++)
		track->walls.at(i)->aff(App);
	for (int i=0;i<cars.size();i++)
		cars.at(i)->aff(App);
}
