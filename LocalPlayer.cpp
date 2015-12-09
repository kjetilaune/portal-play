#include "LocalPlayer.h"


const int FH = 19;

int portNumber2;
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
  
  portNumber2 = portNumber;
  if (portNumber2%2 == 1)
    camera_handler = new CameraHandler("../media/test_video2.mov");
  else
    camera_handler = new CameraHandler();
  screen_width_in_cm = width_in_cm;
  screen_height_in_cm = height_in_cm;
  frontalface_cascade_classifier.load(frontalface_cascade);
  intrinsicCameraParameters = param;
  
  // Init NetworkSender.
  _sender.reset(new NetworkSender(streamWidth, streamHeigth, portNumber, ipAddress, NULL));

  if (portNumber2%2 == 1){
    _currentImg = camera_handler->get_image_from_video();
    _currentImg = camera_handler->get_image_from_video();
  }
  else{
    _currentImg = camera_handler->get_image_from_camera();
    _currentImg = camera_handler->get_image_from_camera();
  }
  //_sender->Send(_currentImg);

  cv::Mat gray_image;
  if (_currentImg.channels() > 1)
    cv::cvtColor(_currentImg, gray_image, CV_RGB2GRAY);
  else
    gray_image = _currentImg;

  double aspect_ratio = _currentImg.size().width*1.0 / _currentImg.size().height;
  resize(gray_image, resized_gray_image, cv::Size(320.0, (int)(320.0/aspect_ratio)));

  
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

void LocalPlayer::calculate_optical_flow(){
  double aspect_ratio = _currentImg.size().width*1.0 / _currentImg.size().height;

  cv::Mat previous_gray_image2 = resized_gray_image.clone();
  cv::resize(previous_gray_image2, previous_gray_image, cv::Size(320.0, (int)(320.0/aspect_ratio)));

  cv::Mat gray_image;
  if (_currentImg.channels() > 1)
    cv::cvtColor(_currentImg, gray_image, CV_RGB2GRAY);
  else
    gray_image = _currentImg;
  
  cv::resize(gray_image, resized_gray_image, cv::Size(320.0, (int)(320.0/aspect_ratio)));
  
  //Calculate optical flow
  cv::Mat flow(previous_gray_image.size(), CV_32FC1), flow_downscaled;
  calcOpticalFlowFarneback(previous_gray_image, resized_gray_image, flow_downscaled, 0.5, 1, 3, 1, 10, 1.1, 0);
   for (int i = 0; i < flow_downscaled.rows; i++){
    for (int j = 0; j < flow_downscaled.cols; j++){
      cv::Point2f p = flow_downscaled.at<cv::Point2f>(i,j);
      flow.at<float>(i,j) = sqrt(p.x*p.x + p.y*p.y);
    } 
  }

  cv::Mat a, thresholded_flow_image;
  cv::resize(flow, a, cv::Size(_currentImg.size().width, _currentImg.size().height));  
  cv::threshold(a, thresholded_flow_image, 10, 255, cv::THRESH_BINARY);

  current_threshold_image = thresholded_flow_image.clone();

}

bool LocalPlayer::is_fire_button_pushed(){
  cv::Rect fire_rect(20, 20, 160, 160);
  cv::Mat right_square(current_threshold_image, fire_rect);
  if (cv::countNonZero(right_square) > 2000){
    this->shoot = 1;
    return true;
  }
  return false;
  
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
  //std::cout << (portNumber2%2 == 1) << std::endl;
  if (portNumber2%2 == 1)
    _currentImg = camera_handler->get_image_from_video();
  else
    _currentImg = camera_handler->get_image_from_camera();
  find_face();
  calculate_optical_flow();

  //Shows optical flow
  //cv::namedWindow( "DisplayWindow", cv::WINDOW_AUTOSIZE );
  //cv::imshow("DisplayWindow", current_threshold_image);
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
  msg.hit = this->hit;
  hit = 0;
  msg.shoot = this->shoot;
  this->shoot = 0;

  _sender->Send(this->_currentImg, msg);
}
