#include "LocalPlayer.h"


//-------------------------------------------------------------------------
LocalPlayer::LocalPlayer(std::string name)
  : Player(name) {

  camera_handler = new CameraHandler();  
    
}

cv::Mat LocalPlayer::getImage() {
  return camera_handler->get_image_from_camera();
}

FaceData LocalPlayer::getFaceData() {



}