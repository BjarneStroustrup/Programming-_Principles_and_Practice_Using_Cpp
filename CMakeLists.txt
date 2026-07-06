cmake_minimum_required(VERSION 4.3.4)
project(ppp-cpp
  DESCRIPTION "Programming Principles and Practice using C++"
  HOMEPAGE_URL https://github.com/wouterbeek/Programming-_Principles_and_Practice_Using_Cpp
  LANGUAGES CXX
  VERSION 0.1.0
)

set(cppVersion 23)
set(CXX_EXTENSIONS OFF)
set(CXX_STANDARD ${cppVersion})
set(CXX_STANDARD_REQUIRED ON)

add_library(base INTERFACE)
add_library(${PROJECT_NAME}::base ALIAS base)
target_compile_features(base INTERFACE cxx_std_${cppVersion})

find_package(fltk REQUIRED)

add_library(ppp STATIC)
add_library(${PROJECT_NAME}::ppp ALIAS ppp)
target_include_directories(ppp PUBLIC include)
target_link_libraries(ppp PUBLIC fltk::fltk ${PROJECT_NAME}::base)
target_sources(ppp
  PRIVATE
    src/Graph_lib/Graph.cpp
    src/Graph_lib/GUI.cpp
    src/Graph_lib/Simple_window.cpp
    src/Graph_lib/Window.cpp
)

add_executable(chapter12)
target_link_libraries(chapter12 PRIVATE ${PROJECT_NAME}::ppp)
target_sources(chapter12 PRIVATE tool/chapter12.cpp)

add_executable(chapter13)
target_link_libraries(chapter13 PRIVATE ${PROJECT_NAME}::ppp)
target_sources(chapter13 PRIVATE tool/chapter13.cpp)
