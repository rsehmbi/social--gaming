
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
        Error,
    };

    enum class RuleFields{
        rule,
        list,
        element,
        rules,
        until,
        cases,
        target,
        from,
        to,
        count,
        roles,
        value,
        duration,
        mode,
        flag,
        prompt,
        result,
        score,
        ascending
    };

    using ListName = std::string;
    using Mode = std::string ;
    using VariableName = std::string;
    using Count = int;
    using TimerLength = int;
    using Input = std::string;

    RuleType matchRuleType(const nlohmann::json& jsonRuleName);

    // Type defenition for RuleContaine struct
    struct RuleContainer {
        std::map<RuleFields, std::string> ruleInformation;
        RuleContainer* subRules;

        void add(RuleFields item, std::string value) {
            ruleInformation[item] = value;
        }
    };

    // The Rule class is responsible for holding information relevent
    // to executing a rule
    class Rule {
        public:

            Rule() {
            // This constructor is required to be explicity declared
            // because it is called by the constructors of subclasses
            }

            Rule(RuleType ruleType, RuleContainer& rule);

            RuleType getRuleType() const;
            
            const RuleContainer& getRuleContainer() const;

            void setRuleContainer(RuleContainer& rule);

            static std::unordered_map<RuleFields, std::string> ruleFieldToString;

            // Used for testing and debugging
            std::string toString();

        private:
            RuleType ruleType;
            RuleContainer ruleContainer;

    };
}


