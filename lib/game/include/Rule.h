#ifndef RULE_H
#define RULE_H

#include <map>
#include "json.hpp"

namespace game {

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

#endif