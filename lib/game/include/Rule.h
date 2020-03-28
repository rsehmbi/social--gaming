
#pragma once

#include <map>
#include <variant>
#include "json.hpp"

namespace game {
    
    using ListName = std::string;
    using Mode = std::string ;
    using VariableName = std::string;
    using Count = int;
    using TimerLength = int;
    using Input = std::string;
    using Value = std::variant<std::string, int, bool>;

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
        Foreach,
        ParallelFor,
        When,
        Error,
    };

    enum class RuleField{
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
        ascending,
        timeout,
        choices
    };

    extern std::unordered_map<game::RuleField, std::string> ruleFieldToString;
    extern std::unordered_map<std::string, game::RuleField> stringToRuleField;

    RuleType matchRuleType(const nlohmann::json& jsonRuleName);
    bool isNestedJsonRule(const nlohmann::json& jsonRule);
    bool hasCasesInRule(const nlohmann::json& jsonRule);

    // Type defenition for RuleContainer struct
    struct RuleContainer {
        std::map<RuleField, Value> ruleInformation;

        void add(RuleField item, Value value);
        const Value& get(RuleField item);
        std::string toString();
    };

    // The Rule class is responsible for holding information relevent
    // to executing a rule
    class Rule {
    public:
        struct Case {
            std::variant<std::string, bool> condition;
            std::vector<game::Rule> rules;
            std::string toString();
        };

        Rule();
        Rule(RuleType ruleType, RuleContainer& rule);
        Rule(RuleType ruleType, RuleContainer& rule, std::vector<Rule>& nestedRules);
        Rule(RuleType ruleType, RuleContainer& rule, std::vector<Rule::Case>& cases);

        RuleType getRuleType() const;
        
        const RuleContainer& getRuleContainer() const;
        const std::vector<Rule>& getNestedRules();
        const std::vector<Case>& getCases();

        bool hasNestedRules();
        bool hasCases();

        void setRuleContainer(RuleContainer& rule);

        // Used for testing and debugging
        std::string toString();

    private:
        RuleContainer ruleContainer;
        std::vector<Rule> nestedRules;
        std::vector<Case> cases; 

        RuleType ruleType;

        bool m_hasNestedRules;
        bool m_hasCases;
    };
}