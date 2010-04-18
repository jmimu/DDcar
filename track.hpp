//      track.h
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


#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include <string>
#include "box.hpp"
#include <Box2D.h>
#include <deque>

#include "checkpoint.hpp"


/*
 * Track: walls
 * map : big image cut into tiles
 * */
class Track
{
	public:
		Track(b2World &world,std::string track_file,int _tile_size=41);
		std::vector <Box*> walls;
		void aff(sf::RenderWindow *_App);
		sf::Color get_ground_nature(float x, float y);
		std::vector <b2Vec2> trajectory;
		std::vector <Checkpoint *> checkpoints;
		
		void add_pixel(float x,float y,sf::Color c);//change the pixel in the background image

  //std::deque <b2Vec2> tire_marks;//modified by cars
	private:
		int tile_size;
		std::vector <sf::Image*> tiles_img; //picture of the track
		float TRACK_PIXEL_PER_UNIT;
		std::vector <sf::Sprite*> tiles_spr;
		sf::Image ground_nature;//unseen image !
		float GROUND_PIXEL_PER_UNIT;
		int nbr_tiles_x;
		int nbr_tiles_y;
  //sf::Image tire_mark_image;
		
};

#endif /* TRACK_H */ 
