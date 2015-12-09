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

void Drawer::draw_fire_button(cv::Mat &image){
  cv::Point p;
  p.x = image.size().width - 100;
  p.y = image.size().height - 100;
  int radius = 70;
  cv::Scalar color(0,0,255);

  line(image, cv::Point(p.x - radius + 15, p.y), cv::Point(p.x - 15, p.y), color, 3);
  line(image, cv::Point(p.x + radius - 15, p.y), cv::Point(p.x + 15, p.y), color, 3);
  line(image, cv::Point(p.x, p.y + radius - 15), cv::Point(p.x, p.y + 15), color, 3);
  line(image, cv::Point(p.x, p.y - radius + 15), cv::Point(p.x, p.y - 15), color, 3);
  circle(image, p, 4, color, -1);
	circle(image, p, radius, color, 5);
}

void Drawer::draw_lives(cv::Mat &image, float numberOfLives){
  cv::Mat mask = cv::imread("../media/heart64.png", CV_LOAD_IMAGE_UNCHANGED);

  cv::Mat resized_mask;
  cv::resize(mask, resized_mask, cv::Size(50, 50));
  cv::flip(resized_mask, resized_mask, -1);
  for (int i = 0; i < numberOfLives; i++){
    overlayImage(image, resized_mask, image, cv::Point2i(image.size().width/2 - numberOfLives/2*100 + 100*i, image.size().height - 100));
  }
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

//Function found at http://jepsonsblog.blogspot.com/2012/10/overlay-transparent-image-in-opencv.html
void Drawer::overlayImage(const cv::Mat &background, const cv::Mat &foreground, 
  cv::Mat &output, cv::Point2i location)
{
  background.copyTo(output);


  // start at the row indicated by location, or at row 0 if location.y is negative.
  for(int y = std::max(location.y , 0); y < background.rows; ++y)
  {
    int fY = y - location.y; // because of the translation

    // we are done of we have processed all rows of the foreground image.
    if(fY >= foreground.rows)
      break;

    // start at the column indicated by location, 

    // or at column 0 if location.x is negative.
    for(int x = std::max(location.x, 0); x < background.cols; ++x)
    {
      int fX = x - location.x; // because of the translation.

      // we are done with this row if the column is outside of the foreground image.
      if(fX >= foreground.cols)
        break;

      // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
      double opacity =
        ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])

        / 255.;


      // and now combine the background and foreground pixel, using the opacity, 

      // but only if opacity > 0.
      for(int c = 0; opacity > 0 && c < output.channels(); ++c)
      {
        unsigned char foregroundPx =
          foreground.data[fY * foreground.step + fX * foreground.channels() + c];
        unsigned char backgroundPx =
          background.data[y * background.step + x * background.channels() + c];
        output.data[y*output.step + output.channels()*x + c] =
          backgroundPx * (1.-opacity) + foregroundPx * opacity;
      }
    }
  }
}
