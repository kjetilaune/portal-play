#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

class CameraHandler{

	VideoCapture *cap = NULL;

public:
	CameraHandler();

	Mat get_image_from_camera();
	int get_width();
	int get_height();

};