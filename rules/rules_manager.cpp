#include "rules_manager.h"

Rule* create_rule(rule_type t)
{
    Rule* r=NULL;
    switch (t)
    {
        //here add your rule constructor
        case be_first:
            r=new Rule_First();
    }
    return r;
}
/*
std::string get_rule_title(rule_type t)
{

}

std::string get_rule_description(rule_type t)
{

}

std::string get_rule_reminder(rule_type t)
{

}
*/
