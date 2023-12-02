cmake_minimum_required(VERSION 3.20)
project(PluginTest)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/common)
add_subdirectory(common)
add_subdirectory(application)
add_subdirectory(plugin)
