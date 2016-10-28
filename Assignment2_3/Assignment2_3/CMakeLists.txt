cmake_minimum_required(VERSION 3.5)
project(Assignment2_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES animate.cpp animate_class.cpp)
add_executable(animate ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(animate ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
