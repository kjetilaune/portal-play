#include "NetworkSender.h"
#include "Protocol.h"
#include "Util.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//-------------------------------------------------------------------------
NetworkSender::NetworkSender(int serverPort, 
                             std::string serverIp,
                             ISenderCallback* caller)
  : _caller(caller) {

  struct sockaddr_in serverAddr;
  socklen_t serverAddrLen = sizeof(serverAddr);

  if((_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    Error("create socket failed");
  }

  serverAddr.sin_family = PF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(serverIp.c_str());
  serverAddr.sin_port = htons(serverPort);

  if (connect(_socket, (sockaddr*)&serverAddr, serverAddrLen) < 0) {
    Error("-> socket connect() failed.");
  }
}

//-------------------------------------------------------------------------
void NetworkSender::Send(cv::Mat img) {

  cv::Mat img0;
  cv::Mat img1;
  Message msg;

  // Convert to grayscale
  img0 = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
  flip(img, img, 1);
  cvtColor(img, img0, CV_BGR2GRAY);

  int bytes=0;
  img1 = (img0.reshape(0,1));

  // Determine size of field to transfer
  int imgSize = img0.total()*img0.elemSize();
  int msgSize = sizeof(msg);
  int totalSize = imgSize + msgSize;

  uchar* targetBuffer = new uchar[totalSize]; 
  std::memcpy(targetBuffer, img1.data, imgSize);
  std::memcpy(targetBuffer + imgSize, (void*)&msg, msgSize);

  // send the grayscaled image
  bool sendResult = true;
  if ((bytes = send(_socket, targetBuffer, totalSize, 0)) < 0){
	  Error("Sender send() failed");
    sendResult = false;
	}

  // Notify caller that sending is completed.
  if(_caller != NULL)
    _caller->OnSentCompleted(sendResult);
}
