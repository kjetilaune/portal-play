PROJECT(network)
FIND_PACKAGE(OpenCV)

SET(network_SRCS
  NetworkReceiver.cpp
  NetworkSender.cpp
  Util.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#
ADD_LIBRARY(network STATIC
  ${network_SRCS})

TARGET_INCLUDE_DIRECTORIES(network
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#
ADD_EXECUTABLE(network_test
  ${network_SRCS}
  NetworkTest.cpp)

TARGET_LINK_LIBRARIES(network_test 
  ${OpenCV_LIBS})
