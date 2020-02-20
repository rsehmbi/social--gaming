#include "include/Rule.h"

using game::Rule;
using game::RuleContainer;
using game::GlobalMessageRule;

Rule::Rule() {
    // This constructor is required to be explicity declared
    // because it is called by the constructors of subclasses
}

Rule::Rule(RuleContainer& rule) : rule(rule) {}

void Rule::setRule(RuleContainer& rule) {
    this->rule = rule;
}

RuleContainer& Rule::getRule() {
    return this->rule;
}

// GlobalMessageRule class
GlobalMessageRule::GlobalMessageRule() {
    
}

GlobalMessageRule::GlobalMessageRule(RuleContainer& rule) {
    this->rule = rule;
}

void GlobalMessageRule::setRule(RuleContainer& rule) {
    this->rule = rule;
}

RuleContainer& GlobalMessageRule::getRule() {
    return this->rule;
}