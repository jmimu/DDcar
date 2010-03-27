//      track.cpp
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


#include "track.hpp"

#include <Box2D.h>

Track::Track(b2World &world)
: walls()
{
	walls.push_back(new Box(world,0.0f, 5.0f,70.0f, 1.0f,0.2,sf::Color::Blue,NULL,0.0,false)); //down
	walls.push_back(new Box(world,-35.0f, 120.0f,150.0f, 1.0f,1.5,sf::Color::Blue,NULL,0.0,false)); //left
	walls.push_back(new Box(world,0.0f, 240.0f,70.0f, 1.0f,-0.1,sf::Color::Blue,NULL,0.0,false)); //up
	walls.push_back(new Box(world,35.0f, 120.0f,200.0f, 1.0f,1.5,sf::Color::Blue,NULL,0.0,false));	//right
}


