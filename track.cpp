//      track.cpp
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


#include "track.hpp"

#include <iostream>
#include <sstream>
#include "tinyxml/tinyxml.h"


#define XML_VERSION "0.1"

Track::Track(b2World &world,std::string img_filename,std::string gnd_img_filename,int _tile_size)
: walls(),tile_size(_tile_size),trajectory()
{
	//read xml file
	std::string track_file="data/track.xml";
	TiXmlDocument doc( track_file.c_str() );
	bool loadOkay = doc.LoadFile();
	if ( !loadOkay )
	{
		std::cout<<"Could not load test xml file. Error='"<<doc.ErrorDesc()<<"'. Exiting.\n";
	}
	else
	{
		std::cout<<"XML file OK"<<std::endl;
		
		TiXmlHandle hDoc( &doc );
		TiXmlElement* root;
		try{
			// check that we have "track" root node...
			// ... and that version is XML_VERSION
				root = doc.FirstChildElement( "track" );
				
				if ( !root )
					throw std::string( "Unable to find track root node !" );
				std::string rootNode( root->Value() );
				if ( rootNode != "track" )
					throw std::string( "Root node MUST be 'track' !" );
				
				TiXmlElement* version = root->FirstChildElement("version");
				if ( !version )
					throw std::string( "Unable to find 'version' node !" );
				std::string versionNode( version->GetText() );
				if ( versionNode != XML_VERSION )
				{
					std::ostringstream oss;
					oss << "'version' MUST be '"<<XML_VERSION<<"' ! Value is '" << versionNode << "'." << std::endl;
					throw std::string( oss.str() );
				}
				
				TiXmlElement* track_name = root->FirstChildElement("name");
				if ( !track_name )
					throw std::string( "Unable to find 'name' node !" );
				std::cout<<"Track name: "<<track_name->GetText()<<std::endl;
				
				//read trajectory
				TiXmlElement* traj_el = root->FirstChildElement("trajectory");
				if ( !traj_el )
					throw std::string( "Unable to find 'trajectory' node !" );
				
				TiXmlElement* traj_pt_el = traj_el->FirstChildElement("point");
				if ( !traj_pt_el )
					throw std::string( "Unable to find 'trajectory>point' node !" );
				trajectory.clear();
				while (traj_pt_el)
				{
					TiXmlElement* traj_pt_x_el = traj_pt_el->FirstChildElement("x");
					if ( !traj_pt_x_el )
						throw std::string( "Unable to find 'trajectory>point>x' node !" );
					TiXmlElement* traj_pt_y_el = traj_pt_el->FirstChildElement("y");
					if ( !traj_pt_y_el )
						throw std::string( "Unable to find 'trajectory>point>y' node !" );
					
					b2Vec2 pt;
					pt.x=atof(traj_pt_x_el->GetText());
					pt.y=atof(traj_pt_y_el->GetText());
					trajectory.push_back(pt);
					traj_pt_el = traj_pt_el->NextSiblingElement("point");
				}
				std::cout<<"Trajectory: "<<trajectory.size()<<std::endl;
				
				std::cout << "File " << track_file << " is valid ..." << std::endl;
			}
		catch(const std::string& s)
		{
			std::cerr<<s<<"\n";
		}
	}
	
	//create walls
	walls.push_back(new Box(world,0.0f, 250.0f,500.0f, 1.0f,1.5708,sf::Color::Blue,NULL,0.0,false)); //left
	walls.push_back(new Box(world,250.0f, 500.0f,500.0f, 1.0f,0,sf::Color::Blue,NULL,0.0,false)); //down
	walls.push_back(new Box(world,250.0f, 0.0f,500.0f, 1.0f,0,sf::Color::Blue,NULL,0.0,false)); //up
	walls.push_back(new Box(world,500.0f, 250.0f,500.0f, 1.0f,1.5708,sf::Color::Blue,NULL,0.0,false));	//right
	
	std::cout<<"Loading track image..."<<std::endl;
	sf::Image image_full;
	if (!image_full.LoadFromFile(img_filename))
		std::cout<<"ERROR! Image not found: "<<img_filename<<std::endl;
	int image_full_w=image_full.GetWidth();
	int image_full_h=image_full.GetHeight();
	nbr_tiles_x=(image_full_w-1)/tile_size+1;//+1 not full
	nbr_tiles_y=(image_full_h-1)/tile_size+1;
	
	//image must be N*tile_size
	for (int y=0;y<nbr_tiles_y;y++)
		for (int x=0;x<nbr_tiles_x;x++)
		{
			sf::Image * img=new sf::Image();
			img->Create(tile_size,tile_size);
			img->Copy(image_full,0,0,sf::IntRect(tile_size*x, tile_size*y, tile_size*(x+1), tile_size*(y+1)),true);
			img->SetSmooth(false);
			tiles_img.push_back(img);
		}
	
	for (int y=0;y<nbr_tiles_y;y++)
		for (int x=0;x<nbr_tiles_x;x++)
		{
			sf::Sprite * spr=new sf::Sprite();
			spr->SetPosition(float(tile_size*x)/TRACK_PIXEL_PER_UNIT, float(tile_size*y)/TRACK_PIXEL_PER_UNIT); //? //scale ? TRACK_PIXEL_PER_UNIT
			spr->SetImage(*tiles_img[x+nbr_tiles_x*y]);
			spr->SetScale(1.0/TRACK_PIXEL_PER_UNIT,1.0/TRACK_PIXEL_PER_UNIT);
			tiles_spr.push_back(spr);
		}
	
	//ground nature image
	if (!ground_nature.LoadFromFile(gnd_img_filename))
		std::cout<<"ERROR! Ground nature image not found: "<<img_filename<<std::endl;
}

void Track::aff(sf::RenderWindow *_App)
{
	sf::View _view=_App->GetView();
	
	for (int y=0;y<nbr_tiles_y;y++)
		for (int x=0;x<nbr_tiles_x;x++)
		{
			if (( fabs((tiles_spr[x+nbr_tiles_x*y]->GetPosition().x+tile_size/2)-_view.GetCenter().x)< _view.GetHalfSize().x+tile_size/2)
				&& ( fabs((tiles_spr[x+nbr_tiles_x*y]->GetPosition().y+tile_size/2)-_view.GetCenter().y)< _view.GetHalfSize().y+tile_size/2) )
				_App->Draw(*tiles_spr[x+nbr_tiles_x*y]);
		}
}

sf::Color Track::get_ground_nature(float x, float y)
{
	int _x=x*GROUND_PIXEL_PER_UNIT;
	int _y=y*GROUND_PIXEL_PER_UNIT;
	if ((_x<0) || (_x>=ground_nature.GetWidth()) || (_y<0) || (_y>=ground_nature.GetHeight()) )
		return sf::Color(0,0,0);
	return ground_nature.GetPixel(_x,_y);  
}


