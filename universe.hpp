//      universe.h
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


#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>

#include "track.hpp"
#include "car.hpp"
#include "camera.hpp"

static const int32 B2_ITERATIONS = 10;
static const float32 B2_TIMESTEP = 1.0f / 30.0f;

/*
 * All the universe: track, cars, objects...
 * 
 * */
class Universe
{
	public:
		Universe(sf::RenderWindow *_App);
		void step();
		void render();
		sf::RenderWindow * get_App(){return App;}
		
		
		Track *track;
		std::vector <Car*> cars;
		Car *player1;
		b2World *world;
	private:
		sf::Image car_image;
		sf::Image wheel_image;
		Camera camera;
		sf::RenderWindow *App;
};

#endif /* UNIVERSE_H */ 
