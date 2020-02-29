#include "include/Rule.h"

using game::Rule;
using game::RuleContainer;
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

    return RuleType::Error;
}