#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace cv;

class CameraHandler{

	VideoCapture *cap = NULL;
	VideoCapture *opponent_capture = NULL;
	int framecounter = 0;
	int number_of_frames;
	string video_path;

public:
	CameraHandler();
	CameraHandler(string);

	Mat get_image_from_camera();
	Mat get_image_from_opponent();
	int get_width();
	int get_height();


};