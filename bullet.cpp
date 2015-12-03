#include "bullet.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <iostream>

using namespace std;

Bullet::Bullet(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Bullet::Bullet(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
	cout << "X: " << this->x << endl;
}


void Bullet::draw(){
	this->z -= 10;
	glPushMatrix();
		glPushAttrib( GL_CURRENT_BIT );
		glTranslatef(this->x, this->y, this->z);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidSphere(0.1, 20, 20);
	glPopMatrix();
}