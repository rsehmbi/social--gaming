#include "gtest/gtest.h"
#include "../lib/interpreter/include/interpreter.h"

using interpreter::Interpreter;

class InterpreterTests : public ::testing::Test {
protected:
    void SetUp() override {
    }

     void TearDown() override {

    }
    GameState gameState;
};

TEST_F(InterpreterTests, execute_Reverse_Test)
{
    // As variable class is changing will update as we update the variable class.
}

TEST_F(InterpreterTests, execute_Shuffle_Test)
{

}

TEST_F(InterpreterTests, execute_Sort_Test)
{

}
TEST_F(InterpreterTests, execute_Deal_Test)
{

}




