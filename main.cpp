// Skeleton Code for CS290I Homework 1
// 2012, Jon Ventura and Chris Sweeney

// adapt the include statements for your system:

// For OpenCV 2.X use this import statement: 
//#include <opencv/cv.h>

// For OpenCV 3.X use this import statement: 
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <cstdio>
#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>

#include "eigen/Eigen/Dense"
#include "eigen/Eigen/Geometry"

#include "player.h"
#include "drawer.h"
#include "camera_handler.h"

using namespace cv;
using namespace std;


int width = 2880;
int height = 1800;
int current_quad = 9, current_quad_z;
const int number_of_quads = 10;
//const float screen_width_in_cm = 33.2;22.1
//const float screen_height_in_cm = 21.35;12.8
const float screen_width_in_cm = 22.1;
const float screen_height_in_cm = 12.8;
const float camera_distance_from_center = screen_height_in_cm/2 + 0.5;
double  x, y, z, 
        near = 1, far = 100;
double l, r, b, t, ratio;
bool blend_mode = true;
bool in_bump_mode = false;
bool in_bump_ascending = true;
bool first = true;
bool left_button_pressed = false;
bool right_button_pressed = false;



cv::Mat image, gray_image, resized_gray_image, target_texture, flow_image,
  thresholded_flow_image, current_threshold_image;
//Intrinsic camera parameters
float fovx, fovy, focalLength, principalPointX, principalPointY, fx, fy, k1, k2, p1, p2;
Mat cameraMatrix;
vector<double> distCoeffs;
vector<Rect> rect;

float quad_x[number_of_quads];
float quad_y[number_of_quads];
float quad_z[number_of_quads];


const String frontalface_cascade = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
const String texture_path = "/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/hw3/targettexture2.png";
CascadeClassifier frontalface_cascade_classifier;
const int FH = 17; // faceheight

Drawer *drawer;
CameraHandler *camera_handler;

// a useful function for displaying your coordinate system
void drawAxes(float length)
{
  glPushAttrib(GL_POLYGON_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT) ;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) ;
  glDisable(GL_LIGHTING) ;

  glBegin(GL_LINES) ;
  glColor3f(1,0,0) ;
  glVertex3f(0,0,0) ;
  glVertex3f(length,0,0);

  glColor3f(0,1,0) ;
  glVertex3f(0,0,0) ;
  glVertex3f(0,length,0);

  glColor3f(0,0,1) ;
  glVertex3f(0,0,0) ;
  glVertex3f(0,0,length);
  glEnd() ;


  glPopAttrib() ;
}



void cross_product(Eigen::VectorXd& vec, Eigen::VectorXd a, Eigen::VectorXd b){
  vec(0) = a(1)*b(2) - a(2)*b(1);
  vec(1) = a(2)*b(0) - a(0)*b(2);
  vec(2) = a(0)*b(1) - a(1)*b(0);
}



void find_clipping_planes(){
   //Screen corners- and eye coordinates
   Eigen::VectorXd  pa(3), pb(3), pc(3), pe(3);
   Eigen::VectorXd vr(3), vu(3), vn(3), va(3), vb(3), vc(3);

   pa << -screen_width_in_cm/2.0,-screen_height_in_cm/2.0,0;
   pb << screen_width_in_cm/2.0,-screen_height_in_cm/2.0,0;
   pc << -screen_width_in_cm/2.0,screen_height_in_cm/2.0,0;
   pe << x, y, z;
   
   vr = pb - pa;
   vu = pc - pa;

   vr.normalize();
   vu.normalize();
   cross_product(vn, vr, vu);
   vn.normalize();

   va = pa - pe;
   vb = pb - pe;
   vc = pc - pe;

   double d = -va.dot(vn);

   l = vr.dot(va) * near / d;
   r = vr.dot(vb) * near / d;
   b = vu.dot(va) * near / d;
   t = vu.dot(vc) * near / d;

   double nn = pe.norm();

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(l,r,b,t,near,far+d);

   double M[16];

   M[0] = vr(0); M[4] = vr(1); M[8]  = vr(2);
   M[1] = vu(0); M[5] = vu(1); M[9]  = vu(2);
   M[2] = vn(0); M[6] = vn(1); M[10] = vn(2);

   M[15] = 1.0;

   glMultMatrixd(M);

   glTranslatef(-pe(0), -pe(1), -pe(2));
}



