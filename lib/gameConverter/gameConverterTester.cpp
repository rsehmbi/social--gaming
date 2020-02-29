#include <iostream>

#include "GameRules.h"
#include "Rule.h"
#include "GameConverter.h"

using game::Rule;
using game::GameRules;
using game::RuleContainer;
using game::GlobalMessageRule;
using gameConverter::GameConverter;

namespace gameConverter {
class gameConverterTester {
public:
  void testConvertGameRules();
  void testConstructRuleContainer();
  void printRules(GameRules rules);

private:

};
}

void 
gameConverter::gameConverterTester::testConvertGameRules() {
  nlohmann::json globalMessage1 = nlohmann::json::array({
    {
      {"rule", "global-message"},
      {"value", "Round {round}. Choose your weapon!"}
    },
    {
      {"rule", "global-message"},
      {"value", "You win!"}
    },

  });

  GameConverter converter;

  GameRules rules = converter.convertGameRules(globalMessage1);

  printRules(rules);
}

void 
gameConverter::gameConverterTester::testConstructRuleContainer() {

}

void 
gameConverter::gameConverterTester::printRules(GameRules rules) {
  auto ruleList = rules.getRules();
    for(auto rule: ruleList) {
        RuleContainer ruleCont = rule.getRuleContainer();
        for(auto mapElem : ruleCont.ruleInformation) {
           std::cout << mapElem.first << " " << mapElem.second << " " << std::endl;
        } 
    }
}

int main() {
  gameConverter::gameConverterTester tester;
  tester.testConvertGameRules();

  return 0;
}