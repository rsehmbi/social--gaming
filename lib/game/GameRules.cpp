#include "include/GameRules.h"

using game::Rule;
using game::GameRules;

GameRules::GameRules() {
}

void GameRules::addRule(Rule& rule) {
    rules.push_back(std::move(rule));
}

const std::vector<Rule>& GameRules::getRules() {
    return rules;
}

std::string GameRules::toString() {
    std::string strRuleList = "";

    for(auto& rule : rules) {
        strRuleList += rule.toString();
    }

    return strRuleList;
}