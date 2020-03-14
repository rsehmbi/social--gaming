set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/googletest)
set(BINARY tests)
enable_testing()

add_subdirectory(gameConverterTests)
add_subdirectory(DomainNameInterpreterTests)