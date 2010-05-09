//      gui.cpp
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


#include "gui.hpp"


GUI::GUI(sf::RenderWindow *_App)
:view(sf::FloatRect(-GUI_WIN_W/2, -GUI_WIN_H/2, GUI_WIN_W, GUI_WIN_H)),counter_img(),counter_spr(),hand_img(),hand_spr(),App(_App),previous_speed(0.0)
{
	counter_img.LoadFromFile("data/speed120.png");
	counter_spr.SetImage(counter_img);
	hand_img.LoadFromFile("data/speed_hand.png");
	hand_spr.SetImage(hand_img);
	
	counter_spr.SetPosition (GUI_WIN_W-256,GUI_WIN_H-256);
	//counter_spr.SetScale(0.33,0.33);

	hand_spr.SetCenter(5+1, 85);
	hand_spr.SetPosition (GUI_WIN_W-128,GUI_WIN_H-128);
	//hand_spr.SetScale(0.33,0.33);
}


GUI::~GUI()
{
	
}

void GUI::draw(float speed)
{
	previous_speed=previous_speed+(speed-previous_speed)/10;
	
	App->SetView(view);
	
	hand_spr.SetRotation(-2*previous_speed+135);
	App->Draw(counter_spr);
	App->Draw(hand_spr);
}
