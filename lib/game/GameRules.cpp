#include "include/GameRules.h"

using game::Rule;
using game::GameRules;

GameRules::GameRules() {
}

void GameRules::addRule(Rule& rule) {
    rules.push_back(rule);
}

// Used for testing only
const std::vector<Rule>& GameRules::getRules() {
    return rules;
}