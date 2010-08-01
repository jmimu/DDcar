#include "rule_laps.h"

#include <sstream>


/*std::string Rule::title="5 laps";
std::string Rule::description="Make 5 laps as quickly as possible.";
std::string Rule::reminder="Make 5 laps";*/


Rule_Laps::Rule_Laps(int _nbr_laps):Rule(),nbr_laps(_nbr_laps)
{

}

std::string Rule_Laps::title()
{
    std::ostringstream oss;
    oss<<nbr_laps<<" laps";
    return oss.str();
}

std::string Rule_Laps::description()
{
    std::ostringstream oss;
    oss<<"Make "<<nbr_laps<<" laps as quickly as possible.";
    return oss.str();
}

std::string Rule_Laps::reminder()
{
    std::ostringstream oss;
    oss<<"Make "<<nbr_laps<<" laps";
    return oss.str();
}


Rule_Laps::~Rule_Laps()
{

}

bool Rule_Laps::update()//true if something happened
{
    if (universe->player1->nbr_laps>=nbr_laps)
    {
        finished=true;
        won=true;
        return true;
    }else
        return false;
}



