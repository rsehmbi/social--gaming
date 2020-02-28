
#pragma once

#include <map>
#include "json.hpp"

namespace game {
    
    enum class RuleType {
        GlobalMessage,
        Extend,
        Reverse,
        Shuffle,
        Sort,
        Deal,
        Discard,
        ListAttributes,
        Add,
        NumericalAttributes,
        Timer,
        InputChoice,
        InputText,
        InputVote,
        Message,
        Scores,
    };

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
        Rule(RuleType ruleType, RuleContainer& rule);

        RuleType getRuleType() const;
        
        RuleContainer& getRuleContainer() const;

        void setRuleContainer(RuleContainer& rule);

    private:
        RuleContainer ruleContainer;

        RuleType ruleType;
    };

}
