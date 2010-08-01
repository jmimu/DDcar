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

#include "race.hpp"

static const int32 SCREEN_W = 640;//800;
static const int32 SCREEN_H = 480;//600;


//static const float PI = 3.14159265359;

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    // Create main window
    sf::RenderWindow App(sf::VideoMode(SCREEN_W, SCREEN_H), "DDcar"/*, sf::Style::Fullscreen*/);
    App.UseVerticalSync(true);

    App.SetFramerateLimit(60);
    //const sf::Input& Input = App.GetInput();

    //main menu ?
    bool quit_game=false;
    while (!quit_game)
    {
        Race race(&App,"data/track.xml",15);
        if (race.run())
        {
            quit_game=true;
        }
    }
    App.Close();

	return 0;
}
