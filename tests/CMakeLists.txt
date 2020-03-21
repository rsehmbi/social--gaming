set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/googletest gameConverterTests)
set(BINARY tests)
enable_testing()

add_executable(runConvertGameRulesTests
    gameConverterTests/convertGameRulesTests.cpp
    InterpreterTests.cpp
    ConfigurationTests.cpp

)

add_executable(runDomainInterpreterTests
    DomainNameInterpreterTests/DomainNameTests.cpp
)

target_link_libraries(runConvertGameRulesTests gameConverter gtest gtest_main)
target_link_libraries(runDomainInterpreterTests domainnametranslator gtest gtest_main)

add_test(NAME convertGameRulesTests COMMAND runConvertGameRulesTests)
add_test(NAME DomainNameInterpreterTests COMMAND runDomainInterpreterTests)

target_link_libraries(runConvertGameRulesTests interpreter gameSessionInterface)