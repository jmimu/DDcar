//      race.hpp
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


#ifndef RACE_HPP
#define RACE_HPP

#include <SFML/Graphics.hpp>
#include "universe.hpp"
#include "gui.hpp"
#include "camera.hpp"
#include "rules/rule.h"
#include "rules/rules_manager.h"

enum race_status
{
	before,start,during,after
};

/**
 * A Race is the universe + gui + input
 * + race data : ranking, nbr of laps, begin/end...
 * 
 * */
class Race
{
    public:
        Race(sf::RenderWindow *_App,std::string track_filename,int nbr_cars=10);
        virtual ~Race();
        bool run();
        Universe * get_universe(){return &universe;}
    private:
        race_status status;

        Universe universe;
        sf::RenderWindow *App;
        GUI gui;
        const sf::Input& Input;
        Camera camera;
        long total_time;

        Rule * rule;

        void update();
        void render();
        bool introduction();//begining of race
        bool conclusion();//end of race
        double time_to_start;
};

#endif /* RACE_HPP */ 


