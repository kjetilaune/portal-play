#ifndef LOCALPLAYER_H_
#define LOCALPLAYER_H_

#include "player.h"
#include "camera_handler.h"
#include "IntrinsicCameraParameters.h"
#include "network/NetworkSender.h"
#include "bullet.h"

#include <memory>
#include <string>


/*
 *
 */
class LocalPlayer
  : public Player {
    
public:
  LocalPlayer(std::string name, 
              IntrinsicCameraParameters, 
              float width_in_cm, 
              float height_in_cm,
              std::string ipAddress,
              int portNumber,
              int streamWidth,
              int streamHeigth);
  virtual ~LocalPlayer() {}

// From Player
public:
  virtual cv::Mat getImage();
  virtual FaceData getFaceData();

public:
  int get_width();
  int get_height();
  
  //Must be called in order to calculate new positions
  void update();
  void updateRemotePlayer();
  bool is_fire_button_pushed();
  int get_selection_direction();

  int hit;
  int shoot;
  int direction;

private:
  float pixel_to_cm(int, int);
	void find_face();
  void calculate_optical_flow();
  

private:
  //OpenCv members
	const std::string frontalface_cascade = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
	cv::CascadeClassifier frontalface_cascade_classifier;
  
	float screen_width_in_cm;
	float screen_height_in_cm;
	IntrinsicCameraParameters intrinsicCameraParameters;

  //Object members
  CameraHandler *camera_handler = NULL;
  NetworkSenderPtr _sender;

  cv::Mat resized_gray_image, previous_gray_image, current_threshold_image;
  Bullet *bullet = NULL;
};
typedef std::shared_ptr<LocalPlayer> LocalPlayerPtr;

#endif //LOCALPLAYER_H_
