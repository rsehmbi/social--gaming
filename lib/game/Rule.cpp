#include "include/Rule.h"

using game::Rule;
using game::RuleContainer;
// using game::GlobalMessageRule;
// using game::Shuffle;
// using game::Sort;
// using game::Deal;
using game::RuleType;
// using game::Timer;
// using game::Add;
// using game::InputChoice;
// using game::InputText;
// using game::InputVote;

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer) : ruleType(ruleType), ruleContainer(ruleContainer) {
    
}

std::unordered_map<game::RuleFields, std::string> Rule::ruleFieldToString = {
    {RuleFields::rule, "rule"},
    {RuleFields::value, "value"},
    {RuleFields::score, "score"},
    {RuleFields::ascending, "ascending"},
    {RuleFields::to, "to"},
    {RuleFields::duration, "duration"},
    {RuleFields::mode, "mode"},
};

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
    for(auto& mapElem : ruleContainer.ruleInformation) {
        rule += Rule::ruleFieldToString[mapElem.first] + ": " + mapElem.second + "\n";
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
    else if(jsonRuleName == "timer") {
        return RuleType::Timer;
    }
    else if(jsonRuleName == "add") {
        return RuleType::Add;
    }

    return RuleType::Error;
}

