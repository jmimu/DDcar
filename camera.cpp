//      camera.cpp
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


#include "camera.hpp"

Camera::Camera()
 : x(0),y(0),zoom(1),view()
{
	//don't forget to set the view to the application !
}

void Camera::set_target(float t_x,float t_y,float t_z)
{
	x+=(t_x-x)/10;
	y+=(t_y-y)/10;
	float target_zoom=12-t_z/0.8;
	
	zoom+=(target_zoom-zoom)/50;
	
	view.SetCenter(x, y);
	view.SetHalfSize(400.0/zoom,300.0/zoom);

}


