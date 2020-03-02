
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

    typedef std::string ListName;
    typedef std::string Mode;
    typedef std::string VariableName;
    typedef int Count;
    typedef int TimerLength;
    typedef std::string Input;


    // Type defenition for RuleContaine struct
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

        Rule() {
    // This constructor is required to be explicity declared
    // because it is called by the constructors of subclasses
        }

        Rule(RuleType ruleType, RuleContainer& rule);

        RuleType getRuleType() const;
        
        RuleContainer& getRuleContainer();

        void setRuleContainer(RuleContainer& rule);

    private:
        RuleContainer ruleContainer;

        RuleType ruleType;
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
        void setRule(RuleContainer& rule);
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
        void setRule(RuleContainer& rule);
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
        void setRule(RuleContainer& rule);
    private:
        Input to;
        Input prompt;
        Input vhoices;
        Input result;
        Count timeout;
    };
}
