#include "menu.hpp"

#include <sstream>

Menu::Menu(sf::RenderWindow *_App)
: track(""),rule(NULL),nb_cars(1),App(_App),view(sf::FloatRect(-MENU_WIN_W/2, -MENU_WIN_H/2, MENU_WIN_W, MENU_WIN_H))
{
    
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
    nb_cars=15;
    rule=create_rule(be_first);

    Menu_El * el;//current menu element
    el=new Menu_El(App);
    el->entries.push_back(new Menu_Entry(finish_menu,"Play"));
    el->entries.push_back(new Menu_Entry(exit_prog,"Quit"));
    
    

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
					case select_rule:
						break;
					case select_track:
						break;
					case select_stat_pos:
						break;
					case select_nbr_cars:
						break;
					default:
						;
				}
			}
		}
		App->Clear();
		el->show();
		
		App->Display();
		//sleep(1);
	}

    delete el;
    return quit_game;
}


//----------------------------------------------------------------------
Menu_El::Menu_El(sf::RenderWindow *_App)
: entries(),pos(0),App(_App)
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
    for (unsigned int i=0;i<entries.size();i++)
    {
        std::ostringstream oss_entry;
        if ((signed)i==pos) oss_entry<<"=> "; else oss_entry<<"   ";
        oss_entry<<entries.at(i)->text;
        //std::cout<<"Write entry: "<<oss_entry.str()<<std::endl;
        sf::String str_entry;
        str_entry.SetText(oss_entry.str());
        str_entry.SetColor(sf::Color(200, 00, 10,200));
        str_entry.SetPosition(MENU_WIN_W/2-300, MENU_WIN_H/2-250+i*100);
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

