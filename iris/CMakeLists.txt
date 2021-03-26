cmake_minimum_required(VERSION 3.7)

project(NEWTONITERATOR LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

set(Sources iris.cpp)

add_executable(${PROJECT_NAME} ${Sources})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

source_group("Sources" FILES ${Files_SRCS})