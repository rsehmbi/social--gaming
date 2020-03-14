
#pragma once

#include <map>
#include <variant>
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
        Foreach,
        ParallelFor,
        When,
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
    using Value = std::variant<std::string, int, bool>;

    RuleType matchRuleType(const nlohmann::json& jsonRuleName);
    bool isNestedJsonRule(const nlohmann::json& jsonRule);

    // Type defenition for RuleContaine struct
    struct RuleContainer {
        std::map<std::string, std::variant<std::string, int, bool>> ruleInformation;
        
        void add(std::string item, Value value) {
            ruleInformation[item] = value;
        }

        std::string toString() {
            std::string str = "";
            for(auto& mapElem : ruleInformation) {
                str += mapElem.first + ": " + std::get<std::string>(mapElem.second) + "\n";
            }
            
            return str;
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
        Rule(RuleType ruleType, RuleContainer& rule, std::vector<Rule>& nestedRules);

        RuleType getRuleType() const;
        
        const RuleContainer& getRuleContainer() const;
        const std::vector<Rule>& getNestedRules();

        void setRuleContainer(RuleContainer& rule);

        // Used for testing and debugging
        std::string toString();

    private:
        RuleContainer ruleContainer;
        std::vector<Rule> nestedRules;

        RuleType ruleType;

        bool hasNestedRules;
    };

    class GlobalMessageRule : public Rule {
    public:
        GlobalMessageRule(RuleContainer& rule);

        RuleContainer& getRule();
        void setRule(RuleContainer& rule);
    };

    class Shuffle: public Rule {
    public:
        Shuffle(RuleContainer& rule);

        void shuffleList(ListName& list);
        RuleContainer& getRule();
        void setRule(RuleContainer& rule);
    private:
        ListName list;
    };

    // Sorts a list in ascending order
    class Sort: public Rule {
    public:
        Sort(RuleContainer &rule);

        void sortList(ListName& list);
        RuleContainer& getRule();
        void setRule(RuleContainer& rule);
    private:
        ListName list;
    };

    class Deal:public Rule {
        Deal (RuleContainer& rule);

        RuleContainer& getRule();
        void setRule(RuleContainer& rule);
        void dealList(ListName From, ListName To, Count count);
    private:
        Count count;
        ListName From;
        ListName To;
    };

    class Timer: public Rule {
    public:
        Timer(RuleContainer& rule);
        RuleContainer& getRule();
        void setRule(RuleContainer& rule);
    private:
        TimerLength timeLength;
        Mode mode;
        RuleContainer ruleContainer;
        RuleType ruleType;
    };

    class Add: public Rule {
    public:
        Add(RuleContainer& rule);
        RuleContainer& getRule();
        void setRule(RuleContainer& rule);
    private:
        VariableName to;
        VariableName value;
        RuleContainer ruleContainer;
        RuleType ruleType;
    };
    
    class InputChoice: public Rule {
    public:
        InputChoice(RuleContainer& rule);
        RuleContainer& getRule();
        //void setRule(RuleContainer& rule);
    private:
        Input to;
        Input prompt;
        Input choices;
        Input result;
        Count timeout;
    };

    class InputText: public Rule {
    public:
        InputText(RuleContainer& rule);
        RuleContainer& getRule();
        //void setRule(RuleContainer& rule);
    private:
        Input to;
        Input prompt;
        Input result;
        Count timeout;
    };

    class InputVote: public Rule {
    public:
        InputVote(RuleContainer& rule);
        RuleContainer& getRule();
        //void setRule(RuleContainer& rule);
    private:
        Input to;
        Input prompt;
        Input choices;
        Input result;
        Count timeout;
    };
}
