#ifndef DRAWER_H_
#define DRAWER_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>


class Drawer{

public:
	Drawer(char*);

	static void display();
	static void draw_image();
	static void draw_quad(double, double, double);
	static void draw_view_box(int, int);
	static void draw_cross_hair(float, float, float);
	static void draw_fire_button(cv::Mat&);
	static void overlayImage(const cv::Mat &background, 
	                           const cv::Mat &foreground, 
	                           cv::Mat &output, 
	                           cv::Point2i location);
	static void draw_lives(cv::Mat&, float);
	static void draw_waving_hand_button(cv::Mat &image);
	void draw_winner(cv::Mat &image);
	void draw_loser(cv::Mat &image);
};

#endif //DRAWER_H_
