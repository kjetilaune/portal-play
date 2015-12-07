#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>


typedef struct _Message Message;
struct _Message {

  // Face Data.
  cv::Point3f center;
  cv::Point2f topleft;
  cv::Point2f topright;
  cv::Point2f downright;
  cv::Point2f downleft;

  // Game interaction information.
  bool shoot;
};

#endif //PROTOCOL_H
