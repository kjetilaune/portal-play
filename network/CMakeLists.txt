PROJECT(network)
FIND_PACKAGE(OpenCV)

SET(network_SRCS
  NetworkReceiver.cpp
  NetworkSender.cpp
  
  NetworkTest.cpp
  Util.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

ADD_EXECUTABLE(network 
  ${network_SRCS})

TARGET_LINK_LIBRARIES(network 
  ${OpenCV_LIBS})
