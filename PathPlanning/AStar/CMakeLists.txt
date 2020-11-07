cmake_minimum_required(VERSION 3.5)
project(astart)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 

find_package(OpenCV  REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(VTK REQUIRED)
add_executable(astart main.cpp)

target_link_libraries(astart ${OpenCV_LIBS})

install(TARGETS astart RUNTIME DESTINATION bin)