void display()
{
  // clear the window
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Set up lighting
  glEnable(GL_LIGHTING );
  glEnable(GL_LIGHT0 );
  glEnable( GL_COLOR_MATERIAL);
  glEnable(GL_BACK);
  
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  
  // show the current camera frame
  //based on the way cv::Mat stores data, you need to flip it before displaying it
  cv::Mat tempimage, temp2;
  cv::flip(image, tempimage, -1);
  double windowWidth = glutGet(GLUT_SCREEN_WIDTH);
  double windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
  if (!blend_mode){
    if (!tempimage.empty())
      resize(tempimage, temp2, Size(320, 240));

    glDrawPixels( temp2.size().width, temp2.size().height, GL_BGR, GL_UNSIGNED_BYTE, temp2.ptr() );
  }
  else{
    glDrawPixels( tempimage.size().width, tempimage.size().height, GL_BGR, GL_UNSIGNED_BYTE, tempimage.ptr() );
  }
  //////////////////////////////////////////////////////////////////////////////////
  // Here, set up new parameters to render a scene viewed from the camera.

  //glViewport(0, 0, 2880, 1800);
  glViewport(0, 0, tempimage.size().width, tempimage.size().height);

  find_clipping_planes();
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  drawer->draw_view_box(screen_width_in_cm, screen_height_in_cm);
  //drawViewBox(screen_width_in_cm, screen_height_in_cm);
  //draw_random_quads();

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0 );
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_BACK);
 

  // show the rendering on the screen
  glutSwapBuffers();

  // post the next redisplay
  glutPostRedisplay();
}

void reshape( int w, int h )
{
  // set OpenGL viewport (drawable area)
  glViewport( 0, 0, w, h );
}

void mouse( int button, int state, int x, int y )
{
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
    {

    }
}

void keyboard( unsigned char key, int x, int y )
{
  switch ( key )
    {
    case 'q':
      // quit when q is pressed
      exit(0);
      break;
    
    case 'c':
      blend_mode = !blend_mode;
      break;

    default:
      break;
    }
}


float pixel_to_cm(int x, int rec_width){
  if (rec_width > 0){
    float pixel_per_cm = rec_width / (FH*0.8);
    float b = image.size().width/2.0 - x;
    return b/pixel_per_cm;
  }
  return 0;
}


