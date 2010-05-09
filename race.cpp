//      race.cpp
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


#include "race.hpp"
#include <iostream>
#include <sstream>

Race::Race(sf::RenderWindow *_App,std::string track_filename,int nbr_cars)
	: App(_App),universe(_App,track_filename,nbr_cars),gui(App),Input(App->GetInput()),camera(),time_to_start(5.0)
{
	camera.set_xy(universe.player1->get_x(),universe.player1->get_y());
	camera.set_zoom(0.20);
}


Race::~Race()
{
	
}

//return true if asked to quit game
bool Race::run()
{
	bool race_continue=true;
	bool quit_game=false;
	
	//initial cam position
	camera.set_xy(universe.track->x_size(),universe.track->y_size());
	camera.set_zoom(0.01);
	
	while (race_continue)
	{
		sf::Event Event;
		while (App->GetEvent(Event))
		{
		    if (Event.Type == sf::Event::Closed)
		    {
		      race_continue=false;
		      quit_game=true;
		    }
		    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
		      race_continue=false;
		    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space))
			system("read f");
		    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F1))
		      universe.player1_autopilote=!universe.player1_autopilote;
		}

		if (introduction())
			update();
		render();
	}

	return quit_game;
}

///cars moving
void Race::update()
{
	bool LeftKeyDown = Input.IsKeyDown(sf::Key::Left);
	bool RightKeyDown = Input.IsKeyDown(sf::Key::Right);
	bool UpKeyDown = Input.IsKeyDown(sf::Key::Up);
	bool DownKeyDown = Input.IsKeyDown(sf::Key::Down);

	if (LeftKeyDown)
	{
		universe.player1->steeringAngle = -universe.player1->MAX_STEER_ANGLE;
	}

	if (RightKeyDown)
	{
		universe.player1->steeringAngle = universe.player1->MAX_STEER_ANGLE;
	}
	
	if (UpKeyDown)
	{
		universe.player1->engineSpeed = -universe.player1->HORSEPOWERS;
	}
	if (DownKeyDown)
	{
		universe.player1->engineSpeed = universe.player1->HORSEPOWERS;
	}
	if (!UpKeyDown && !DownKeyDown && !universe.player1_autopilote)
	{
		universe.player1->engineSpeed = 0.0;
	}
	if (!LeftKeyDown && !RightKeyDown && !universe.player1_autopilote)
	{
		universe.player1->steeringAngle = 0.0;
	}

	universe.step();//IA and dynamics
}

void Race::render()
{
	App->Clear();
	
	App->SetView(*camera.get_view());
	float point_before_player_x=universe.player1->get_x()+sin(universe.player1->get_main_body()->body->GetAngle())*universe.player1->get_speed()/1.5;
	float point_before_player_y=universe.player1->get_y()-cos(universe.player1->get_main_body()->body->GetAngle())*universe.player1->get_speed()/1.5;
	camera.set_target(point_before_player_x,point_before_player_y,universe.player1->get_speed()/10);
	
	universe.render();

	gui.draw(universe.player1->get_speed());


	if (time_to_start>0)
	{
		std::ostringstream oss;
		oss<<"Start: "<<(int)(time_to_start+0.99)<<"s";
		sf::String Hello;
		Hello.SetText(oss.str());
		Hello.SetColor(sf::Color(200, 00, 10,200));
		//Hello.SetPosition(0*GUI_WIN_W/2+100, 0*GUI_WIN_H/2+50);
		Hello.SetPosition(GUI_WIN_W*0.75-50, GUI_WIN_H*0.75-20);
		//Hello.SetRotation(15.f);
		//Hello.SetSize(20.f);
		App->Draw(Hello);
	}

	App->Display();
}

///begining of race (true : race started)
bool Race::introduction()
{
	if (time_to_start<0) return true;
	time_to_start-=1.0/60.0;
	camera.zoom_inertia=200;
	camera.plani_inertia=200;
	
	if (time_to_start<0)
	{
		camera.zoom_inertia=50;
		camera.plani_inertia=10;
	}
	return false;
}
