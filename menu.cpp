#include "menu.hpp"

#include <sstream>

Menu::Menu(sf::RenderWindow *_App,sf::Font *_MyFont)
//: track(""),rule(NULL),nb_cars(1),App(_App),MyFont(_MyFont),view(sf::FloatRect(-MENU_WIN_W/2, -MENU_WIN_H/2, MENU_WIN_W, MENU_WIN_H)),back_image(),back_sprite()
: track(""),rule(NULL),nb_cars(1),App(_App),MyFont(_MyFont),view(sf::FloatRect(0, 0, MENU_WIN_W, MENU_WIN_H)),back_image(),back_sprite()
{
    back_image.LoadFromFile("data/title.png");
    back_sprite.SetImage(back_image);
}

Menu::~Menu()
{
    if (rule!=NULL) delete rule;
}



void Menu::create()
{

}

bool Menu::show() //true if quit
{
    App->SetView(view);
    if (rule!=NULL) delete rule;
    track="data/track2.xml";
    nb_cars=1;
    rule=create_rule(laps,10);

    Menu_El * el;//current menu element
    
    
    Menu_El * el_begin=new Menu_El(App,MyFont,"Welcome to DDCar!");
    Menu_El * el_rule=new Menu_El(App,MyFont,"Select rule");
    Menu_El * el_track=new Menu_El(App,MyFont,"Select Track");
    Menu_El * el_nbr_cars=new Menu_El(App,MyFont,"Number of cars");
    //Menu_El * el_start_num=new Menu_El(App);
    Menu_El * el_play=new Menu_El(App,MyFont,"Ready?");

    el_begin->entries.push_back(new Menu_Entry(finish_menu,"Quick!"));
    el_begin->entries.push_back(new Menu_Entry(goto_screen,"New race",el_rule));
    el_begin->entries.push_back(new Menu_Entry(exit_prog,"Quit"));
    
    el_rule->entries.push_back(new Menu_Entry(select_rule,"Be the first",el_track,be_first));
    el_rule->entries.push_back(new Menu_Entry(select_rule,"Make 5 laps",el_track,laps));
    el_rule->entries.push_back(new Menu_Entry(goto_screen,"Previous",el_begin));

    el_track->entries.push_back(new Menu_Entry(select_track,"Track 1",el_nbr_cars,0,"data/track.xml"));
    el_track->entries.push_back(new Menu_Entry(select_track,"Track 2",el_nbr_cars,0,"data/track2.xml"));
    el_track->entries.push_back(new Menu_Entry(goto_screen,"Previous",el_rule));

    el_nbr_cars->entries.push_back(new Menu_Entry(select_nbr_cars,"2 cars",el_play,2));
    el_nbr_cars->entries.push_back(new Menu_Entry(select_nbr_cars,"6 cars",el_play,6));
    el_nbr_cars->entries.push_back(new Menu_Entry(select_nbr_cars,"11 cars",el_play,11));
    el_nbr_cars->entries.push_back(new Menu_Entry(goto_screen,"Previous",el_track));
    
/*    el_start_num->entries.push_back(new Menu_Entry(select_track,"first",el_play,0,"data/track.xml"));
    el_start_num->entries.push_back(new Menu_Entry(select_track,"last",el_play,0,"data/track2.xml"));*/

    el_play->entries.push_back(new Menu_Entry(finish_menu,"Go!"));
    el_play->entries.push_back(new Menu_Entry(goto_screen,"Previous",el_nbr_cars));
    
    el=el_begin;

    bool quit_game=false;
    bool menu_continue=true;
	while (menu_continue)
	{
		sf::Event Event;
		while (App->GetEvent(Event))
		{
			if ((Event.Type == sf::Event::Closed) ||
				((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)) )
			{
				menu_continue=false;
				quit_game=true;
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
				el->go_up();
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
				el->go_down();
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
			{
				switch (el->get_selected_entry()->type)
				{
					case exit_prog:
						menu_continue=false;
						quit_game=true;
						break;
					case finish_menu:
						menu_continue=false;
						quit_game=false;
						break;
					case goto_screen:
						el=el->get_selected_entry()->Menu_El_param;
						break;
					case select_rule:
						delete rule;
						rule=create_rule((rule_type)el->get_selected_entry()->int_param,5);//better to be able to choose nbr laps later
						el=el->get_selected_entry()->Menu_El_param;
						break;
					case select_track:
						track=el->get_selected_entry()->str_param;
						el=el->get_selected_entry()->Menu_El_param;
						break;
					case select_stat_pos:
						break;
					case select_nbr_cars:
						nb_cars=el->get_selected_entry()->int_param;
						el=el->get_selected_entry()->Menu_El_param;
						break;
					default:
						;
				}
                el->pos=0;
			}
		}
		App->Clear();
        App->Draw(back_sprite);
		el->show();
		App->Display();
	}

    delete el_begin;
    delete el_rule;
    delete el_track;
    delete el_nbr_cars;
    //delete el_start_num;
    delete el_play;
    
    return quit_game;
}


//----------------------------------------------------------------------
Menu_El::Menu_El(sf::RenderWindow *_App,sf::Font *_MyFont,std::string _title)
: title(_title),entries(),pos(0),App(_App),MyFont(_MyFont)
{
    
}

Menu_El::~Menu_El()
{
    for (unsigned int i=0;i<entries.size();i++)
    {
        delete entries.at(i);
    }
    entries.clear();
}

void Menu_El::show()
{
	sf::String str_title;
	str_title.SetText(title);
	str_title.SetFont(*MyFont);
	str_title.SetColor(sf::Color(94, 4, 36,255));
	str_title.SetPosition(30, 250);
	str_title.SetSize(60.f);
	App->Draw(str_title);
	
    for (unsigned int i=0;i<entries.size();i++)
    {
        std::ostringstream oss_entry;
        if ((signed)i==pos) oss_entry<<"> "; else oss_entry<<"  ";
        oss_entry<<entries.at(i)->text;
        if ((signed)i==pos) oss_entry<<" <"; else oss_entry<<"  ";
        //std::cout<<"Write entry: "<<oss_entry.str()<<std::endl;
        sf::String str_entry;
        str_entry.SetText(oss_entry.str());
        str_entry.SetFont(*MyFont);
        str_entry.SetColor(sf::Color(94, 4, 36,255));
        if ((signed)i==pos) str_entry.SetColor(sf::Color(94, 4, 66,255));
        str_entry.SetPosition(250, 320+i*60);
        str_entry.SetSize(50.f);
        App->Draw(str_entry);
    }
}

//----------------------------------------------------------------------
Menu_Entry::Menu_Entry(menu_entry_type _type,std::string _text,Menu_El * _Menu_El_param,int _int_param,std::string _str_param)
: text(_text),type(_type),Menu_El_param(_Menu_El_param),int_param(_int_param),str_param(_str_param)
{
    
}

Menu_Entry::~Menu_Entry()
{
    
}

