#include "include/Rule.h"

using game::Rule;
using game::ruleContainer;
using game::GlobalMessageRule;

Rule::Rule() {
    // This constructor is required to be explicity declared
    // because it is called by the constructors of subclasses
}

Rule::Rule(ruleContainer& rule) : rule(rule) {}

void Rule::setRule(ruleContainer& rule) {
    this->rule = rule;
}

ruleContainer& Rule::getRule() {
    return this->rule;
}

// GlobalMessageRule class
GlobalMessageRule::GlobalMessageRule(ruleContainer& rule) {
    this->rule = rule;
}

void GlobalMessageRule::setRule(ruleContainer& rule) {
    this->rule = rule;
}

ruleContainer& GlobalMessageRule::getRule() {
    return this->rule;
}