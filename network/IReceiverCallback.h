#ifndef IRECEIVERCALLBACK_H_
#define IRECEIVERCALLBACK_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <string>


/*
 * A Callback interface for the NetworkReceiver Class
 */
class IReceiverCallback {
public:
  virtual void OnReceived(cv::Mat mat) = 0;
};

#endif //IRECEIVERCALLBACK_H_