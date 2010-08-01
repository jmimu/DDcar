#ifndef RULE_H
#define RULE_H

#include "universe.hpp"

class Rule
{
public:
    Rule();
    virtual ~Rule(){}
    virtual bool update()=0;//true if something happened

    void set_universe(Universe* _universe){universe=_universe;}
    bool is_finished(){return finished;}
    bool is_won(){return won;}

    virtual std::string title()=0;
    virtual std::string description()=0;
    virtual std::string reminder()=0;
protected:
    Universe* universe;
    bool finished;
    bool won;
};

#endif // RULE_H
