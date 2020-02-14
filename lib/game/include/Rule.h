#ifndef RULE_H
#define RULE_H

#include <map>
#include "json.hpp"

namespace game {

    // Type defenition for ruleContainer struct
    struct RuleContainer {
        std::map<std::string, std::string> ruleInformation;
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
        GlobalMessageRule(RuleContainer& rule);

        RuleContainer& getRule();
        void setRule(RuleContainer& rule);
    };
}

#endif