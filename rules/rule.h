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

    static std::string title;
    static std::string description;
    static std::string reminder;
protected:
    Universe* universe;
    bool finished;
    bool won;
};

#endif // RULE_H
