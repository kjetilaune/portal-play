#include <iostream>

using namespace std;

class Drawer{
	

public:
	Drawer(char*);

	void display();
	void draw_image();
	void draw_quad(double, double, double);
	void draw_view_box(int, int);
};