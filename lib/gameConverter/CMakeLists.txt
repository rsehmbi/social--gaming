set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(gameConverter 
    GameConverter.cpp
)

target_link_libraries(gameConverter 
    game 
    glog::glog
    gflags::gflags
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