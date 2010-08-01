#include "rule_first.h"

/*std::string Rule::title="Be first";
std::string Rule::description="Become first as soon as possible";
std::string Rule::reminder="Become first!";*/

std::string Rule_First::title(){return "Be first";}
std::string Rule_First::description(){return "Become first as soon as possible";}
std::string Rule_First::reminder(){return "Become first!";}


Rule_First::Rule_First():Rule()
{

}

Rule_First::~Rule_First()
{

}

bool Rule_First::update()//true if something happened
{
    if (universe->player1->rank==1)
    {
        finished=true;
        won=true;
        return true;
    }else
        return false;
}



