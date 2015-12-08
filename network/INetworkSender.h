#ifndef INETWORKSENDER_H_
#define INETWORKSENDER_H_

#include "Protocol.h"

#include <memory>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>


/*
 * A Interface representing a Network Sender.
 */
class INetworkSender {

public:
  virtual void Send(cv::Mat img) = 0;
  virtual void Send(cv::Mat img, Message msg) = 0;

};
typedef std::shared_ptr<INetworkSender> INetworkSenderPtr;

#endif //INETWORKSENDER_H_
