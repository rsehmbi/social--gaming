set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(game 
    Game.cpp 
    GameState.cpp 
    Constants.cpp 
    GameRules.cpp 
    Configurations.cpp 
    Variables.cpp
    Rule.cpp
    UserVariables.cpp
)

target_include_directories(game
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)