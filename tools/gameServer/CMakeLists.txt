
add_executable(main
  main.cpp
)

set_target_properties(main
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(main
  networking
  ${CMAKE_THREAD_LIBS_INIT}
)
#target_link_libraries(main
#  networking
#  ${CMAKE_THREAD_LIBS_INIT}
#  sessionmanager
#)

install(TARGETS main
  RUNTIME DESTINATION bin
)

