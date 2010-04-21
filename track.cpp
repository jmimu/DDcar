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

Track::Track(b2World &world,std::string track_file,int _tile_size)
: walls(),tile_size(_tile_size),trajectory(),checkpoints(),TRACK_PIXEL_PER_UNIT(1),GROUND_PIXEL_PER_UNIT(1)
{
	std::string img_filename;
	std::string gnd_img_filename;
	
	//read xml file
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
			
			//track version
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
			
			//track name
			TiXmlElement* track_name = root->FirstChildElement("name");
			if ( !track_name )
				throw std::string( "Unable to find 'name' node !" );
			std::cout<<"Track name: "<<track_name->GetText()<<std::endl;
			
			
			//background_image
			TiXmlElement* track_background_image = root->FirstChildElement("background_image");
			if ( !track_background_image )
				throw std::string( "Unable to find 'background_image' node !" );
				TiXmlElement* track_background_image_filename = track_background_image->FirstChildElement("filename");
				if ( !track_background_image_filename )
					throw std::string( "Unable to find 'track_background_image>filename' node !" );
				TiXmlElement* track_background_image_dpi = track_background_image->FirstChildElement("dpi");
				if ( !track_background_image_dpi )
					throw std::string( "Unable to find 'track_background_image>dpi' node !" );
				std::cout<<"Track background_image: "<<track_background_image_filename->GetText()
					<<" @ "<<atof(track_background_image_dpi->GetText())<<" pix/B2Dunit"<<std::endl;
				img_filename=track_background_image_filename->GetText();
				TRACK_PIXEL_PER_UNIT=atof(track_background_image_dpi->GetText());
			
			//background_image
			TiXmlElement* track_ground_nature_image = root->FirstChildElement("ground_nature_image");
			if ( !track_ground_nature_image )
				throw std::string( "Unable to find 'ground_nature_image' node !" );
				TiXmlElement* track_ground_nature_image_filename = track_ground_nature_image->FirstChildElement("filename");
				if ( !track_ground_nature_image_filename )
					throw std::string( "Unable to find 'track_ground_nature_image>filename' node !" );
				TiXmlElement* track_ground_nature_image_dpi = track_ground_nature_image->FirstChildElement("dpi");
				if ( !track_ground_nature_image_dpi )
					throw std::string( "Unable to find 'track_ground_nature_image>dpi' node !" );
				std::cout<<"Track ground_nature_image: "<<track_ground_nature_image_filename->GetText()
					<<" @ "<<atof(track_ground_nature_image_dpi->GetText())<<" pix/B2Dunit"<<std::endl;
				gnd_img_filename=track_ground_nature_image_filename->GetText();
				GROUND_PIXEL_PER_UNIT=atof(track_ground_nature_image_dpi->GetText());
			
			//read walls
			TiXmlElement* walls_el = root->FirstChildElement("walls");
			if ( !walls_el )
				throw std::string( "Unable to find 'walls' node !" );
			
			TiXmlElement* walls_wall_el = walls_el->FirstChildElement("wall");
			if ( !walls_wall_el )
				throw std::string( "Unable to find 'walls>wall' node !" );
			walls.clear();
			while (walls_wall_el)
			{
				TiXmlElement* wall_x_el = walls_wall_el->FirstChildElement("x_center");
				if ( !wall_x_el )
					throw std::string( "Unable to find 'walls>wall>x_center' node !" );
				TiXmlElement* wall_y_el = walls_wall_el->FirstChildElement("y_center");
				if ( !wall_y_el )
					throw std::string( "Unable to find 'walls>wall>y_center' node !" );
				TiXmlElement* wall_h_el = walls_wall_el->FirstChildElement("height");
				if ( !wall_h_el )
					throw std::string( "Unable to find 'walls>wall>height' node !" );
				TiXmlElement* wall_w_el = walls_wall_el->FirstChildElement("width");
				if ( !wall_w_el )
					throw std::string( "Unable to find 'walls>wall>width' node !" );
				TiXmlElement* wall_a_el = walls_wall_el->FirstChildElement("angle");
				if ( !wall_a_el )
					throw std::string( "Unable to find 'walls>wall>angle' node !" );
				
				walls.push_back(new Box(world,atof(wall_x_el->GetText()), atof(wall_y_el->GetText()),
					atof(wall_h_el->GetText()), atof(wall_w_el->GetText()),atof(wall_a_el->GetText()),sf::Color::Blue,NULL,0.0,false)); //left
				walls_wall_el = walls_wall_el->NextSiblingElement("wall");
			}
			std::cout<<"walls: "<<walls.size()<<std::endl;
			
			
			//read starting positions
			TiXmlElement* start_el = root->FirstChildElement("coord_departure");
			if ( !start_el )
				throw std::string( "Unable to find 'coord_departure' node !" );
			
			TiXmlElement* start_car_el = start_el->FirstChildElement("car");
			if ( !start_car_el )
				throw std::string( "Unable to find 'coord_departure>car' node !" );

			while (start_car_el)
			{
				TiXmlElement* start_car_x_el = start_car_el->FirstChildElement("x");
				if ( !start_car_x_el )
					throw std::string( "Unable to find 'coord_departure>car>x' node !" );
				TiXmlElement* start_car_y_el = start_car_el->FirstChildElement("y");
				if ( !start_car_y_el )
					throw std::string( "Unable to find 'coord_departure>car>y' node !" );
				TiXmlElement* start_car_a_el = start_car_el->FirstChildElement("a");
				if ( !start_car_a_el )
					throw std::string( "Unable to find 'coord_departure>car>a' node !" );
				
				b2Vec2 pt;
				pt.x=atof(start_car_x_el->GetText());
				pt.y=atof(start_car_y_el->GetText());
				starting_pos.push_back(pt);
				starting_angle.push_back(atof(start_car_a_el->GetText()));
				start_car_el = start_car_el->NextSiblingElement("car");
			}
			std::cout<<"starting positions: "<<starting_pos.size()<<std::endl;
			
			
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
			
			//read checkpoints
			TiXmlElement* checkpoints_el = root->FirstChildElement("checkpoints");
			if ( !checkpoints_el )
				throw std::string( "Unable to find 'checkpoints' node !" );
			
			TiXmlElement* checkpoints_checkpoint_el = checkpoints_el->FirstChildElement("checkpoint");
			if ( !checkpoints_checkpoint_el )
				throw std::string( "Unable to find 'checkpoints>checkpoint' node !" );
			checkpoints.clear();
			while (checkpoints_checkpoint_el)
			{
				TiXmlElement* checkpoint_x1_el = checkpoints_checkpoint_el->FirstChildElement("x1");
				if ( !checkpoint_x1_el )
					throw std::string( "Unable to find 'checkpoints>checkpoint>x1' node !" );
				TiXmlElement* checkpoint_y1_el = checkpoints_checkpoint_el->FirstChildElement("y1");
				if ( !checkpoint_y1_el )
					throw std::string( "Unable to find 'checkpoints>checkpoint>y1' node !" );
				TiXmlElement* checkpoint_x2_el = checkpoints_checkpoint_el->FirstChildElement("x2");
				if ( !checkpoint_x2_el )
					throw std::string( "Unable to find 'checkpoints>checkpoint>x2' node !" );
				TiXmlElement* checkpoint_y2_el = checkpoints_checkpoint_el->FirstChildElement("y2");
				if ( !checkpoint_y2_el )
					throw std::string( "Unable to find 'checkpoints>checkpoint>y2' node !" );
				
				checkpoints.push_back(new Checkpoint(atof(checkpoint_x1_el->GetText()),atof(checkpoint_y1_el->GetText()),
													atof(checkpoint_x2_el->GetText()),atof(checkpoint_y2_el->GetText())));
				checkpoints_checkpoint_el = checkpoints_checkpoint_el->NextSiblingElement("checkpoint");
			}
			std::cout<<"checkpoints: "<<checkpoints.size()<<std::endl;
			
			std::cout << "File " << track_file << " is valid ..." << std::endl;
		}
		catch(const std::string& s)
		{
			std::cerr<<s<<"\n";
		}
	}
	
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
	
	std::cout<<"Loading ground image..."<<std::endl;
	//ground nature image
	if (!ground_nature.LoadFromFile(gnd_img_filename))
		std::cout<<"ERROR! Ground nature image not found: "<<img_filename<<std::endl;
	

	//tire mark image
	//tire_mark_image.LoadFromFile("data/tire_mark.png");

	//swich on first checkpoint
	checkpoints.at(0)->set_switched_on(true);
}

