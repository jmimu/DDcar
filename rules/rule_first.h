#ifndef RULE_FIRST_H
#define RULE_FIRST_H

#include "rule.h"

class Rule_First : public Rule
{
public:
    Rule_First();
    virtual ~Rule_First();
    virtual bool update();//true if something happened


    virtual std::string title(){return "Be first";}
    virtual std::string description(){return "Become first as soon as possible";}
    virtual std::string reminder(){return "Become first!";}
};

#endif // RULE_FIRST_H
