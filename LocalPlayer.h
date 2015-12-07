#ifndef LOCALPLAYER_H_
#define LOCALPLAYER_H_

#include "player.h"
#include "camera_handler.h"
#include "IntrinsicCameraParameters.h"

#include <memory>
#include <string>


/*
 *
 */
class LocalPlayer
  : public Player {
    
public:
  LocalPlayer(std::string name, IntrinsicCameraParameters, float, float);
  virtual ~LocalPlayer() {}

// From Player
public:
  virtual cv::Mat getImage();
  virtual FaceData getFaceData();
  int get_width();
  int get_height();
  
  //Must be called in order to calculate new positions
  void update();

private:
	const String frontalface_cascade = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
	cv::CascadeClassifier frontalface_cascade_classifier;
	CameraHandler *camera_handler = NULL;
	float screen_width_in_cm;
	float screen_height_in_cm;
	IntrinsicCameraParameters intrinsicCameraParameters;

	//Move to player
	const int FH = 19;

	float pixel_to_cm(int, int);
	void find_face();

};
typedef std::shared_ptr<LocalPlayer> LocalPlayerPtr;

#endif //LOCALPLAYER_H_
