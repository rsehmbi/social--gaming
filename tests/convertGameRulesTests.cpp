#include "gtest/gtest.h"
#include "GameConverter.h"

using game::Rule;
using game::RuleType;
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
    for(auto& rule: ruleList) {
        RuleContainer ruleCont = rule.getRuleContainer();
        for(auto& mapElem : ruleCont.ruleInformation) {
           std::cout << mapElem.first << " " << mapElem.second << " " << std::endl;
        } 
    }
}

TEST_F(ConvertGameRulesTest, GlobalMessage) {
    nlohmann::json jsonGlobalMessageRules = nlohmann::json::array({
        {
            {"rule", "global-message"},
            {"value", "Round {round}. Choose your weapon!"}
        },
        {
            {"rule", "global-message"},
            {"value", "You win!"}
        }
    });

    GameRules rules = convertGameRules(jsonGlobalMessageRules);
    // Global message rule is the only rule in GameRules so it's at the front
    Rule globalMessageRule = rules.getRules().front();

    std::string expectedOutput = 
        "rule: global-message\nvalue: Round {round}. Choose your weapon!\nrule: global-message\nvalue: You win!\n";
    
    EXPECT_EQ(expectedOutput, rules.toString());
    EXPECT_EQ(RuleType::GlobalMessage, globalMessageRule.getRuleType());
}

TEST_F(ConvertGameRulesTest, Scores) {
    nlohmann::json jsonScoresRule = nlohmann::json::array({
        { 
            {"rule", "scores"},
            {"score", "wins"},
            {"ascending", "false"}
        }
    });

    GameRules rules = convertGameRules(jsonScoresRule);
    // Scores rule is the only rule in GameRules so it's at the front
    Rule scoresRule = rules.getRules().front();

    // Keys are printed in alphabetic order instead
    // since they are stored in a map
    std::string expectedOutput = 
        "ascending: false\nrule: scores\nscore: wins\n";
    
    EXPECT_EQ(expectedOutput, rules.toString());
    EXPECT_EQ(RuleType::Scores, scoresRule.getRuleType());
}

// TO DO: Add specific cases for when the message is to a list
// of recepients, a single player, or to an audience member
TEST_F(ConvertGameRulesTest, Message) {
    nlohmann::json jsonScoresRule = nlohmann::json::array({
        { 
            {"rule", "message"},
            {"to", "person"},
            {"value", "Your turn!"}
        }
    });

    GameRules rules = convertGameRules(jsonScoresRule);
    // Scores rule is the only rule in GameRules so it's at the front
    Rule scoresRule = rules.getRules().front();

    // Keys are printed in alphabetic order instead
    // since they are stored in a map
    std::string expectedOutput = 
        "rule: message\nto: person\nvalue: Your turn!\n";
    
    EXPECT_EQ(expectedOutput, rules.toString());
    EXPECT_EQ(RuleType::Message, scoresRule.getRuleType());
}
}