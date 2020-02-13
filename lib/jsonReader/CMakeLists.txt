set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glog 0.4.0 REQUIRED)

add_library(jsonReader JsonReader.cpp)

target_link_libraries(jsonReader glog::glog)

target_include_directories(jsonReader
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)