void Track::aff(sf::RenderWindow *_App)
{
	sf::View _view=_App->GetView();
	//ground
	
	
	for (int y=0;y<nbr_tiles_y;y++)
		for (int x=0;x<nbr_tiles_x;x++)
		{
			if (( fabs((tiles_spr[x+nbr_tiles_x*y]->GetPosition().x+tile_size/2)-_view.GetCenter().x)< _view.GetHalfSize().x+tile_size/2)
				&& ( fabs((tiles_spr[x+nbr_tiles_x*y]->GetPosition().y+tile_size/2)-_view.GetCenter().y)< _view.GetHalfSize().y+tile_size/2) )
                                _App->Draw(*tiles_spr[x+nbr_tiles_x*y]);
		}
	
	
	//checkpoints
	for (unsigned int i=0;i<checkpoints.size();i++)
		checkpoints.at(i)->aff(_App);

/*
	//tire marks
	std::deque<b2Vec2>::iterator iter1 = tire_marks.begin();
	while( iter1 != tire_marks.end())
	  {
	    b2Vec2* pos=&(*iter1);
	    if ( (fabs(pos->x-_view.GetCenter().x)< _view.GetHalfSize().x)
		 && (fabs(pos->y-_view.GetCenter().y)< _view.GetHalfSize().y) )
	      {

		sf::Sprite spr(tire_mark_image);
		spr.SetCenter(tire_mark_image.GetWidth()/2,tire_mark_image.GetHeight()/2);
		spr.SetScale(0.1,0.1);
		spr.SetPosition (pos->x ,pos->y);
		_App->Draw(spr);
	      }
	    ++iter1;
	  }
*/
}

