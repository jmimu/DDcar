#ifndef RULES_MANAGER_H
#define RULES_MANAGER_H

#include <string>

#include "rule.h"
//here add your rule header
#include "rule_first.h"
#include "rule_laps.h"

enum rule_type
{
    //here add rule type
    be_first,laps
};

Rule* create_rule(rule_type t,int option1=1);




#endif // RULES_MANAGER_H
