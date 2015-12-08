#ifndef NETWORKSENDER_H_
#define NETWORKSENDER_H_

#include "INetworkSender.h"
#include "ISenderCallback.h"
#include "Protocol.h"

#include <memory>
#include <thread>
#include <string>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>


/*
 * A class representing a sender that uses TCP as transport.
 */
class NetworkSender
  : public INetworkSender {
public:
  NetworkSender(int heigth, 
                int width, 
                int serverPort, 
                std::string serverIp,
                ISenderCallback* caller);
  virtual ~NetworkSender() {}

// INetworkSender
public:
  // These methods create new threads in a fire and forget fasion.
  // If defined in the constructor, a callback in the calling class
  // is called.
  virtual void Send(cv::Mat img);
  virtual void Send(cv::Mat img, Message msg);

public:
  bool isBuisy() { return _isBuisy; }

private:
  void _Send(cv::Mat img, Message msg);

private:
  int _heigth;
  int _width;

  int _socket;

  ISenderCallback* _caller;

  bool _isBuisy;
};
typedef std::shared_ptr<NetworkSender> NetworkSenderPtr;

#endif //NETWORKSENDER_H_
