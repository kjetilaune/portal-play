#ifndef CAMERAHANDLER_H_
#define CAMERAHANDLER_H_

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <stdlib.h>
#include <iostream>


class CameraHandler {

  cv::VideoCapture *cap = NULL;
  cv::VideoCapture *opponent_capture = NULL;
	int framecounter = 0;
	int number_of_frames;
  std::string video_path;
  cv::Mat _currentImage;

public:
	CameraHandler();
	CameraHandler(std::string);

  cv::Mat get_image_from_camera();
  cv::Mat get_image_from_opponent();
	int get_width();
	int get_height();

};

#endif //CAMERAHANDLER_H_
