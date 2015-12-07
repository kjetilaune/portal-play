#ifndef LOCALPLAYER_H_
#define LOCALPLAYER_H_

#include "player.h"

#include <memory>
#include <string>


/*
 *
 */
class LocalPlayer
  : public Player {
    
public:
  LocalPlayer(std::string name);
  virtual ~LocalPlayer() {}

// From Player
public:
  virtual cv::Mat getImage() {}
  virtual FaceData getFaceData() {}

private:
	CameraHandler *camera_handler = NULL;

};
typedef std::shared_ptr<LocalPlayer> LocalPlayerPtr;

#endif //LOCALPLAYER_H_
