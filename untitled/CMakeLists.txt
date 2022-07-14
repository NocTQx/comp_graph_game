cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(untitled main.cpp view.h cmake-build-debug/map.h)

target_link_libraries(untitled sfml-graphics sfml-audio)