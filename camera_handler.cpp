#include "camera_handler.h"


using namespace std;
using namespace cv;

CameraHandler::CameraHandler(){
	cap = new VideoCapture(0);

	if (cap == NULL || !cap->isOpened())
		exit(EXIT_FAILURE);

  // Init Sender
  //_sender.reset(new NetworkSender(320, 240, 1234, "127.0.0.1", this));
  (*cap) >> _currentImage;
  //_sender->Send(_currentImage);
}

CameraHandler::CameraHandler(string video_path){
	cap = new VideoCapture(0);
	opponent_capture = new VideoCapture(video_path);
	this->video_path = video_path;
	if (cap == NULL || !cap->isOpened() 
		|| opponent_capture == NULL || !opponent_capture->isOpened())
		
		exit(EXIT_FAILURE);
	this->number_of_frames = (int) opponent_capture->get(CV_CAP_PROP_FRAME_COUNT);
}


Mat CameraHandler::get_image_from_camera(){

	(*cap) >> _currentImage;

	return _currentImage;
}

Mat CameraHandler::get_image_from_opponent(){
	Mat image;
	
	if (framecounter >= number_of_frames-1){
		delete opponent_capture;
		opponent_capture = new VideoCapture(this->video_path);
		framecounter = -1;
	}
		
	framecounter++;

	(*opponent_capture) >> image;

	return image;
}

int CameraHandler::get_height(){
	return (int) cap->get( CV_CAP_PROP_FRAME_HEIGHT );
}

int CameraHandler::get_width(){
	return (int) cap->get( CV_CAP_PROP_FRAME_WIDTH );
}
