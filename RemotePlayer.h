#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_

#include "player.h"

#include <memory>


/*
 *
 */
class RemotePlayer
  : public Player {
    
public:
  RemotePlayer(std::string name);
  virtual ~RemotePlayer() {}

// From Player
public:
  virtual cv::Mat getImage() {}
  virtual FaceData getFaceData() {}

private:

};
typedef std::shared_ptr<RemotePlayer> RemotePlayerPtr;

#endif //REMOTEPLAYER_H_
