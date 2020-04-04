set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(domainnametranslator
    DomainNameTranslator.cpp
)

target_link_libraries(domainnametranslator 
    game,
    gamesession
)

target_include_directories(domainnametranslator
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(domainnametranslator
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)