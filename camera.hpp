//      camera.h
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


#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
/*
 * To draw the universe on the screen
 * 
 * */
class Camera
{
	public:
		Camera();
		
		void set_target(float t_x,float t_y,float t_z);
		sf::View * get_view(){return &view;} 
		float get_x(){return x;}
		float get_y(){return y;}
		float get_zoom(){return zoom;}
		bool set_zoom(float _zoom)
		{
			if ((_zoom>0)&&(_zoom<100))
			{
				zoom=_zoom;
				return true;
			}else{
				return false;
			}
		}
		

		
	private:
		float x,y,zoom;
		sf::View view;
};

#endif /* CAMERA_H */ 
