
add_library(sessionmanager
  src/SessionManager.cpp
)

target_include_directories(sessionmanager
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(sessionmanager
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

target_link_libraries(sessionmanager 
  networking 
  gamesession 
  game
  glog::glog)


install(TARGETS sessionmanager
  ARCHIVE DESTINATION lib
)

