#include <iostream>

#include "include/GameRules.h"
#include "include/Rule.h"

using game::Rule;
using game::GameRules;
using game::RuleContainer;
using game::GlobalMessageRule;

void testGlobalMessage();

int main() {
    testGlobalMessage();

    return 0;
}

void testGlobalMessage() {
    // Test global message
    nlohmann::json globalMessage1 = {
      {"rule", "global-message"},
      {"value", "Round {round}. Choose your weapon!"}  
        
    };

    nlohmann::json globalMessage2 = {
      {"rule", "global-message"},
      {"value", "Tie game!"}  
    };

    // Create rule containers
    // Conversion will later be handled by a dedicated convertor class
    RuleContainer globalMessageContainer1;
    globalMessageContainer1.ruleInformation.insert(std::pair<std::string, std::string>("rule", "global-message"));
    globalMessageContainer1.ruleInformation.insert(std::pair<std::string, std::string>("value", "Round {round}. Choose your weapon!"));

    RuleContainer globalMessageContainer2;
    globalMessageContainer2.ruleInformation.insert(std::pair<std::string, std::string>("rule", "global-message"));
    globalMessageContainer2.ruleInformation.insert(std::pair<std::string, std::string>("value", "Tie game!"));

    // Create rules using rule containers
    Rule globalMessageRule1(globalMessageContainer1);
    GlobalMessageRule globalMessageRule2(globalMessageContainer2);

    GameRules rules;
    rules.addRule(globalMessageRule1);
    rules.addRule(globalMessageRule2);

    // Print out rules
    auto ruleList = rules.getRules();
    for(auto rule: ruleList) {
        RuleContainer ruleCont = rule.getRule();
        for(auto mapElem : ruleCont.ruleInformation) {
           std::cout << mapElem.first << " " << mapElem.second << " " << std::endl;
        } 
    }
}