cmake_minimum_required(VERSION 3.4)
PROJECT( viewbox )
FIND_PACKAGE( OpenCV REQUIRED )

message(status "----${OpenCV_INCLUDE_DIRS}")

FIND_PACKAGE( OpenGL REQUIRED )
FIND_PACKAGE( GLUT REQUIRED )
SET(MySources main.cpp player.cpp player.h drawer.cpp drawer.h)
ADD_EXECUTABLE( viewbox ${MySources} )
TARGET_LINK_LIBRARIES( viewbox ${OpenCV_LIBS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
SET_SOURCE_FILES_PROPERTIES(${MySources} PROPERTIES LANGUAGE CXX ) 
INCLUDE_DIRECTORIES(viewbox 
	"/usr/local/include")