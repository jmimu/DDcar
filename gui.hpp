//      gui.h
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


#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

#define  GUI_WIN_W  800//800;
#define  GUI_WIN_H  600//600;

class GUI
{
	public:
		GUI(sf::RenderWindow *_App);
		virtual ~GUI();
		void draw(float speed);
		sf::View * get_view(){return &view;} 
		sf::RenderWindow * get_App(){return App;}
	private:
		sf::View view;
		sf::Image counter_img;
		sf::Sprite counter_spr;
		sf::Image hand_img;
		sf::Sprite hand_spr;
		sf::RenderWindow *App;
};

#endif /* GUI_H */ 
