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

#include "LocalPlayer.h"
#include "drawer.h"
#include "camera_handler.h"
#include "bullet.h"
#include "bird.h"

#include <tgmath.h> //for log2


using namespace cv;
using namespace std;


int width = 2880;
int height = 1800;
int current_quad = 9, current_quad_z;

int rotcnt = 0;

int bird_degrees = 0;

const int number_of_quads = 10;
//const float screen_width_in_cm = 33.2;22.1
//const float screen_height_in_cm = 21.35;12.8
const float screen_width_in_cm = 22.1;
const float screen_height_in_cm = 12.8;
const float camera_distance_from_center = screen_height_in_cm/2 + 0.5;
double  near = 1, far = 200;
double l, r, b, t, ratio;
bool blend_mode = true;
bool in_bump_mode = false;
bool in_bump_ascending = true;
bool first = true;
bool left_button_pressed = false;
bool right_button_pressed = false;

int last_positions[3][2] = {{0,0},{0,0},{0,0}};
int position_counter = 0;
int x_avg = 0, y_avg = 0;

cv::Mat image, gray_image, resized_gray_image, target_texture, flow_image,
  thresholded_flow_image, current_threshold_image, opponent;

LocalPlayer *local_player;
const int IS_BGR = 0;
const int IS_BGRA = 1;



IntrinsicCameraParameters intrinsicCameraParameters;

vector<Rect> rect;
int quad_x, quad_y, quad_z;

const String frontalface_cascade = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
const String texture_path = "/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/media/heart.png";
CascadeClassifier frontalface_cascade_classifier;
const int FH = 19; // faceheight

Drawer *drawer;
CameraHandler *camera_handler;
Bullet *bullet;
Bird *bird;
Bird *bird1, *bird2, *bird3;

bool hit_animation = false;

time_t first_time, second_time;

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



void find_clipping_planes(float x, float y, float z){
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

void draw_opponent(Mat &opponent, float x, float y, float z, int code, int screen_width_in_cm, int screen_height_in_cm){
  //Texture set-up
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


  uchar* image_data = new uchar[opponent.total()*4];
  Mat temp_rgb, temp_opponent;

  
  Mat opponentRGBA(opponent.size(), CV_8UC4, image_data);
  if (code == IS_BGR)
    cvtColor(opponent, opponentRGBA, CV_BGR2RGBA, 4);
  else if (code == IS_BGRA)
    cvtColor(opponent, opponentRGBA, CV_BGRA2RGBA, 4);


  int xpaddingexp = (int)(log2(opponent.size().width) + 1);
  int ypaddingexp = (int)(log2(opponent.size().height) + 1);
  Mat opponentRGBAFlipped;
  flip(opponentRGBA, opponentRGBAFlipped, -1);

  if (xpaddingexp == 7){
    xpaddingexp = 6;
    ypaddingexp = 6;
  }

  //Fill the Mat with transparent pixels where padded
  copyMakeBorder(opponentRGBAFlipped, temp_opponent,(pow(2,ypaddingexp)-opponent.size().height)/2,(pow(2,ypaddingexp)-opponent.size().height)/2, (pow(2,xpaddingexp)-opponent.size().width)/2, (pow(2,xpaddingexp)-opponent.size().width)/2,BORDER_CONSTANT, Scalar(0,0,0,0));

  //glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, target_texture.size().width, target_texture.size().height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)target_texture.ptr());
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, temp_opponent.size().width, temp_opponent.size().height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)temp_opponent.ptr());

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, 3);

  //cout << (int)(log2(image.size().width) + 1) << " " << image.size().width << endl;

  //Using the ratio between pixels and cm for both padded and unpadded images
  float quad_w = (pow(2, xpaddingexp) * screen_width_in_cm)/(opponent.size().width*2);
  float quad_h = (pow(2, ypaddingexp) * screen_height_in_cm)/(opponent.size().height*2);
  cout << xpaddingexp << endl;
  glBegin(GL_QUADS); 
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-quad_w, y-quad_h, z);
     
    glTexCoord2f(1.0, 0.0);
    glVertex3f(x+quad_w, y-quad_h, z);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x+quad_w, y+quad_h, z);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(x-quad_w, y+quad_h, z);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}

