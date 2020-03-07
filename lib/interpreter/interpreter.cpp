#include "interpreter.h"

using interpreter::Interpreter;
using game::GameState;
using game::RuleContainer;

void Interpreter::executeGlobalMessageRule(Rule rule) {
    GameState newState;

    RuleContainer ruleContainer = rule.getRuleContainer();
    std::string value = ruleContainer.get("value");

    // TO DO: Pass message to GameSession
}

void executeMessageRule(Rule rule) {
    // TO DO: Need to ask for example of a Message rule
}