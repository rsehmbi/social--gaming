set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(interpreter
    interpreter.cpp
)

target_link_libraries(interpreter 
    game
    gameSessionInterface
)

target_include_directories(interpreter
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(interpreter
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)