//change the pixel in the background image
void Track::add_pixel(float x,float y,sf::Color c)
{
	x*=TRACK_PIXEL_PER_UNIT;
	y*=TRACK_PIXEL_PER_UNIT;
	//std::cout<<"try to add at "<<x<<" "<<y<<" "<<tile_size*nbr_tiles_x<<" "<<tile_size*nbr_tiles_y<<std::endl;
	if ((x<0)||(x>=tile_size*nbr_tiles_x)||(y<0)||(y>=tile_size*nbr_tiles_y))
	{
		//std::cout<<"no."<<std::endl;
		return;
	}
	int tile_x=x/tile_size;
	int tile_y=y/tile_size;
	int offset_x=(int)x % tile_size;
	int offset_y=(int)y % tile_size;
	//std::cout<<"=> "<<tile_x<<" "<<tile_y<<" "<<offset_x<<" "<<offset_y<<std::endl;
	
	//smooth
	sf::Color previous=tiles_img[tile_x+nbr_tiles_x*tile_y]->GetPixel(offset_x,offset_y);
	sf::Color next(previous.r+(c.r-previous.r)/4,previous.g+(c.g-previous.g)/4,previous.b+(c.b-previous.b)/4,255);
	tiles_img[tile_x+nbr_tiles_x*tile_y]->SetPixel(offset_x,offset_y,next);
}

sf::Color Track::get_ground_nature(float x, float y)
{
	int _x=x*GROUND_PIXEL_PER_UNIT;
	int _y=y*GROUND_PIXEL_PER_UNIT;
	if ((_x<0) || (_x>=ground_nature.GetWidth()) || (_y<0) || (_y>=ground_nature.GetHeight()) )
		return sf::Color(0,0,0);
	return ground_nature.GetPixel(_x,_y);  
}


