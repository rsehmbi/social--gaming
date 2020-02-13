
add_library(users
  src/Users.cpp
)

target_include_directories(users
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(users
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

#target_link_libraries(users gamesession)

install(TARGETS users
  ARCHIVE DESTINATION lib
)

