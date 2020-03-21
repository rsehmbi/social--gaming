#include "gtest/gtest.h"
#include "DomainNameTranslator.h"

#include <string>
#include <vector>

using domainnametranslator::DomainNameTranslator;

class DomainNameInterpreterTests : public ::testing::Test {
};

TEST_F(DomainNameInterpreterTests, testInstructionDelimitedByPeriods) {
    std::string testInstruction = "players.elements.collect";
    std::vector<std::string> expected = {"players","elements","collect"};

    std::vector<std::string> actual = DomainNameTranslator::parseInstruction(testInstruction);
    EXPECT_EQ(expected, actual);
}

TEST_F(DomainNameInterpreterTests, testStringNotDelimitedByAnything) {
    std::string testInstruction = "players";
    std::vector<std::string> expected = {"players"};

    std::vector<std::string> actual = DomainNameTranslator::parseInstruction(testInstruction);
    EXPECT_EQ(expected, actual);
}

TEST_F(DomainNameInterpreterTests, testInstructionSurroundedByCurlyBraces) {
    std::string testInstruction = "{players}";
    std::vector<std::string> expected = {"players"};

    std::vector<std::string> actual = DomainNameTranslator::parseInstruction(testInstruction);
    EXPECT_EQ(expected, actual);
}

TEST_F(DomainNameInterpreterTests, testInstructionSurroundedByCurlyBracesDelimitedByPeriods) {
    std::string testInstruction = "{players.name}";
    std::vector<std::string> expected = {"players", "name"};

    std::vector<std::string> actual = DomainNameTranslator::parseInstruction(testInstruction);
    EXPECT_EQ(expected, actual);
}

TEST_F(DomainNameInterpreterTests, testInstructionWithMethodAndParameters) {
    std::string testInstruction = "players.elements.contains(weapon.name)";
    std::vector<std::string> expected = {"players", "elements"};
    std::vector<std::string> actual = DomainNameTranslator::parseInstruction(testInstruction);
    EXPECT_EQ(expected, actual);
}