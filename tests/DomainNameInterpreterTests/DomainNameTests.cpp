#include "gtest/gtest.h"
#include "DomainNameTranslator.h"

#include <string>
#include <vector>

using domainnametranslator::DomainNameTranslator;

class DomainNameInterpreterTests : public ::testing::Test {
};

TEST_F(DomainNameInterpreterTests, test) {
    std::string testInstruction = "players.elements.collect";
    std::vector<std::string> expected = {"players","elements","collect"};

    std::vector<std::string> actual = DomainNameTranslator::parseInstruction(testInstruction);
    EXPECT_EQ(expected, actual);
}