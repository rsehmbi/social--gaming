
add_library(sessionmanager
  src/sessionManager.cpp
)

target_include_directories(sessionmanager
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

set_target_properties(sessionmanager
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS sessionmanager
  ARCHIVE DESTINATION lib
)

