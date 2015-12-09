#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_

#include "player.h"
#include "network/NetworkReceiver.h"
#include "network/IReceiverCallback.h"

#include <memory>


/*
 * A class representing a remote player. It gets the
 * remote data by opening a TCP server.
 */
class RemotePlayer
  : public Player,
    public IReceiverCallback {
    
public:
  RemotePlayer(std::string playerName,
               int heigth,
               int width,
               int serverPort);
  virtual ~RemotePlayer() {}

// From Player
public:
  virtual cv::Mat getImage();
  virtual FaceData getFaceData();
  virtual void drawBullet();
  int hit;
  int shoot;
//IReceiverCallback
public:
  virtual void OnReceived(cv::Mat mat, Message msg);

private:
  NetworkReceiverPtr _receiver;
  

};
typedef std::shared_ptr<RemotePlayer> RemotePlayerPtr;

#endif //REMOTEPLAYER_H_
