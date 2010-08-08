#ifndef MENU_H
#define MENU_H


#include <string>
#include <SFML/Graphics.hpp>
#include "rules/rules_manager.h"

#define  MENU_WIN_W  800//800;
#define  MENU_WIN_H  600//600;


class Menu_El;
class Menu_Entry;

//to add : go_back, nbr_laps, ...
enum menu_entry_type
{
    exit_prog=0, //to quit programme
    finish_menu, //to finish menu, and start the race
    goto_screen, //+ Menu_El_param
    select_rule, //+ int_param + Menu_El_param
    select_track, //+ str_param + Menu_El_param
    select_stat_pos, //+ int_param + Menu_El_param
    select_nbr_cars //+ int_param + Menu_El_param
};

//todo : show status ?
class Menu
{
    friend class Menu_El;
    friend class Menu_Entry;
public:
    Menu(sf::RenderWindow *_App,sf::Font *_MyFont);
    ~Menu();
    std::string get_track(){return track;}
    Rule * get_rule(){return rule;}
    int get_nbr_cars(){return nb_cars;}
    
    void create();
    bool show(); //true if quit
    
protected:
    std::string track;
    Rule * rule;
    int nb_cars;
    sf::RenderWindow *App;
    sf::Font *MyFont;
    sf::View view;
    
    sf::Image back_image;
    sf::Sprite back_sprite;

};

//----------------------------------------------------------------------

//todo : add a title...
class Menu_El //menu screen
{
    friend class Menu;
    friend class Menu_Entry;
public:
    Menu_El(sf::RenderWindow *_App,sf::Font *_MyFont,std::string _title);
    ~Menu_El();
    
    void show();
    void go_up(){if (pos>0) pos--;}
    void go_down(){if (pos<((int)entries.size())-1) pos++;}
    Menu_Entry * get_selected_entry(){return entries.at(pos);}
protected:
    std::string title;
    std::vector<Menu_Entry*> entries;
    int pos;
    sf::RenderWindow *App;
    sf::Font *MyFont;
};

//----------------------------------------------------------------------

class Menu_Entry //menu screen entry
{
    friend class Menu;
    friend class Menu_El;
public:
    Menu_Entry(menu_entry_type _type,std::string _text,Menu_El * _Menu_El_param=NULL,int _int_param=0,std::string _str_param="?");
    ~Menu_Entry();
    
protected:
    std::string text;
    menu_entry_type type; //the action
    Menu_El * Menu_El_param;
    int int_param; //the action int param
    std::string str_param; //the action int param
};

#endif // MENU_H