void idle()
{
  Mat prev, prev_gray;
  // grab a frame from the camera
  image = camera_handler->get_image_from_camera();
  
  double aspect_ratio = image.size().width*1.0 / image.size().height;
  Size s(320, int(320.0/aspect_ratio));

  if (first){
    first = false;
    cvtColor(image, gray_image, CV_RGB2GRAY);
    resize(gray_image, resized_gray_image, s);
    
  }
  else {
    prev_gray = resized_gray_image.clone();

    cvtColor(image, gray_image, CV_RGB2GRAY);
    resize(gray_image, resized_gray_image, s);

    //Calculate optical flow
    Mat flow(resized_gray_image.size(), CV_32FC1), flow_downscaled;
    calcOpticalFlowFarneback(prev_gray, resized_gray_image, flow_downscaled, 0.5, 1, 3, 1, 5, 1.1, 0);
     for (int i = 0; i < flow_downscaled.rows; i++){
      for (int j = 0; j < flow_downscaled.cols; j++){
        Point2f p = flow_downscaled.at<Point2f>(i,j);
        flow.at<float>(i,j) = sqrt(p.x*p.x + p.y*p.y);
      } 
    }

    Mat a;
    resize(flow, a, Size(image.size().width, image.size().height));  
    threshold(a, thresholded_flow_image, 10, 255, THRESH_BINARY);

    current_threshold_image = thresholded_flow_image.clone();

    //drawButtons(image);
  }
  
  //Detect face
  frontalface_cascade_classifier.detectMultiScale(gray_image, rect, 1.1, 2, CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(100,100));
  
  //Find largest face
  Scalar color(0,255,255);
  Rect max_rect;
  if(rect.size() > 0)
    max_rect = rect[0];
  for (int i = 0; i < rect.size(); i++){
    if (rect[i].width > max_rect.width)
      max_rect = rect[i];
  }
  if (true)
    //box is 0.8*height
    rectangle(image, Point(max_rect.x + 0.1*max_rect.width, max_rect.y), Point(max_rect.x + 0.9*max_rect.width, max_rect.y + max_rect.height), color, 1);  

  //Calculate x,y,z in cm
  z = fy * (FH) / (max_rect.height);
  x = pixel_to_cm(max_rect.x + max_rect.width/2.0, max_rect.width); //NOT sure why 1.25 gives nice results...
  y = ((image.size().height/2.0 - (max_rect.y + max_rect.height/2)) / (max_rect.height / FH));

  if (x < -screen_width_in_cm/2)
    x = -screen_width_in_cm/2 + 0.1;
  if (x > screen_width_in_cm/2)
    x = screen_width_in_cm/2 - 0.1;
  cout << -screen_width_in_cm/2;
  cout << x << endl;
}

void populateParameterList(char* s, std::vector<float>& list){
  std::ifstream source;
  source.open(s);
  float line;
  while(source >> line){
    list.push_back(line);
  }
}

void assignParameterVariables(std::vector<float>& list){
  fovx = list[0];
  fovy = list[1];
  focalLength = list[2];
  principalPointX = list[3];
  principalPointY = list[4];
  fx = list[5];
  fy = list[6];
  k1 = list[7];
  k2 = list[8];
  p1 = list[9];
  p2 = list[10];

  cameraMatrix = (Mat_<float>(3,3) << fx, 0, principalPointX, 0, fy, principalPointY, 0, 0, 1);

  distCoeffs.push_back(k1);
  distCoeffs.push_back(k2);
  distCoeffs.push_back(p1);
  distCoeffs.push_back(p2);
}

int main( int argc, char **argv )
{
  //Seed for random generation
  srand (time(NULL));

  Player *p = new Player("Kjetil");
  cout << p->get_name() << endl;


  drawer = new Drawer("/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/hw3/stadium2.jpg");

  //camera_handler = new CameraHandler();

  //Generate random positions
  //populate_quad_position_lists();

  int w,h;

  //Load face recognizer
  frontalface_cascade_classifier.load(frontalface_cascade);

  //Load texture
  target_texture = imread(texture_path, CV_LOAD_IMAGE_UNCHANGED);
    
  if ( argc == 1 ) {
    camera_handler = new CameraHandler();
  } else if ( argc == 2 ) {
    char* paramsPath(argv[1]);
    std::vector<float> paramList;
    populateParameterList(paramsPath, paramList);
    assignParameterVariables(paramList);
    camera_handler = new CameraHandler();
  } else {
    fprintf( stderr, "usage: %s [<filename>]\n", argv[0] );
    return 1;
  }


  // get width and height
  w = camera_handler->get_width();
  h = camera_handler->get_height();
  // On Linux, there is currently a bug in OpenCV that returns 
  // zero for both width and height here (at least for video from file)
  // hence the following override to global variable defaults: 
  width = w ? w : width;
  height = h ? h : height;

  // initialize GLUT
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition( 20, 20 );
  glutInitWindowSize( width, height );
  glutCreateWindow( "OpenGL / OpenCV Example" );

  // set up GUI callback functions
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutMouseFunc( mouse );
  glutKeyboardFunc( keyboard );
  glutIdleFunc( idle );

  // start GUI loop
  glutMainLoop();

  return 0;
}