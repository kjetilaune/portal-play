#ifndef LOCALPLAYER_H_
#define LOCALPLAYER_H_

#include "player.h"
#include "camera_handler.h"
#include "IntrinsicCameraParameters.h"
#include "network/NetworkSender.h"
#include "network/ISenderCallback.h"

#include <memory>
#include <string>


/*
 *
 */
class LocalPlayer
  : public Player,
    public ISenderCallback {
    
public:
  LocalPlayer(std::string name, IntrinsicCameraParameters, float, float);
  virtual ~LocalPlayer() {}

// ISenderCallback
public:
  virtual void OnSentCompleted(bool sendResult); 

// From Player
public:
  virtual cv::Mat getImage();
  virtual FaceData getFaceData();

public:
  int get_width();
  int get_height();
  
  //Must be called in order to calculate new positions
  void update();

private:
  float pixel_to_cm(int, int);
	void find_face();

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
};
typedef std::shared_ptr<LocalPlayer> LocalPlayerPtr;

#endif //LOCALPLAYER_H_
