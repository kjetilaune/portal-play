#ifndef DRAWER_H_
#define DRAWER_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>


class Drawer{

public:
	Drawer(char*);

	void display();
	void draw_image();
	void draw_quad(double, double, double);
	void draw_view_box(int, int);
	void draw_cross_hair(float, float, float);
	void draw_fire_button(cv::Mat&);
};

#endif //DRAWER_H_
