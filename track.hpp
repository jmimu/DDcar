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

#include "checkpoint.hpp"


/*
 * Track: walls
 * map : big image cut into tiles
 * */
class Track
{
	public:
		Track(b2World &world,std::string img_filename,std::string gnd_img_filename,int _tile_size);
		std::vector <Box*> walls;
		void aff(sf::RenderWindow *_App);
		sf::Color get_ground_nature(float x, float y);
		std::vector <b2Vec2> trajectory;
		std::vector <Checkpoint *> checkpoints;
	private:
		int tile_size;
		std::vector <sf::Image*> tiles_img; //picture of the track
		float TRACK_PIXEL_PER_UNIT;
		std::vector <sf::Sprite*> tiles_spr;
		sf::Image ground_nature;//unseen image !
		float GROUND_PIXEL_PER_UNIT;
		int nbr_tiles_x;
		int nbr_tiles_y;
		
		
};

#endif /* TRACK_H */ 
