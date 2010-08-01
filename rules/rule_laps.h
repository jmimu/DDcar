#ifndef RULE_LAPS_H
#define RULE_LAPS_H

#include "rule.h"

class Rule_Laps : public Rule
{
public:
    Rule_Laps(int _nbr_laps);
    virtual ~Rule_Laps();
    virtual bool update();//true if something happened

    virtual std::string title();
    virtual std::string description();
    virtual std::string reminder();

private:
    long nbr_laps;
};

#endif // RULE_LAPS_H
