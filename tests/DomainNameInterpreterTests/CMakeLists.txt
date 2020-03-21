set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(runDomainNameInterpreterTests
    DomainNameTests.cpp
)

target_link_libraries(runDomainNameInterpreterTests domainnametranslator gtest gtest_main)

add_test(NAME DomainNameInterpreterTests COMMAND runDomainNameInterpreterTests)