set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(variableTest)
set(BINARY tests)
enable_testing()

add_executable(runConvertGameRulesTests
    convertGameRulesTests.cpp
)

target_link_libraries(runConvertGameRulesTests 
    gameConverter 
    gtest 
    gtest_main
    gameSessionInterface
)

add_test(NAME convertGameRulesTests COMMAND runConvertGameRulesTests)
