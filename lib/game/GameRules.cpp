#include "include/GameRules.h"

using game::Rule;
using game::GameRules;

GameRules::GameRules() {
}

void GameRules::addRule(Rule& rule) {
    rules.push_back(rule);
}

// Gets game rules from JSON file
// Will be moved to a separate convertor class
void GameRules::getRulesByConverting(nlohmann::json jsonRules) {

}

// Used for testing only
const std::vector<Rule>& GameRules::getRules() {
    return rules;
}