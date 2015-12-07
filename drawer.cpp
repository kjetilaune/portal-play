#include "drawer.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>


using namespace std;

GLuint texture;
unsigned char *data;
FILE *file;
const char* path;
int w = 320, h = 178;

Drawer::Drawer(char* texture_path){
	/*path = texture_path;

	file = fopen(texture_path, "rb");

	data = (unsigned char*) malloc(w * h * 3);

	fread(data, w * h * 3, 1, file);
	fclose(file);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);*/
}

void Drawer::draw_cross_hair(float x, float y, float z){
	glPushAttrib(GL_POLYGON_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT) ;
    glDisable(GL_LIGHTING) ;

    //Draw cross hair
    glPushMatrix();
      glBegin(GL_LINES);
          glColor3f(1.0f,0.0f,0.0f);    
          glVertex3f(x, y-0.75, -60);
          glVertex3f(x, y-0.25, -60);
      glEnd();
      
    glPopMatrix();

    glPushMatrix();
      glBegin(GL_LINES);
          glColor3f(1.0f,0.0f,0.0f);    
          glVertex3f(x, y+0.75, -60);
          glVertex3f(x, y+0.25, -60);
      glEnd();
      
    glPopMatrix();

    glPushMatrix();
      glBegin(GL_LINES);
          glColor3f(1.0f,0.0f,0.0f);    
          glVertex3f(x-0.75, y, -60);
          glVertex3f(x-0.25, y, -60);
      glEnd();
      
    glPopMatrix();

    glPushMatrix();
      glBegin(GL_LINES);
          glColor3f(1.0f,0.0f,0.0f);    
          glVertex3f(x+0.75, y, -60);
          glVertex3f(x+0.25, y, -60);
      glEnd();
      glDisable(GL_DEPTH_TEST);
    glPopMatrix();
}

void Drawer::draw_view_box(int width, int height){

	glDisable(GL_LIGHTING) ;

	float w = width/2.0;
	float h = height/2.0 + 0.5;
	float d = 20.0; //Depth
	float number_of_squares = 12;

	//Draw squares
	for (int i = -3; i < number_of_squares -3; i++){
	  glBegin(GL_LINE_LOOP);
	    glColor3f(1.0f,1.0f,1.0f);
	    glVertex3f(-1.0f*w ,-1.0f*h,float(-d*i));
	    glVertex3f(-1.0f*w ,1.0f*h,float(-d*i) );
	    glVertex3f(1.0f*w ,1.0f*h,float(-d*i) );
	    glVertex3f(1.0f*w ,-1.0f*h,float(-d*i));
	  glEnd();
	}

  	//Draw lines
	for (int i = 0; i < 11; i++){
	glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_LINES);
      glVertex3f(-1.0*w, -1.0*h + 2*h*i/10, 1000);
      glVertex3f(-1.0*w, -1.0*h + 2*h*i/10, -d*(number_of_squares-1));
    glEnd();
  	}
  	for (int i = 0; i < 11; i++){
	    glBegin(GL_LINES);
	      glVertex3f(1.0*w, -1.0*h + 2*h*i/10, 1000);
	      glVertex3f(1.0*w, -1.0*h + 2*h*i/10, -d*(number_of_squares-1));
	    glEnd();
  	}
	  for (int i = 1; i < 10; i++){
	    glBegin(GL_LINES);
	      glVertex3f(-1.0*w + 2*w*i/10, -1.0*h, 1000);
	      glVertex3f(-1.0*w + 2*w*i/10, -1.0*h, -d*(number_of_squares-1));
	    glEnd();
	  }
	  for (int i = 1; i < 10; i++){
	    glBegin(GL_LINES);
	      glVertex3f(-1.0*w + 2*w*i/10, 1.0*h, 1000);
	      glVertex3f(-1.0*w + 2*w*i/10, 1.0*h, -d*(number_of_squares-1));
	    glEnd();
	  }
  glEnable(GL_LIGHTING);

  
}

void Drawer::draw_quad(double x, double y, double z){
  glBegin(GL_QUADS); 
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-1.0, y-1.0, z);
     
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x+1.0, y-1.0, z);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x+1.0, y+1.0, z);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(x-1.0, y+1.0, z);
  glEnd();
  
}

void Drawer::draw_image(){
	int x = 0, y = 0, z = 0;
	//Texture set-up
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, &texture);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, 3);

  glBegin(GL_QUADS); 
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-1.0, y-1.0, z);
     
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x+1.0, y-1.0, z);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x+1.0, y+1.0, z);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(x-1.0, y+1.0, z);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);

}
