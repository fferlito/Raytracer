cmake_minimum_required(VERSION 3.2)

project(ray)

# Create a debug build
set(CMAKE_CXX_FLAGS "-Wall --std=c++14")

# Set all CPP files to be source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Code/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
