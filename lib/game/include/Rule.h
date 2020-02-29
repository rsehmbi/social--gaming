
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

    typedef std::string listName;
    typedef int Count;

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

        void shuffleList(listName &list);
        RuleContainer& getRule();
        void setRule(RuleContainer  & rule);
    private:
        listName list;
    };

    // Sorts a list in ascending order
    class Sort: public Rule {
    public:
        Sort(RuleContainer &rule);

        void sortList(listName &list);
        RuleContainer& getRule();
        void setRule(RuleContainer  & rule);
    private:
        listName list;
    };

    class Deal:public Rule {
        Deal (RuleContainer &rule);

        RuleContainer& getRule();
        void setRule(RuleContainer  & rule);
        void dealList(listName From, listName To, Count count);
    private:
        Count count;
        listName From;
        listName To;
    };

}
