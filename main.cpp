/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include "car.hpp"
#include "box.hpp"

#include "universe.hpp"
#include "gui.hpp"

static const int32 SCREEN_W = 800;//800;
static const int32 SCREEN_H = 600;//600;


//static const float PI = 3.14159265359;

int main(int argc, char** argv)
{
	// Create main window
	sf::RenderWindow App(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML Shapes");
	App.UseVerticalSync(true);
	
	Universe universe(&App);
	GUI gui(&App);;

	App.SetFramerateLimit(60);
	const sf::Input& Input = App.GetInput();

	while (App.IsOpened())
	{
		sf::Event Event;
		while (App.GetEvent(Event))
		{
		    if (Event.Type == sf::Event::Closed)
		      App.Close();
		    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
		      App.Close();
/*		    if ((Event.Type == sf::Event::MouseWheelMoved))
		    {
				if (Event.MouseWheel.Delta>0)
					camera.set_zoom(camera.get_zoom()*1.1);
				else
					camera.set_zoom(camera.get_zoom()/1.1);
			}*/
		}	
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
		if (!UpKeyDown && !DownKeyDown)
		  {
		    universe.player1->engineSpeed = 0.0;
		  }
		if (!LeftKeyDown && !RightKeyDown)
		  {
		    universe.player1->steeringAngle = 0.0;
		  }

		universe.step();
		
		App.Clear();
		universe.render();

		gui.draw(universe.player1->get_speed());
		
		App.Display();

	}

	return 0;
}
