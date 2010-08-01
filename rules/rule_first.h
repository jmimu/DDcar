#ifndef RULE_FIRST_H
#define RULE_FIRST_H

#include "rule.h"

class Rule_First : public Rule
{
public:
    Rule_First();
    virtual ~Rule_First();
    virtual bool update();//true if something happened


};

#endif // RULE_FIRST_H
