#ifndef RULE_H
#define RULE_H

#include <map>
#include "../interpreter/include/json.hpp"

// Type defenition for ruleContainer struct
struct ruleContainer {
    std::map<std::string, std::string> ruleInformation;
};

// The Rule class is responsible for holding information relevent
// to executing a rule
class Rule {
public:
    Rule();
    Rule(ruleContainer& rule);

    virtual ruleContainer& getRule();
    virtual void setRule(ruleContainer& rule);

protected:
    ruleContainer rule;
};

class GlobalMessageRule : public Rule {
public:
    GlobalMessageRule(ruleContainer& rule);

    ruleContainer& getRule();
    void setRule(ruleContainer& rule);
};

#endif