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

Universe::Universe(sf::RenderWindow *_App,std::string track_filename,int nbr_cars)
  : player1(NULL),App(_App),player1_autopilote(false)
{
	//create box2d world
	/*b2AABB worldAABB;
	worldAABB.lowerBound.Set(-1000.0f, -1000.0f);
	worldAABB.upperBound.Set(10000.0f, 10000.0f);*/
	b2Vec2 gravity(0.0f, -10.0f*0);
	bool doSleep = true;
	world=new b2World(/*worldAABB,*/ gravity, doSleep);
	
		
	track=new Track(*world,track_filename);
  	
	//cars
	for (unsigned int i=0; i<track->starting_pos.size() && i< nbr_cars;i++)
	{
	  cars.push_back(new Car(*world,track->starting_pos.at(i).x,track->starting_pos.at(i).y,"data/anim/guy1.png"));
	  cars.at(i)->get_main_body()->body->SetTransform(track->starting_pos.at(i), track->starting_angle.at(i));
	}
	
	player1=cars.at(cars.size()-1);
	
	//initialiee cars.at(i)->time_last_checkpoint_in_lap to have the starting order
	for (int i=0;i<cars.size();i++)
		cars.at(i)->time_last_checkpoint_in_lap=i;
	

	
	world->SetContactListener(&contact_listener);
	
	std::cout<<"Universe created."<<std::endl;
}

void Universe::step()
{
	bool one_checkpoint_crossed=false;//to know if re-order needed
	world->Step(B2_TIMESTEP, B2_VELOCITY_ITERATIONS,B2_POSITION_ITERATIONS);
	for (int i=0;i<cars.size();i++)
	{
		sf::Color ground_FR=track->get_ground_nature(cars.at(i)->get_frontR_wheel()->body->GetWorldCenter().x,cars.at(i)->get_frontR_wheel()->body->GetWorldCenter().y);
		sf::Color ground_FL=track->get_ground_nature(cars.at(i)->get_frontL_wheel()->body->GetWorldCenter().x,cars.at(i)->get_frontL_wheel()->body->GetWorldCenter().y);
		sf::Color ground_RR=track->get_ground_nature(cars.at(i)->get_rearR_wheel()->body->GetWorldCenter().x,cars.at(i)->get_rearR_wheel()->body->GetWorldCenter().y);
		sf::Color ground_RL=track->get_ground_nature(cars.at(i)->get_rearL_wheel()->body->GetWorldCenter().x,cars.at(i)->get_rearL_wheel()->body->GetWorldCenter().y);
		//std::cout<<" "<<(int)ground_FL.r<<" "<<(int)ground_FR.r<<" / "<<(int)ground_RL.r<<" "<<(int)ground_RR.r<<std::endl;
		cars.at(i)->update(ground_FR,ground_FL,ground_RR,ground_RL/*,& track->tire_marks*/,track);
		
		
		//test checkpoint
		int checkpoint_index=cars.at(i)->next_checkpoint_index;
		//std::cout<<"test "<<checkpoint_index<<std::endl;
		if (track->checkpoints.at(checkpoint_index)->test(cars.at(i)))
		{
			if (checkpoint_index==0) //start line
			{
				double lap_time=cars.at(i)->new_lap()/60.0;
				//if (cars.at(i)==player1) std::cout<<"Lap: "<<lap_time<<std::endl;
			} //else if (cars.at(i)==player1) std::cout<<"Checkpoint!"<<std::endl;
			
			one_checkpoint_crossed=true;
			cars.at(i)->nbr_checkpoints++;
			cars.at(i)->time_last_checkpoint_in_lap=cars.at(i)->lap_time;
			
			
			if (cars.at(i)==player1) track->checkpoints.at(checkpoint_index)->set_switched_on(false);
			cars.at(i)->next_checkpoint_index++;
			if (cars.at(i)->next_checkpoint_index>=track->checkpoints.size())
				cars.at(i)->next_checkpoint_index=0;
			if (cars.at(i)==player1) track->checkpoints.at(cars.at(i)->next_checkpoint_index)->set_switched_on(true);
		}
		
		//AI
		if ((cars.at(i)!=player1) || player1_autopilote)
		{
			//			cars.at(i)->follow(track->trajectory.at(cars.at(i)->index_trajectory_point_target).x,track->trajectory.at(cars.at(i)->index_trajectory_point_target).y);
			cars.at(i)->follow(&(track->trajectory));
		}
	}
	
	if (one_checkpoint_crossed)
	{
		sort( cars.begin(), cars.end(), cmp_Cars );
		for (int i=0;i<cars.size();i++)
			cars.at(i)->rank=i+1;
	}
}

void Universe::render()
{


	/*b2Vec2 localPoint(0,0);
	b2Vec2 velocity = player1->get_main_body()->body->GetLinearVelocityFromLocalPoint(localPoint);
	std::cout<<"Speed: "<<player1->get_speed()<<" "<<velocity.x<<" "<<velocity.y<<std::endl;*/
	

	track->aff(App);

	for (int i=0;i<track->walls.size();i++)
		track->walls.at(i)->aff(App);
	for (int i=0;i<cars.size();i++)
		cars.at(i)->aff(App,true);
	
	//std::cout<<"contacts: "<<player1->contact_list.size()<<std::endl;
}
