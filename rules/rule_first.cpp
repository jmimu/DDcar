#include "rule_first.h"


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



