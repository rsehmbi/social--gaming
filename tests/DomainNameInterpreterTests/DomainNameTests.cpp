#include "gtest/gtest.h"
#include "DomainNameTranslator.h"

#include <string>
#include <vector>

using domainnametranslator::DomainNameTranslator;

class DomainNameInterpreterTests : public ::testing::Test {
};

TEST_F(DomainNameInterpreterTests, testParsingInstructionDelimitedByPeriods) {
    std::string testInstruction = "players.elements.collect";
    std::vector<std::string> expected = {"players","elements","collect"};

    std::vector<std::string> actual = DomainNameTranslator::parseCommandChain(testInstruction);
    EXPECT_EQ(expected, actual);
}

TEST_F(DomainNameInterpreterTests, testParsingStringNotDelimitedByAnything) {
    std::string testInstruction = "players";
    std::vector<std::string> expected = {"players"};

    std::vector<std::string> actual = DomainNameTranslator::parseCommandChain(testInstruction);
    EXPECT_EQ(expected, actual);
}

TEST_F(DomainNameInterpreterTests, testParsingInstructionSurroundedByCurlyBraces) {
    std::string testInstruction = "{players}";
    std::vector<std::string> expected = {"players"};

    std::vector<std::string> actual = DomainNameTranslator::parseCommandChain(testInstruction);
    EXPECT_EQ(expected, actual);
}

TEST_F(DomainNameInterpreterTests, testParsingInstructionSurroundedByCurlyBracesDelimitedByPeriods) {
    std::string testInstruction = "{players.name}";
    std::vector<std::string> expected = {"players", "name"};

    std::vector<std::string> actual = DomainNameTranslator::parseCommandChain(testInstruction);
    EXPECT_EQ(expected, actual);
}

TEST_F(DomainNameInterpreterTests, testParsingInstructionWithMethodAndParameters1) {
    std::string testInstruction = "players.elements.contains(weapon.name)";

    std::vector<std::string> expectedCommandChain = {"players", "elements", "contains"};
    std::vector<std::string> actualCommandChain = DomainNameTranslator::parseCommandChain(testInstruction);

    std::vector<std::string> expectedFuncArgs = {"weapon.name"};
    std::vector<std::string> actualFuncArgs = DomainNameTranslator::parseFuncArgs(testInstruction);

    EXPECT_EQ(expectedCommandChain, actualCommandChain);
    EXPECT_EQ(expectedFuncArgs, actualFuncArgs);
}

TEST_F(DomainNameInterpreterTests, testParsingInstructionWithMethodAndParameters2) {
    std::string testInstruction = "players.elements.collect(player, player.weapon == weapon.beats)";

    std::vector<std::string> expectedCommandChain = {"players", "elements", "collect"};
    std::vector<std::string> actualCommandChain = DomainNameTranslator::parseCommandChain(testInstruction);

    std::vector<std::string> expectedFuncArgs = {"player", "player.weapon==weapon.beats"};
    std::vector<std::string> actualFuncArgs = DomainNameTranslator::parseFuncArgs(testInstruction);

    EXPECT_EQ(expectedCommandChain, actualCommandChain);
    EXPECT_EQ(expectedFuncArgs, actualFuncArgs);
}