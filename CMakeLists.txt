CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(UBSAN OFF)
option(ASAN OFF)

project(PPP LANGUAGES CXX)

if (UBSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=undefined")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -fsanitize=undefined")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=undefined")
endif()

if (ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

#execute_process(COMMAND ../local/bin/fltk-config --use-gl --use-images --cxxflags OUTPUT_VARIABLE FLTK_CXX_FLAGS)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLTK_CXX_FLAGS}")

set(FLTK_DIR ../local/share/fltk)
find_package(FLTK REQUIRED NO_MODULE)
#FIND_PACKAGE(OpenGL REQUIRED)

include_directories(BEFORE ../local/include)
link_directories(BEFORE ../local/lib)

add_executable(Chapter_12_3 Chapter_12_3.cpp Window.cpp GUI.cpp Graph.cpp)
target_link_libraries(Chapter_12_3 fltk fltk_images)

#add_executable(Window Window.cpp)
#target_link_libraries(Window fltk)
