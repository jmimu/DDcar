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
	
	track=new Track(*world,"data/track.png","data/trackB.png",32);
	
	//images
	car_image.LoadFromFile("data/car.png");
	wheel_image.LoadFromFile("data/wheel.png");
	//cars
	cars.push_back(new Car(*world,10,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,80,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,100,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,120,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,140,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,160,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,180,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,200,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,220,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,240,20,&car_image,&wheel_image));
	cars.push_back(new Car(*world,260,20,&car_image,&wheel_image));
	player1=cars.at(0);
	
}

void Universe::step()
{
	world->Step(B2_TIMESTEP, B2_ITERATIONS);
	for (int i=0;i<cars.size();i++)
	{
		sf::Color ground_FR=track->get_ground_nature(player1->get_frontR_wheel()->body->GetWorldCenter().x,player1->get_frontR_wheel()->body->GetWorldCenter().y);
		sf::Color ground_FL=track->get_ground_nature(player1->get_frontL_wheel()->body->GetWorldCenter().x,player1->get_frontL_wheel()->body->GetWorldCenter().y);
		sf::Color ground_RR=track->get_ground_nature(player1->get_rearR_wheel()->body->GetWorldCenter().x,player1->get_rearR_wheel()->body->GetWorldCenter().y);
		sf::Color ground_RL=track->get_ground_nature(player1->get_rearL_wheel()->body->GetWorldCenter().x,player1->get_rearL_wheel()->body->GetWorldCenter().y);
		//std::cout<<" "<<(int)ground_FL.r<<" "<<(int)ground_FR.r<<" / "<<(int)ground_RL.r<<" "<<(int)ground_RR.r<<std::endl;
		cars.at(i)->update(ground_FR,ground_FL,ground_RR,ground_RL);
		
		//AI
		if (i>0)
			cars.at(i)->follow(player1->get_x(),player1->get_y());
	}
}

void Universe::render()
{
	float point_before_player_x=player1->get_x()+sin(player1->get_main_body()->body->GetAngle())*player1->get_speed()/2;
	float point_before_player_y=player1->get_y()-cos(player1->get_main_body()->body->GetAngle())*player1->get_speed()/2;
	std::cout<<"Speed: "<<player1->get_speed()<<std::endl;
	
	App->SetView(*camera.get_view());
	camera.set_target(point_before_player_x,point_before_player_y,player1->get_speed()/10);

	track->aff(App);

	for (int i=0;i<track->walls.size();i++)
		track->walls.at(i)->aff(App);
	for (int i=0;i<cars.size();i++)
		cars.at(i)->aff(App);
}
