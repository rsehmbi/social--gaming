
add_library(gamesession
  src/GameSession.cpp
)

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

target_link_libraries(gamesession sessionmanager)

install(TARGETS gamesession
  ARCHIVE DESTINATION lib
)

