#ifndef RULE_H
#define RULE_H

#include <map>
#include "json.hpp"

namespace game {

    // Type defenition for ruleContainer struct
    struct RuleContainer {
        std::map<std::string, std::string> ruleInformation;
        RuleContainer* subRules;

        void add(std::string item, std::string value) {
            ruleInformation[item] = value;
        }
    };

    // The Rule class is responsible for holding information relevent
    // to executing a rule
    class Rule {
    public:
        Rule();
        Rule(RuleContainer& rule);

        virtual RuleContainer& getRule();
        virtual void setRule(RuleContainer& rule);

    protected:
        RuleContainer rule;
    };

    class GlobalMessageRule : public Rule {
    public:
        GlobalMessageRule();
        GlobalMessageRule(RuleContainer& rule);

        RuleContainer& getRule();
        void setRule(RuleContainer& rule);
    };
}

#endif