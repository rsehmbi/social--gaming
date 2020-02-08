#include "include/GameRules.h"

GameRules::GameRules() {
}

void GameRules::addRule(Rule& rule) {
    rules.push_back(rule);
}

// Gets game rules based on JSON file
// Calls interpreter to do so
void GameRules::getRulesByConverting(nlohmann::json jsonRules) {

}

// Used for testing only
const std::vector<Rule>& GameRules::getRules() {
    return rules;
}