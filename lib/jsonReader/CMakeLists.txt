cmake_minimum_required(VERSION 3.16)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(jsonParser jsonParser.cpp)
# add_executable(jsonParser jsonParser.cpp)
target_link_libraries(jsonParser PRIVATE nlohmann_json::nlohmann_json)

find_package(glog 0.4.0 REQUIRED)
target_link_libraries(jsonParser glog::glog)

target_include_directories(
    jsonParser 
        PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)