#include "include/Rule.h"

using game::Rule;
using game::RuleContainer;
using game::RuleType;

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer) : ruleType(ruleType), ruleContainer(ruleContainer) {
    
}

void Rule::setRuleContainer(RuleContainer& ruleContainer) {
    this->ruleContainer = ruleContainer;
}

RuleContainer& Rule::getRuleContainer() {
    return this->ruleContainer;
}

RuleType Rule::getRuleType() const {
    return this->ruleType;
}