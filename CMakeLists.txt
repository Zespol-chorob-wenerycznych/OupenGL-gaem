cmake_minimum_required(VERSION 3.26)
project(gl)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(gl)
set_target_properties(gl PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)  
target_sources(gl PRIVATE ${MY_SOURCES})

add_subdirectory(vendor)