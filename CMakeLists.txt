cmake_minimum_required(VERSION 3.19)

project(MCRecipesLister)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/dist")

find_package(jsoncpp CONFIG REQUIRED)
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)
