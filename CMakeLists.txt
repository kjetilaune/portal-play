cmake_minimum_required(VERSION 3.0)
PROJECT(viewbox)

FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)

SET(MySources
  main.cpp 
  player.cpp 
  player.h 
  drawer.cpp 
  drawer.h 
  camera_handler.cpp 
  camera_handler.h 
  bullet.cpp 
  bullet.h 
  bird.cpp 
  bird.h)

set(CMAKE_CXX_FLAGS 
  "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-writable-strings -Wno-unicode-whitespace")

ADD_EXECUTABLE(viewbox 
  ${MySources})

TARGET_LINK_LIBRARIES(viewbox
  network

  ${OpenCV_LIBS}
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY})

#
ADD_SUBDIRECTORY(network)

### Have to be set for El Capitain ###
SET_SOURCE_FILES_PROPERTIES(${MySources} PROPERTIES LANGUAGE CXX ) 
INCLUDE_DIRECTORIES(viewbox 
	"/usr/local/include")
