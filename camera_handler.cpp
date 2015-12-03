#include "camera_handler.h"

CameraHandler::CameraHandler(){
	cap = new VideoCapture(0);

	if (cap == NULL || !cap->isOpened())
		exit(EXIT_FAILURE);
}


Mat CameraHandler::get_image_from_camera(){

	Mat image;

	(*cap) >> image;

	return image;
}


int CameraHandler::get_height(){
	return (int) cap->get( CV_CAP_PROP_FRAME_HEIGHT );
}

int CameraHandler::get_width(){
	return (int) cap->get( CV_CAP_PROP_FRAME_WIDTH );
}

