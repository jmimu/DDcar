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
        : status(before),universe(_App,track_filename,nbr_cars),App(_App),gui(App),
        Input(App->GetInput()),camera(),rule(NULL),time_to_start(3.0)
{
    camera.set_xy(universe.player1->get_x(),universe.player1->get_y());
    camera.set_zoom(0.20);

    rule=create_rule(be_first);
    rule->set_universe(get_universe());
}


Race::~Race()
{
    delete rule;
}

//return true if asked to quit game
bool Race::run()
{
	bool race_continue=true;
	bool quit_game=false;
	
	//initial cam position
	camera.set_xy(universe.track->x_size()/2,universe.track->y_size()/2);
	camera.set_zoom(0.5);
	
	while (race_continue)
	{
		sf::Event Event;
		while (App->GetEvent(Event))
		{
			if ((Event.Type == sf::Event::Closed) ||
				((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)) )
			{
				race_continue=false;
				quit_game=true;
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F2))
				race_continue=false;
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space))
				system("read f");
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F1))
				universe.player1_autopilote=!universe.player1_autopilote;
		}

		if ((status == before)||(status == start)) introduction();
		else if (status == during) update();
                else if (status == after) if (conclusion()) race_continue=false;

                if ((status == during) && (rule->update()))//rule is completed
                {
                    time_to_start=1;
                    status= after;
                    camera.set_zoom(0.5);
                }

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

        {
            std::ostringstream oss;
            oss<<"Objective: "<<rule->reminder;
            sf::String Hello;
            Hello.SetText(oss.str());
            Hello.SetColor(sf::Color(200, 00, 10,200));
            Hello.SetPosition(-GUI_WIN_W/2+100, -GUI_WIN_H/2+50);
            //Hello.SetPosition(-50,-20);
            Hello.SetSize(50.f);
            App->Draw(Hello);
        }
        if (status == during)
        {

        }
	if (status == before)
	{
		std::ostringstream oss;
		oss<<"Start: "<<(int)(time_to_start+0.99)<<"s";
		sf::String Hello;
		Hello.SetText(oss.str());
		Hello.SetColor(sf::Color(200, 00, 10,200));
		//Hello.SetPosition(0*GUI_WIN_W/2+100, 0*GUI_WIN_H/2+50);
		Hello.SetPosition(-50,-20);
		Hello.SetRotation(15.f);
		Hello.SetSize(200.f);
		App->Draw(Hello);
	}
	if (status == start)
	{
		sf::String Hello;
		Hello.SetText("Go!");
		Hello.SetColor(sf::Color(200, 00, 10,200));
		//Hello.SetPosition(0*GUI_WIN_W/2+100, 0*GUI_WIN_H/2+50);
		Hello.SetPosition(-10,-20);
		Hello.SetRotation(15.f);
		Hello.SetSize(200.f);
		App->Draw(Hello);
	}
        if (status == after)
        {
                sf::String Hello;
                if (rule->is_won())
                {
                    Hello.SetText("Won!");
                }else{
                    Hello.SetText("Lost!");
                }
                Hello.SetColor(sf::Color(200, 00, 10,200));
                //Hello.SetPosition(0*GUI_WIN_W/2+100, 0*GUI_WIN_H/2+50);
                Hello.SetPosition(-10,-20);
                Hello.SetRotation(15.f);
                Hello.SetSize(200.f);
                App->Draw(Hello);
        }
	App->Display();
}

///begining of race (true : race started)
bool Race::introduction()
{
	time_to_start-=1.0/60.0;
	camera.zoom_inertia=1000;
	camera.plani_inertia=100;
	if (time_to_start<2)
	{
		camera.zoom_inertia=500;
		camera.plani_inertia=60;
	}
	if (time_to_start<1)
	{
		camera.zoom_inertia=200;
		camera.plani_inertia=30;
	}
	if (time_to_start<0)
	{
		camera.zoom_inertia=50;
		camera.plani_inertia=10;
		status = start;
	}
	if (time_to_start<-0.3)
	{
		status = during;
	}
	return false;
}

///end of race (true : finished)
bool Race::conclusion()
{
        time_to_start-=1.0/60.0;

        if (time_to_start<0)
        {
                return true;
        }
        return false;
}
