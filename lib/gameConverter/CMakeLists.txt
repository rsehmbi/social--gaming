set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glog 0.4.0 REQUIRED)

add_library(gameConverter 
    GameConverter.cpp
)

target_link_libraries(gameConverter 
    game 
    glog::glog
)

target_include_directories(gameConverter
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(gameConverter
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

# Used to create gameConverterTester
# TO DO: Create a separate testing library
add_executable(gameConverterTester gameConverterTester.cpp)
target_link_libraries(gameConverterTester gameConverter)