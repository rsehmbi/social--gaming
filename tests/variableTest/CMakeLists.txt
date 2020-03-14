
add_executable(variableTest
  variableTest.cpp
)

set_target_properties(variableTest
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(variableTest networking 
    			   gameConverter
    			   sessionmanager
    			   jsonReader
    			   ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS variableTest
  RUNTIME DESTINATION bin
)

