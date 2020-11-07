cmake_minimum_required(VERSION 3.5)
PROJECT(dstar)

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
#########################################################
# Include Files
#########################################################
add_executable(dstar main.cpp Dstar.cpp)
target_link_libraries(dstar ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}) 





# cmake_minimum_required(VERSION 3.5)
# project(dstar)
# find_package(Qt4 REQUIRED)
# 
# enable_testing()
# 
# include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})
# 
# set(Dstar_SRCS Dstar.cpp main.cpp)
# 
# qt4_automoc(${Dstar_SRCS})
# add_executable(dstar ${Dstar_SRCS})
# target_link_libraries(dstar ${QT_QTCORE_LIBRARY})
# 
# add_subdirectory(tests)
# 
# install(TARGETS dstar RUNTIME DESTINATION bin)