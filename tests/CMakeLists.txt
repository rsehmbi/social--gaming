add_subdirectory(lib/googletest)
set(BINARY tests)
enable_testing()

add_executable(runConvertGameRulesTests
    convertGameRulesTests.cpp
)

target_link_libraries(runConvertGameRulesTests gameConverter gtest gtest_main)

add_test(NAME convertGameRulesTests COMMAND runConvertGameRulesTests)
