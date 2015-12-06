#ifndef DRAWER_H_
#define DRAWER_H_

#include <iostream>


class Drawer{

public:
	Drawer(char*);

	void display();
	void draw_image();
	void draw_quad(double, double, double);
	void draw_view_box(int, int);
};

#endif //DRAWER_H_
