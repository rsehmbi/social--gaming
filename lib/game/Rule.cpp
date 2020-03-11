#include "include/Rule.h"

using game::Rule;
using game::RuleContainer;
using game::GlobalMessageRule;
using game::Shuffle;
using game::Sort;
using game::Deal;
using game::RuleType;
using game::Timer;
using game::Add;
using game::InputChoice;
using game::InputText;
using game::InputVote;

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer) : ruleType(ruleType), ruleContainer(ruleContainer) {
    hasNestedRules = false;
}

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer, std::vector<Rule>& nestedRules) : 
ruleType(ruleType), ruleContainer(ruleContainer), nestedRules(nestedRules)  {
    hasNestedRules = true;
}

void Rule::setRuleContainer(RuleContainer& ruleContainer) {
    this->ruleContainer = ruleContainer;
}

RuleType Rule::getRuleType() const {
    return this->ruleType;
}

const RuleContainer& Rule::getRuleContainer() const {
    return this->ruleContainer;
}

const std::vector<Rule>& Rule::getNestedRules() {
    assert(hasNestedRules);
    return nestedRules;
}

std::string Rule::toString() {
    std::string ruleStr = ruleContainer.toString();
    
    if(hasNestedRules) {
        ruleStr += "rules: \n{\n";
        for(auto& rule : nestedRules) {
            ruleStr += rule.toString();
        }
        ruleStr += "}\n";
    }
    
    return ruleStr;
}

RuleType game::matchRuleType(const nlohmann::json& jsonRuleName) {
    if (jsonRuleName == "global-message") {
        return RuleType::GlobalMessage;
    }
    else if(jsonRuleName == "scores") {
        return RuleType::Scores;
    }
    else if(jsonRuleName == "timer") {
        return RuleType::Timer;
    }
    else if(jsonRuleName == "add") {
        return RuleType::Add;
    }
    else if(jsonRuleName == "foreach") {
        return RuleType::Foreach;
    }
    else if(jsonRuleName == "parallelfor") {
        return RuleType::ParallelFor;
    }
    else if(jsonRuleName == "input-choice") {
        return RuleType::InputChoice;
    }
    else if(jsonRuleName == "discard") {
        return RuleType::Discard;
    }
    else if(jsonRuleName == "when") {
        return RuleType::When;
    }
    else if(jsonRuleName == "extend") {
        return RuleType::Extend;
    }

    return RuleType::Error;
}

bool game::isNestedJsonRule(const nlohmann::json& jsonRule) {
    auto it = std::find_if(jsonRule.items().begin(), jsonRule.items().end(), 
        [] (auto& jsonRule) { 
            return jsonRule.key() == "rules";
        }
    );

    bool isNested = (it != jsonRule.items().end());
    return isNested;
}

//Shuffle
Shuffle::Shuffle(RuleContainer& rule)
{

}

RuleContainer& Shuffle::getRule()
{

}

//Sort 
Sort::Sort(RuleContainer& rule)
{

}

RuleContainer& Sort::getRule()
{

}


//Deal
Deal::Deal(RuleContainer& rule)
{

}

RuleContainer& Deal::getRule()
{

}


//Timer
Timer::Timer(RuleContainer& rule) 
{

}
RuleContainer& Timer::getRule()
{

}

//Add
Add::Add(RuleContainer& rule) 
{

}
RuleContainer& Add::getRule()
{

}

//InputChoice
InputChoice::InputChoice(RuleContainer& rule) 
{}

RuleContainer& InputChoice::getRule()
{}

//InputText
InputText::InputText(RuleContainer& rule) 
{}

RuleContainer& InputText::getRule()
{}

//InputVote
InputVote::InputVote(RuleContainer& rule) 
{}

RuleContainer& InputVote::getRule()
{}

