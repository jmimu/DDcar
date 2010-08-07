#ifndef MENU_H
#define MENU_H


#include <string>
#include <SFML/Graphics.hpp>
#include "rules/rules_manager.h"

#define  MENU_WIN_W  800//800;
#define  MENU_WIN_H  600//600;


class Menu_El;
class Menu_Entry;


class Menu
{
    friend class Menu_El;
    friend class Menu_Entry;
public:
    Menu(sf::RenderWindow *_App);
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
    sf::View view;
};

//----------------------------------------------------------------------

class Menu_El //menu screen
{
    friend class Menu;
    friend class Menu_Entry;
public:
    Menu_El(sf::RenderWindow *_App);
    ~Menu_El();
    
    void show();
    void go_up(){if (pos>0) pos--;}
    void go_down(){if (pos<((int)entries.size())-1) pos++;}
    
protected:
    std::vector<Menu_Entry*> entries;
    int pos;
    sf::RenderWindow *App;
};

//----------------------------------------------------------------------

class Menu_Entry //menu screen entry
{
    friend class Menu;
    friend class Menu_El;
public:
    Menu_Entry(std::string _text);
    ~Menu_Entry();
    
protected:
    std::string text;
};

#endif // MENU_H
