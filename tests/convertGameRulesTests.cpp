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

TEST_F(ConvertGameRulesTest, Add) {
    nlohmann::json jsonScoresRule = nlohmann::json::array({
        { 
            {"rule", "add"},
            {"to", "winner.wins"},
            {"value", "1"}
        }
    });

    GameRules rules = convertGameRules(jsonScoresRule);
    // Add rule is the only rule in GameRules so it's at the front
    Rule scoresRule = rules.getRules().front();

    std::string expectedOutput = 
        "rule: add\nto: winner.wins\nvalue: 1\n";
    
    EXPECT_EQ(expectedOutput, rules.toString());
    EXPECT_EQ(RuleType::Add, scoresRule.getRuleType());
}

TEST_F(ConvertGameRulesTest, Timer) {
    nlohmann::json jsonScoresRule = nlohmann::json::array({
        { 
            {"rule", "timer"},
            {"duration", "5"},
            {"mode", "at most"},
            {"rules", {
                {"rule", "scores"},
                {"score", "wins"},
                {"ascending", "false"}
            }}
        }
    });

    GameRules rules = convertGameRules(jsonScoresRule);
    Rule scoresRule = rules.getRules().front();

    std::string expectedOutput = "";
    // TODO: figure out a way to store nested rules properly. Then revisit this test.
    // Currently, the RuleContainer adds rules as a map. The map can only only have one unique key meaning
    // any value that has a key gets overwritten by a new value with the same key. Need to discuss
    // how we want to store nested rules in RuleContainer.

    // EXPECT_EQ(expectedOutput, rules.toString());
    EXPECT_EQ(RuleType::Timer, scoresRule.getRuleType());
}
}