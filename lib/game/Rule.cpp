#include "include/Rule.h"

using game::Rule;
using game::RuleContainer;
using game::GlobalMessageRule;
using game::Shuffle;
using game::Sort;
using game::Deal;
using game::RuleType;

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer) : ruleType(ruleType), ruleContainer(ruleContainer) {
    
}

void Rule::setRuleContainer(RuleContainer& ruleContainer) {
    this->ruleContainer = ruleContainer;
}

const RuleContainer& Rule::getRuleContainer() const {
    return this->ruleContainer;
}

RuleType Rule::getRuleType() const {
    return this->ruleType;
}

std::string Rule::toString() {
    std::string rule = "";
    for(auto mapElem : ruleContainer.ruleInformation) {
        rule += mapElem.first + ": " + mapElem.second + "\n";
    } 
    
    return rule;
}

RuleType game::matchRuleType(const nlohmann::json& jsonRuleName) {
    if (jsonRuleName == "global-message") {
        return RuleType::GlobalMessage;
    }
    else if(jsonRuleName == "scores") {
        return RuleType::Scores;
    }

    return RuleType::Error;
}
//Shuffle
Shuffle::Shuffle(RuleContainer& rule)
{

}
void Shuffle::shuffleList(listName &list)
{

}

RuleContainer& Shuffle::getRule()
{

}
void Shuffle::setRule(RuleContainer  & rule)
{

}

//Sort 
void Sort::sortList(listName &lis)
{

}
Sort::Sort(RuleContainer& rule)
{

}

RuleContainer& Sort::getRule()
{

}
void Sort::setRule(RuleContainer  & rule)
{

}

//Deal
Deal::Deal(RuleContainer& rule)
{

}

RuleContainer& Deal::getRule()
{

}
void Deal::setRule(RuleContainer  & rule)
{

}
void Deal::dealList(listName From, listName To, Count count)
{
}
