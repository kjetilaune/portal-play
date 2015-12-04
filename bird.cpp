#include "drawer.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include "bird.h"

Bird::Bird(){

}

Bird::Bird(int size){

}

void draw_body(){

	//Top deck
	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(-5.0f, 1.0f, -1.0f);
		glVertex3f(-5.0f, 1.0f, 1.0f);
		glVertex3f(5.0f, 1.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(5.0f, 1.0f, -1.0f);
		glVertex3f(5.0f, 1.0f, 1.0f);
		glVertex3f(-5.0f, 1.0f, 1.0f);
	glEnd();

	//Bottom deck
	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(-5.0f, -1.0f, -1.0f);
		glVertex3f(-5.0f, -1.0f, 1.0f);
		glVertex3f(5.0f, -1.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(5.0f, -1.0f, -1.0f);
		glVertex3f(5.0f, -1.0f, 1.0f);
		glVertex3f(-5.0f, -1.0f, 1.0f);
	glEnd();

	//Right side
	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(-5.0f, 1.0f, 1.0f);
		glVertex3f(-5.0f, -1.0f, 1.0f);
		glVertex3f(5.0f, 1.0f, 1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(5.0f, -1.0f, 1.0f);
		glVertex3f(5.0f, 1.0f, 1.0f);
		glVertex3f(-5.0f, -1.0f, 1.0f);
	glEnd();

	//Left side
	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(-5.0f, 1.0f, -1.0f);
		glVertex3f(-5.0f, -1.0f, -1.0f);
		glVertex3f(5.0f, 1.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(5.0f, -1.0f, -1.0f);
		glVertex3f(5.0f, 1.0f, -1.0f);
		glVertex3f(-5.0f, -1.0f, -1.0f);
	glEnd();

	//Short side front
	glBegin(GL_TRIANGLES);
		glColor3f(0,0,0);
		glVertex3f(5.0f, 1.0f, 1.0f);
		glVertex3f(5.0f, -1.0f, 1.0f);
		glVertex3f(5.0f, 1.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(0,0,0);
		glVertex3f(5.0f, -1.0f, -1.0f);
		glVertex3f(5.0f, 1.0f, -1.0f);
		glVertex3f(5.0f, -1.0f, 1.0f);
	glEnd();

	//Short side back
	glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glVertex3f(-5.0f, 1.0f, 1.0f);
		glVertex3f(-5.0f, -1.0f, 1.0f);
		glVertex3f(-5.0f, 1.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glVertex3f(-5.0f, -1.0f, -1.0f);
		glVertex3f(-5.0f, 1.0f, -1.0f);
		glVertex3f(-5.0f, -1.0f, 1.0f);
	glEnd();

}

void draw_tail(){
	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(-7.0f, 1.0f, -1.0f);
		glVertex3f(-7.0f, 1.0f, 1.0f);
		glVertex3f(-5.0f, 1.0f, 1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		//glColor3f(1,0,0);
		glVertex3f(-7.0f, 1.0f, -1.0f);
		glVertex3f(-5.0f, 1.0f, 1.0f);
		glVertex3f(-5.0f, 1.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		//glColor3f(1,0,0);
		glVertex3f(-7.0f, 1.0f, -1.0f);
		glVertex3f(-7.0f, 1.0f, 1.0f);
		glVertex3f(-5.0f, -1.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		//glColor3f(1,0,0);
		glVertex3f(-5.0f, -1.0f, -1.0f);
		glVertex3f(-5.0f, -1.0f, 1.0f);
		glVertex3f(-7.0f, 1.0f, 1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		//glColor3f(0,1,0);
		glVertex3f(-5.0f, -1.0f, -1.0f);
		glVertex3f(-5.0f, 1.0f, -1.0f);
		glVertex3f(-7.0f, 1.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		//glColor3f(0,1,0);
		glVertex3f(-5.0f, -1.0f, 1.0f);
		glVertex3f(-5.0f, 1.0f, 1.0f);
		glVertex3f(-7.0f, 1.0f, 1.0f);
	glEnd();
}

void draw_beak(){
	glBegin(GL_TRIANGLES);
		glColor3f(1,0.6f,0);
		glVertex3f(5.0f, 0.0f, -1.0f);
		glVertex3f(5.0f, 0.0f, 1.0f);
		glVertex3f(8.0f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1,0.6f,0);
		glVertex3f(5.0f, -1.0f, -1.0f);
		glVertex3f(5.0f, -1.0f, 1.0f);
		glVertex3f(8.0f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1,0.6f,0);
		glVertex3f(5.0f, 0.0f, -1.0f);
		glVertex3f(5.0f, -1.0f, -1.0f);
		glVertex3f(8.0f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1,0.6f,0);
		glVertex3f(5.0f, 0.0f, 1.0f);
		glVertex3f(5.0f, -1.0f, 1.0f);
		glVertex3f(8.0f, -0.5f, 0.0f);
	glEnd();
}

void draw_wings(float wing_tip_height){

	
	//glRotatef(90, 0,1,0);
	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(-5.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 7.5f, 7.5f);
		glVertex3f(5.0f, 1.0f, 1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);
		glVertex3f(-5.0f, 1.0f, -1.0f);
		glVertex3f(0.0f, 7.5f, -7.5f);
		glVertex3f(5.0f, 1.0f, -1.0f);
	glEnd();

	
}


void Bird::draw(int x, int y, int z, int rot){
	glPushMatrix();
	//glTranslatef(0,0,-20);
	//glRotatef(rot, 0, 1, 0);
	draw_wings(0);
	draw_body();
	draw_tail();
	draw_beak();
	glPopMatrix();
}