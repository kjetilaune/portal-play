#ifndef NETWORKSENDER_H_
#define NETWORKSENDER_H_

#include "ISenderCallback.h"
#include "Protocol.h"

#include <memory>
#include <string>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>


/*
 * A class representing a sender that uses TCP as transport.
 */
class NetworkSender {
public:
  NetworkSender(int heigth, 
                int width, 
                int serverPort, 
                std::string serverIp,
                ISenderCallback* caller);
  virtual ~NetworkSender() {}

public:
  void Send(cv::Mat img);
  void Send(cv::Mat img, Message msg);

private:
  int _heigth;
  int _width;

  int _socket;

  ISenderCallback* _caller;

};
typedef std::shared_ptr<NetworkSender> NetworkSenderPtr;

#endif //NETWORKSENDER_H_
