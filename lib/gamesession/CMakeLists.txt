
add_library(gamesession
  src/GameSession.cpp
)

# Build rules for game Session Interface
add_library(gameSessionInterface INTERFACE)

target_include_directories(gameSessionInterface 
  INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(gameSessionInterface 
  INTERFACE
    networking 
)

# Build rules for game Session
target_include_directories(gamesession
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(gamesession
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

target_link_libraries(gamesession sessionmanager interpreter)

target_link_libraries(gamesession user)

install(TARGETS gamesession
  ARCHIVE DESTINATION lib
)

