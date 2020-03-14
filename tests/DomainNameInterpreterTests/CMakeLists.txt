set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(runDomainNameTests
    DomainNameTests.cpp
)

target_link_libraries(runDomainNameTests domainnametranslator gtest gtest_main)

add_test(NAME DomainNameTests COMMAND runDomainNameTests)