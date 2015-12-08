#include "LocalPlayer.h"


const int FH = 19;

//-------------------------------------------------------------------------
LocalPlayer::LocalPlayer(std::string name, 
                         IntrinsicCameraParameters param, 
                         float width_in_cm, 
                         float height_in_cm,
                         std::string ipAddress,
                         int portNumber,
                         int streamWidth,
                         int streamHeigth)
  : Player(name) {

  camera_handler = new CameraHandler();
  screen_width_in_cm = width_in_cm;
  screen_height_in_cm = height_in_cm;
  frontalface_cascade_classifier.load(frontalface_cascade);
  intrinsicCameraParameters = param;
  
  // Init NetworkSender.
  _sender.reset(new NetworkSender(streamWidth, streamHeigth, portNumber, ipAddress, NULL));

  _currentImg = camera_handler->get_image_from_camera();
  _sender->Send(_currentImg);
}

float LocalPlayer::pixel_to_cm(int x, int rec_width){
  if (rec_width > 0){
    float pixel_per_cm = rec_width / (FH*0.8);
    float b = _currentImg.size().width/2.0 - x;
    return b/pixel_per_cm;
  }
  return 0;
}

void LocalPlayer::find_face(){
  std::vector<cv::Rect> rect;
  cv::Mat gray_image, gray_image_downsized;
  cv::cvtColor(_currentImg, gray_image, CV_RGB2GRAY);
  cv::resize(gray_image, gray_image_downsized, cv::Size(300, 300*gray_image.size().height/gray_image.size().width));

  frontalface_cascade_classifier.detectMultiScale(gray_image_downsized, rect, 1.1, 2, CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(25,25));

  //Find largest face
  cv::Scalar color(0,255,255);
  cv::Rect max_rect;
  if(rect.size() > 0)
    max_rect = rect[0];
  for (int i = 0; i < rect.size(); i++){
    if (rect[i].width > max_rect.width)
      max_rect = rect[i];
  }
  max_rect.x = max_rect.x*gray_image.size().width/300;
  max_rect.y = max_rect.y*gray_image.size().height/(300*gray_image.size().height/gray_image.size().width);
  max_rect.width = max_rect.width*gray_image.size().width/300;
  max_rect.height = max_rect.height*gray_image.size().height/(300*gray_image.size().height/gray_image.size().width);
  if (true)
    //box is 0.8*height
    rectangle(_currentImg, cv::Point(max_rect.x + 0.1*max_rect.width, max_rect.y), cv::Point(max_rect.x + 0.9*max_rect.width, max_rect.y + max_rect.height), color, 1);  

  float x, y, z;

  //Calculate x,y,z in cm
  z = intrinsicCameraParameters.fy * (FH) / (max_rect.height);
  x = pixel_to_cm(max_rect.x + max_rect.width/2.0, max_rect.width); //NOT sure why 1.25 gives nice results...
  y = ((_currentImg.size().height/2.0 - (max_rect.y + max_rect.height/2)) / (max_rect.height / FH));

  if (x < -screen_width_in_cm/2)
    x = -screen_width_in_cm/2 + 0.1;
  if (x > screen_width_in_cm/2)
    x = screen_width_in_cm/2 - 0.1;

  if (y < -screen_height_in_cm/2)
    y = -screen_height_in_cm/2 + 0.1;
  if (y > screen_height_in_cm/2)
    y = screen_height_in_cm/2 - 0.1;

  _faceData.center = cv::Point3f(x, y, z);
  _faceData.topleft = cv::Point2f(x - FH*0.8/2, y + FH/2);
  _faceData.topright = cv::Point2f(x + FH*0.8/2, y + FH/2);
  _faceData.downleft = cv::Point2f(x - FH*0.8/2, y - FH/2);
  _faceData.downright = cv::Point2f(x + FH*0.8/2, y - FH/2);
}

cv::Mat LocalPlayer::getImage() {
  return _currentImg;
}

FaceData LocalPlayer::getFaceData() {
  return _faceData;
}

int LocalPlayer::get_width(){
  return camera_handler->get_width();
}

int LocalPlayer::get_height(){
  return camera_handler->get_height();
}

void LocalPlayer::update(){
  this->_currentImg = camera_handler->get_image_from_camera();
  find_face();

  updateRemotePlayer();
}

void LocalPlayer::updateRemotePlayer() {
  
  if(_sender->isBuisy() == true)
    return;
  
  // Build Message.
  Message msg;
  msg.center = _faceData.center;
  msg.topleft = _faceData.topleft;
  msg.topright = _faceData.topright;
  msg.downleft = _faceData.downleft;
  msg.downright = _faceData.downright;

  _sender->Send(this->_currentImg);
}
