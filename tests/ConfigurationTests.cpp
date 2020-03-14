#include "gtest/gtest.h"
#include "Configurations.h"

TEST(ConfigurationTests, Default_Constructor_Test)
{
    game::Configurations configuration;

    EXPECT_FALSE(configuration.hasAudience());
    EXPECT_EQ(configuration.getMaxNoOfPlayers(),0);
    EXPECT_EQ(configuration.getMinNoOfPlayers(),0);
    EXPECT_EQ(configuration.getGameName()," ");
}

TEST(ConfigurationTests, Constructor_Test)
{
    game::Configurations configuration("RockPaperScissor",false,0,2);

    EXPECT_FALSE(configuration.hasAudience());
    EXPECT_EQ(configuration.getMaxNoOfPlayers(),2);
    EXPECT_EQ(configuration.getMinNoOfPlayers(),0);
    EXPECT_EQ(configuration.getGameName(),"RockPaperScissor");
}

TEST(ConfigurationTests, Constructor_Test_With_Values)
{
    game::Configurations configuration("TicTacToe",
                                       true,2,2);

    EXPECT_TRUE(configuration.hasAudience());
    EXPECT_EQ(configuration.getMaxNoOfPlayers(),2);
    EXPECT_EQ(configuration.getMinNoOfPlayers(),2);
    EXPECT_EQ(configuration.getGameName(),"TicTacToe");
}

TEST(ConfigurationTests, Constructor_Test_With_Complex_Values)
{
    game::Configurations configuration("A really really long game provided by the user is enetered here.",
            true,9999,9999);

    EXPECT_TRUE(configuration.hasAudience());
    EXPECT_EQ(configuration.getMaxNoOfPlayers(),9999);
    EXPECT_EQ(configuration.getMinNoOfPlayers(),9999);
    EXPECT_EQ(configuration.getGameName(),"A really really long game provided by the user is enetered here.");
}