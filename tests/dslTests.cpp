#include "lib/googletest/include/gtest/gtest.h"
#include "../lib/interpreter/include/dsl.h"
#include "../lib/interpreter/include/json.hpp"

TEST(ListOperations, testExtend) {
    json obj;
    obj["target"] = json::array({"player0"});
    obj["list"] = json::array({"player1", "player2", "player3"});

    json expected;
    json actual = DSL::extend(obj);
    expected["target"] = json::array({"player0", "player1", "player2", "player3"});
    EXPECT_EQ(actual, expected);
}