double get_random_double(int min, int max){
  return rand() % (abs(max) + abs(min)) - abs(min);
}

void display_hit_animation(Mat &image, float x, float y, float z){
  second_time = time(NULL);
    
  if (difftime(second_time, first_time) > 3){
    hit_animation = false;
  }

  glDrawPixels( image.size().width, image.size().height, GL_BGR, GL_UNSIGNED_BYTE, image.ptr() );
  glViewport(0, 0, image.size().width, image.size().height);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  gluPerspective(intrinsicCameraParameters.fovy, image.size().width*1.0/image.size().height, 1, 500); 

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

  bird_degrees += 5;
  if (bird_degrees >= 360)
    bird_degrees = 0;

  glEnable( GL_DEPTH_TEST );
  glPushMatrix();
    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_TRUE);
    glTranslatef(0, 0, -z);
    glRectd(x - FH*0.8/2, y - FH/2.0, x + FH*0.8/2, y + FH/2.0);
  glPopMatrix();
    
  glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

  glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, -z);
    glTranslatef(0,0,-20);
    glRotatef(bird_degrees, 0,1,0);
    glTranslatef(0,0,20);
    bird1->draw(0,0,0,0);
    //glDisable( GL_DEPTH_TEST );
  glPopMatrix();

  glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, -z);
    glTranslatef(0,0,-20);
    glRotatef(bird_degrees + 120, 0,1,0);
    glTranslatef(0,0,20);
    bird2->draw(0,0,0,0);
    //glDisable( GL_DEPTH_TEST );
  glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, -z);
    glTranslatef(0,0,-20);
    glRotatef(bird_degrees + 240, 0,1,0);
    glTranslatef(0,0,20);
    bird3->draw(0,0,0,0);
    glDisable( GL_DEPTH_TEST );
  glPopMatrix();



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
  
  //calculate_average_face();

  if (hit_animation){
    display_hit_animation(tempimage, local_player->getFaceData().center.x, local_player->getFaceData().center.y, local_player->getFaceData().center.z);
  }

  else{

    if (!blend_mode){
      if (!tempimage.empty())
        resize(tempimage, temp2, Size(320, 240));

      glDrawPixels( temp2.size().width, temp2.size().height, GL_BGR, GL_UNSIGNED_BYTE, temp2.ptr() );
    }
    else{
      Mat opponent2;
      flip(opponent, opponent2, -1);
      glDrawPixels( opponent2.size().width, opponent2.size().height, GL_BGR, GL_UNSIGNED_BYTE, opponent2.ptr() );
    }

    glViewport(0, 0, tempimage.size().width, tempimage.size().height);


    find_clipping_planes(local_player->getFaceData().center.x, local_player->getFaceData().center.y, local_player->getFaceData().center.z);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawer->draw_view_box(screen_width_in_cm, screen_height_in_cm);
    glEnable(GL_DEPTH_TEST);
    
    rotcnt+= 10;
    
    glPushAttrib(GL_POLYGON_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT) ;
    glDisable(GL_LIGHTING) ;

    //glRotatef(rotcnt, 0, 1, 0);
    //bird->draw(0,0,0, rotcnt%360);

    if (bullet != NULL){
      


      bullet->draw();

      if (bullet->x < quad_x + 1 && bullet->x > quad_x - 1 && bullet->y < quad_y + 1 && bullet->y > quad_y - 1 && bullet->z <= quad_z){
        if (bullet->z < -220){
          bullet = NULL;
        }
        first_time = time(NULL);
        hit_animation = true;

        bullet = NULL;
        cout << " HIT " << endl;
        quad_x = get_random_double(-8, 8);
        quad_y = get_random_double(-4, 4);
        quad_z = get_random_double(-20, 0);
      }
      
    }
    if (!first)
      draw_opponent(opponent, 0, 0, -180, IS_BGR, screen_width_in_cm, screen_height_in_cm);
    draw_opponent(target_texture, 0, 0, -150, IS_BGRA, FH, FH);
    
    //drawViewBox(screen_width_in_cm, screen_height_in_cm);
    //draw_random_quads();

    drawer->draw_cross_hair(local_player->getFaceData().center.x, local_player->getFaceData().center.y, local_player->getFaceData().center.z);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0 );
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BACK);
 }

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

