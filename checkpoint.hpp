//      checkpoint.h
//      
//      Copyright 2010 Roa <roa@am>
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


#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <SFML/Graphics.hpp>
#include "car.hpp"

class Checkpoint
{
	public:
		Checkpoint(float _x1,float _y1,float _x2,float _y2);
		virtual ~Checkpoint();
		float get_x1(){return x1;}
		float get_y1(){return y1;}
		float get_x2(){return x2;}
		float get_y2(){return y2;}
		void aff(sf::RenderWindow *_App);
		void set_switched_on(bool on=true);
		bool test(Car * car);//test if car crosses the checkpoint
	private:
		static sf::Image light_off_img;
		static sf::Image light_on_img;
		static bool img_loaded;
		sf::Sprite light_spr1;//left flag
		sf::Sprite light_spr2;//right flag
		float x1,y1,x2,y2;
		float xc,yc,len2;//center
		float a,b,c;//equation
		bool switched_on;
};

#endif /* CHECKPOINT_H */ 
