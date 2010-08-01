#ifndef RULES_MANAGER_H
#define RULES_MANAGER_H

#include <string>

#include "rule.h"
//here add your rule header
#include "rule_first.h"

enum rule_type
{
    //here add rule type
    be_first
};

Rule* create_rule(rule_type t);
/*std::string get_rule_title(rule_type t);
std::string get_rule_description(rule_type t);
std::string get_rule_reminder(rule_type t);
*/



#endif // RULES_MANAGER_H
