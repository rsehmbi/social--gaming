set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(runConvertGameRulesTests
    convertGameRulesTests.cpp
)

target_link_libraries(runConvertGameRulesTests gameConverter gtest gtest_main)

add_test(NAME convertGameRulesTests COMMAND runConvertGameRulesTests)