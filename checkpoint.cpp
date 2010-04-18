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
#include <Box2D.h>
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
	b2Vec2 car_points0[4];
	car_points0[0].x= car->get_w()/2;car_points0[0].y= car->get_h()/2;
	car_points0[1].x=-car->get_w()/2;car_points0[1].y= car->get_h()/2;
	car_points0[2].x=-car->get_w()/2;car_points0[2].y=-car->get_h()/2;
	car_points0[3].x= car->get_w()/2;car_points0[3].y=-car->get_h()/2;

	float cos_a=cos(car->get_main_body()->body->GetAngle());
	float sin_a=sin(car->get_main_body()->body->GetAngle());

	b2Vec2 car_points[4];
	for (int i=0;i<4;i++)
	  {
	    car_points[i].x= car_points0[i].x * cos_a - car_points0[i].y * sin_a + car->get_x();
	    car_points[i].y= car_points0[i].x * sin_a + car_points0[i].y * cos_a + car->get_y();
	  }


	//std::cout<<car_points[0].x<<" "<<car_points[0].y<<" : "<<car_points[1].x<<" "<<car_points[1].y<<" : "
	//	 <<car_points[2].x<<" "<<car_points[2].y<<" : "<<car_points[3].x<<" "<<car_points[3].y<<std::endl;


	//3rd: if across line
	bool is_negative=false;
	bool is_positive=false;
	float res=0.0;
	for (int i=0;i<4;i++)
	  {
	    res=a*car_points[i].x + b*car_points[i].y + c;
	    if (res<=0) is_negative=true;
	    if (res>=0) is_positive=true;
	  }

	if (is_negative && is_positive) return true;
	else return false;


	//4th: if in segment
	
	//return false;//true;
}

