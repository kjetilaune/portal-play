#include "RemotePlayer.h"

//-------------------------------------------------------------------------
RemotePlayer::RemotePlayer(std::string playerName,
                           int heigth,
                           int width,
                           int serverPort)
  : Player(playerName) {
    
  _receiver.reset(new NetworkReceiver(width, heigth, this));
  _receiver->Listen(serverPort);

  //cv::namedWindow("NetworkTest", CV_WINDOW_AUTOSIZE);
}

//-------------------------------------------------------------------------
cv::Mat RemotePlayer::getImage() {
  
  return _currentImg;
}

//-------------------------------------------------------------------------
FaceData RemotePlayer::getFaceData() {
  
  return _faceData;
}

//-------------------------------------------------------------------------
void RemotePlayer::OnReceived(cv::Mat mat, Message msg) {
 
  mat.copyTo(_currentImg);

  // Parse FaceData
  FaceData fd;
  fd.center = msg.center;
  fd.topleft = msg.topleft;
  fd.topright = msg.topright;
  fd.downright = msg.downright;
  fd.downleft = msg.downright;

  _faceData = fd;
}
