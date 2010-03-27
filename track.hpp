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

#define TRACK_PIXEL_PER_UNIT 1

class b2World;
/*
 * Track: walls
 * map : big image cut into tiles
 * */
class Track
{
	public:
		Track(b2World &world,std::string img_filename,int _tile_size);
		std::vector <Box*> walls;
		void aff(sf::RenderWindow *_App);
	private:
		int tile_size;
		std::vector <sf::Image*> tiles_img;
		std::vector <sf::Sprite*> tiles_spr;
		int nbr_tiles_x;
		int nbr_tiles_y;
};

#endif /* TRACK_H */ 
