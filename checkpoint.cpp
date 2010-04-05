//      checkpoint.cpp
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


#include "checkpoint.hpp"

#include <iostream>

sf::Image Checkpoint::light_off_img;
sf::Image Checkpoint::light_on_img;

bool Checkpoint::img_loaded=false;

Checkpoint::Checkpoint(float _x1,float _y1,float _x2,float _y2)
: x1(_x1),y1(_y1),x2(_x2),y2(_y2),switched_on(false),xc((x1+x2)/2),yc((y1+y2)/2)
{
	if (!img_loaded)
	{
		light_off_img.LoadFromFile("data/light1.png");//both pics must have the same size;
		light_on_img.LoadFromFile("data/light2.png");
	}
	light_spr1.SetImage(light_off_img);
	light_spr2.SetImage(light_off_img);
	light_spr1.SetCenter(light_spr1.GetImage()->GetWidth()/2,light_spr1.GetImage()->GetWidth()/2);
	light_spr2.SetCenter(light_spr2.GetImage()->GetWidth()/2,light_spr2.GetImage()->GetWidth()/2);

	light_spr1.SetPosition(x1,y1);
	light_spr1.SetScale(0.2,0.2);
	light_spr2.SetPosition(x2,y2);
	light_spr2.SetScale(0.2,0.2);
	
	//equation:
	float dx=x1-x2;
	float dy=y1-y2;
	if (fabs(dx)>fabs(dy))
	{
		b=1.0;
		a=-dy/dx;
	}else{
		a=1.0;
		b=-dx/dy;
	}
	c=-a*x1-b*y1;
	len2=(dx*dx+dy*dy);
}


Checkpoint::~Checkpoint()
{
	
}

void Checkpoint::set_switched_on(bool on)
{
	if (on == switched_on) return;
	switched_on=on;
	if (switched_on)
	{
		light_on_img.LoadFromFile("data/light2.png");
		light_spr1.SetImage(light_on_img);
		light_spr2.SetImage(light_on_img);
	}else{
		light_off_img.LoadFromFile("data/light1.png");
		light_spr1.SetImage(light_off_img);
		light_spr2.SetImage(light_off_img);
	}
	/*light_spr1.SetCenter(light_spr1.GetImage()->GetWidth()/2,light_spr1.GetImage()->GetWidth()/2);
	light_spr2.SetCenter(light_spr2.GetImage()->GetWidth()/2,light_spr2.GetImage()->GetWidth()/2);
	light_spr1.SetPosition(x1,y1);
	light_spr1.SetScale(0.2,0.2);
	light_spr2.SetPosition(x2,y2);
	light_spr2.SetScale(0.2,0.2);*/
}

void Checkpoint::aff(sf::RenderWindow *_App)
{
	_App->Draw(light_spr1);
	_App->Draw(light_spr2);
}

bool Checkpoint::test(Car * car)//test if car crosses the checkpoint
{
	//1st: approx test
	//std::cout<<
	float dx=car->get_x()-xc;
	float dy=car->get_y()-yc;
	float dist2=dx*dx+dy*dy;
	if (dist2>len2/2)
		return false;//too far
	
	//if dist to center is >40
	//2nd: create car points
	//3rd: if across line
	//4th: if in segment
	
	return true;
}

