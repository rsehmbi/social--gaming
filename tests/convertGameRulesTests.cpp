#include "gtest/gtest.h"
#include "GameConverter.h"

using game::Rule;
using game::GameRules;
using game::RuleContainer;
using gameConverter::GameConverter;

namespace gameConverter{
class ConvertGameRulesTest : public ::testing::Test {
public:
    GameRules convertGameRules(const nlohmann::json& jsonRules) {
        return converter.convertGameRules(jsonRules);
    };

private:
    GameConverter converter;

};

void printRules(GameRules rules) {
    auto ruleList = rules.getRules();
    for(auto rule: ruleList) {
        RuleContainer ruleCont = rule.getRuleContainer();
        for(auto mapElem : ruleCont.ruleInformation) {
           std::cout << mapElem.first << " " << mapElem.second << " " << std::endl;
        } 
    }
}

TEST_F(ConvertGameRulesTest, GlobalMessage) {
    nlohmann::json globalMessageRules = nlohmann::json::array({
        {
            {"rule", "global-message"},
            {"value", "Round {round}. Choose your weapon!"}
        },
        {
            {"rule", "global-message"},
            {"value", "You win!"}
        }
    });

    GameRules rules = convertGameRules(globalMessageRules);
    std::string expectedOutput = 
        "rule: global-message\nvalue: Round {round}. Choose your weapon!\nrule: global-message\nvalue: You win!\n";
    
    EXPECT_EQ(expectedOutput, rules.toString());
}

TEST_F(ConvertGameRulesTest, Scores) {
    nlohmann::json scoresRule = nlohmann::json::array({
        { 
            {"rule", "scores"},
            {"score", "wins"},
            {"ascending", "false"}
        }
    });

    GameRules rules = convertGameRules(scoresRule);

    // Keys are printed in alphabetic order instead
    // since they are stored in a map
    std::string expectedOutput = 
        "ascending: false\nrule: scores\nscore: wins\n";
    
    EXPECT_EQ(expectedOutput, rules.toString());
}
}