void keyboard( unsigned char key, int xxx, int yyy )
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
    case 'f':
    if (bullet == NULL)
        bullet = new Bullet(local_player->getFaceData().center.x, local_player->getFaceData().center.y, local_player->getFaceData().center.z);
      break;
    default:
      break;
    }
}


void idle()
{
  local_player->update();
  Mat prev, prev_gray;
  // grab a frame from the camera
  image = local_player->getImage();
  opponent = camera_handler->get_image_from_opponent();

  //namedWindow( "DisplayWindow", WINDOW_AUTOSIZE );
  //imshow("DisplayWindow", opponent);

  double aspect_ratio = image.size().width*1.0 / image.size().height;
  Size s(320, int(320.0/aspect_ratio));
/*
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
*/
  first = false;

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
  intrinsicCameraParameters.fovx = list[0];
  intrinsicCameraParameters.fovy = list[1];
  intrinsicCameraParameters.focalLength = list[2];
  intrinsicCameraParameters.principalPointX = list[3];
  intrinsicCameraParameters.principalPointY = list[4];
  intrinsicCameraParameters.fx = list[5];
  intrinsicCameraParameters.fy = list[6];
  intrinsicCameraParameters.k1 = list[7];
  intrinsicCameraParameters.k2 = list[8];
  intrinsicCameraParameters.p1 = list[9];
  intrinsicCameraParameters.p2 = list[10];

  intrinsicCameraParameters.cameraMatrix = (Mat_<float>(3,3) << list[5], 0, list[3], 0, list[6], list[4], 0, 0, 1);

  intrinsicCameraParameters.distCoeffs.push_back(intrinsicCameraParameters.k1);
  intrinsicCameraParameters.distCoeffs.push_back(intrinsicCameraParameters.k2);
  intrinsicCameraParameters.distCoeffs.push_back(intrinsicCameraParameters.p1);
  intrinsicCameraParameters.distCoeffs.push_back(intrinsicCameraParameters.p2);
}

int main( int argc, char **argv )
{
  //Seed for random generation
  srand (time(NULL));




  drawer = new Drawer("/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/hw3/stadium2.jpg");

  bird = new Bird();

  bird1 = new Bird();
  bird2 = new Bird();
  bird3 = new Bird();

  


  quad_x = get_random_double(-8, 8);
  quad_y = get_random_double(-4, 4);
  quad_z = get_random_double(-100, 0);
  //Generate random positions
  //populate_quad_position_lists();

  int w,h;

  
  //Load texture
  target_texture = imread(texture_path, CV_LOAD_IMAGE_UNCHANGED);
    
  if ( argc == 1 ) {
    local_player = new LocalPlayer("Kjetil", intrinsicCameraParameters, screen_width_in_cm, screen_height_in_cm);
  } else if ( argc == 2 ) {
    char* paramsPath(argv[1]);
    std::vector<float> paramList;
    populateParameterList(paramsPath, paramList);
    assignParameterVariables(paramList);

    local_player = new LocalPlayer("Kjetil", intrinsicCameraParameters, screen_width_in_cm, screen_height_in_cm);
    //camera_handler = new CameraHandler();
  } else if (argc == 3){
    char* paramsPath(argv[1]);
    std::vector<float> paramList;
    populateParameterList(paramsPath, paramList);
    assignParameterVariables(paramList);

    local_player = new LocalPlayer("Kjetil", intrinsicCameraParameters, screen_width_in_cm, screen_height_in_cm);

    //Remove when remoteplayer can provide images
    camera_handler = new CameraHandler(argv[2]);
  } else {
    fprintf( stderr, "usage: %s [<filename>]\n", argv[0] );
    return 1;
  }

  

  // get width and height
  w = local_player->get_width();
  h = local_player->get_height();
  cout << w << " " << h << endl;
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
