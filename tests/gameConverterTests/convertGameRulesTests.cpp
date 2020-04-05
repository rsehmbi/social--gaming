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
        std::cout << ruleCont.toString();
    }
}

TEST_F(ConvertGameRulesTest, GlobalMessage) {
    nlohmann::json jsonRules = nlohmann::json::array({
        {
            {"rule", "global-message"},
            {"value", "Round {round}. Choose your weapon!"}
        }
    });

    GameRules ruleList = convertGameRules(jsonRules);
    // Global message rule is the only rule in GameRules so it's at the front
    Rule rule = ruleList.getRules().front();

    std::string expectedOutput = 
        "rule: global-message\nvalue: Round {round}. Choose your weapon!\n";
    
    EXPECT_EQ(expectedOutput, rule.toString());
    EXPECT_EQ(RuleType::GlobalMessage, rule.getRuleType());
}

TEST_F(ConvertGameRulesTest, Scores) {
    nlohmann::json jsonRules = nlohmann::json::array({
        { 
            {"rule", "scores"},
            {"score", "wins"},
            {"ascending", "false"}
        }
    });

    GameRules ruleList = convertGameRules(jsonRules);
    // Scores rule is the only rule in GameRules so it's at the front
    Rule rule = ruleList.getRules().front();

    // Keys are printed in alphabetic order instead
    // since they are stored in a map
    std::string expectedOutput = 
        "rule: scores\nscore: wins\nascending: false\n";
    
    EXPECT_EQ(expectedOutput, rule.toString());
    EXPECT_EQ(RuleType::Scores, rule.getRuleType());
}

TEST_F(ConvertGameRulesTest, Add) {
    nlohmann::json jsonRules = nlohmann::json::array({
        { 
            {"rule", "add"},
            {"to", "winner.wins"},
            {"value", "1"}
        }
    });

    GameRules ruleList = convertGameRules(jsonRules);
    // Add rule is the only rule in GameRules so it's at the front
    Rule rule = ruleList.getRules().front();

    std::string expectedOutput = 
        "rule: add\nto: winner.wins\nvalue: 1\n";
    
    EXPECT_EQ(expectedOutput, rule.toString());
    EXPECT_EQ(RuleType::Add, rule.getRuleType());
}

TEST_F(ConvertGameRulesTest, Timer) {
    nlohmann::json jsonRule = nlohmann::json::array({
        { 
            {"rule", "timer"},
            {"duration", "5"},
            {"mode", "at most"},
            {"rules", 
                {
                    {
                        {"rule", "scores"},
                        {"score", "wins"},
                        {"ascending", "false"}
                    },
                }
            }
        },
    });

    GameRules ruleList = convertGameRules(jsonRule);
    Rule rule = ruleList.getRules().front();
    
    std::string expectedOutput = "rule: timer\n"
        "duration: 5\n"
        "mode: at most\n"
        "rules: \n"
        "{\n"
        "rule: scores\n"
        "score: wins\n"
        "ascending: false\n"
        "}\n";

    EXPECT_EQ(expectedOutput, rule.toString());
    EXPECT_EQ(RuleType::Timer, rule.getRuleType());
}


TEST_F(ConvertGameRulesTest, Foreach) {
    nlohmann::json jsonRule = nlohmann::json::array({
        { 
            {"rule", "foreach"},
            {"list", "configuration.Rounds.upfrom(1)"},
            {"element", "round"},
            {"rules", 
                {
                    {
                        {"rule", "global-message"},
                        {"value", "Round {round}. Choose your weapon!"}
                    },
                    {
                        {"rule", "foreach"},
                        {"list", "weapons"},
                        {"element", "weapon"},
                        {"rules",
                            {
                                {
                                    {"rule", "global-message"},
                                    {"value", "You chose a good weapon!"}
                                },
                                {
                                    {"rule", "global-message"},
                                    {"value", "Waiting for other players to choose weapons..."}
                                },
                            }
                        }
                    },
                    {
                        {"rule", "scores"},
                        {"score", "wins"},
                        {"ascending", "false"}
                    },
                }
            }
        },
    });

    GameRules ruleList = convertGameRules(jsonRule);
    Rule rule = ruleList.getRules().front();

    std::string expectedOutput = "rule: foreach\n"
        "list: configuration.Rounds.upfrom(1)\n"
        "element: round\n"
        "rules: \n"
        "{\n"
        "rule: global-message\n"
        "value: Round {round}. Choose your weapon!\n"
        "rule: foreach\n"
        "list: weapons\n"
        "element: weapon\n"
        "rules: \n"
        "{\n"
        "rule: global-message\n"
        "value: You chose a good weapon!\n"
        "rule: global-message\n"
        "value: Waiting for other players to choose weapons...\n"
        "}\n"
        "rule: scores\n"
        "score: wins\n"
        "ascending: false\n"
        "}\n";

    EXPECT_EQ(expectedOutput, rule.toString());
    EXPECT_EQ(RuleType::Foreach, rule.getRuleType());

    auto& nestedRules = rule.getNestedRules();
    EXPECT_EQ(RuleType::GlobalMessage, nestedRules[0].getRuleType());
    EXPECT_EQ(RuleType::Foreach, nestedRules[1].getRuleType());
    EXPECT_EQ(RuleType::Scores, nestedRules[2].getRuleType());  
}

TEST_F(ConvertGameRulesTest, When) {
    nlohmann::json jsonRule = nlohmann::json::array({
        {
            {"rule", "when"},
            {"cases",
                {
                    {
                        {"condition", "winners.size == players.size"},
                        {"rules", 
                            {
                                {
                                    {"rule", "global-message"},
                                    {"value", "Tie game!"}
                                }
                            }
                        }
                    },
                    {
                        {"condition", "winners.size == 0"},
                        {"rules", 
                            {
                                {
                                    {"rule", "global-message"},
                                    {"value", "Tie game!"}
                                }
                            }
                        }
                    },
                    {
                        {"condition", true},
                        {"rules", 
                            {
                                {
                                    {"rule", "global-message"},
                                    {"value", "Winners: {winners.elements.name}"}
                                },
                                {
                                    {"rule", "foreach"},
                                    {"list", "winners"},
                                    {"element", "winner"},
                                    {"rules", 
                                        {
                                            {
                                                {"rule", "add"},
                                                {"to", "winner.wins"},
                                                {"value", 1}
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    },
                }
            }

        }
    });

    std::string expectedOutput = "rule: when\n"
        "cases: \n"
        "{\n"
        "condition: winners.size == players.size\n"
        "rules: \n"
        "{\n"
        "rule: global-message\n"
        "value: Tie game!\n"
        "}\n"
        "condition: winners.size == 0\n"
        "rules: \n"
        "{\n"
        "rule: global-message\n"
        "value: Tie game!\n"
        "}\n"
        "condition: true\n"
        "rules: \n"
        "{\n"
        "rule: global-message\n"
        "value: Winners: {winners.elements.name}\n"
        "rule: foreach\n"
        "list: winners\n"
        "element: winner\n"
        "rules: \n"
        "{\n"
        "rule: add\n"
        "to: winner.wins\n"
        "}\n"
        "}\n"
        "}\n";

    GameRules ruleList = convertGameRules(jsonRule);
    Rule rule = ruleList.getRules().front();

    EXPECT_EQ(expectedOutput, rule.toString());
    EXPECT_EQ(RuleType::When, rule.getRuleType());
}
}