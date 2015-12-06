#include "NetworkReceiver.h"
#include "util.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//-------------------------------------------------------------------------
NetworkReceiver::NetworkReceiver(int heigth, 
                                 int width, 
                                 IReceiverCallback* caller)
  : _heigth(heigth),
    _width(width),
    _caller(caller) {

    cv::namedWindow("stream_client", CV_WINDOW_AUTOSIZE);
      
}

//-------------------------------------------------------------------------
void NetworkReceiver::Listen(int serverPort) {

  _socketListenerThread
    = std::thread(&NetworkReceiver::_Listen, this, serverPort);
}

//-------------------------------------------------------------------------
void NetworkReceiver::_Listen(int serverPort) {

  struct sockaddr_in serverAddr;
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);

  // Create Socket
  serverAddr.sin_family = PF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(serverPort);

  if((_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    Error("Receiver socket() failed");
  }

  if(bind(_socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
    Error("Receiver bind() failed");
  }

  if(listen(_socket, 5) == -1) {
    Error("Receiver listen() failed");
  }

  // Determine size of transferred field
  cv::Mat img = cv::Mat::zeros(_width, _heigth, CV_8UC1);
  int imgSize = img.total()*img.elemSize();
  
  char sockData[imgSize];
  int bytes = 0;

  // Block forever
  while(1) {
    int connectingSocket;
    if ((connectingSocket = accept(_socket, 
                                   (sockaddr*)&clientAddr, 
                                    &clientAddrLen)) == -1) {
      Error("Receiver accept() failed");

    } else {
      // Now that we have a valid connection, we can receive the data.
      Info("Receiving Data");

      while(1) {
        // Reset from previous run.
        memset(sockData, 0x0, sizeof(sockData));

        // Receive all data.
        for (int i = 0; i < imgSize; i += bytes) {
        	if ((bytes = recv(connectingSocket, 
                            sockData + i, 
                            imgSize - i, 
                            0)) == -1) {
 	          Error("Receiver recv() failed");
          }
        }

        // Build OpenCV Mat using received data.
        for (int i = 0;  i < img.rows; i++) {
          for (int j = 0; j < img.cols; j++) {
            (img.row(i)).col(j) = (uchar)sockData[((img.cols)*i)+j];
          }
        }
 
        // Send image to caller.
        if(_caller != NULL)
          _caller->OnReceived(img);
      }
    }
  }
}
