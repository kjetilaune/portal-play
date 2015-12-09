#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <iostream>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>


typedef struct _FaceData FaceData;
struct _FaceData {
  cv::Point3f center;
  cv::Point2f topleft;
  cv::Point2f topright;
  cv::Point2f downright;
  cv::Point2f downleft;
};


class Player{

public:
	Player(std::string name);
  virtual ~Player() {}

  std::string get_name(){return _name;}
	int decrease_lives();
	int increase_lives();

public:
  virtual cv::Mat getImage() = 0;
  virtual FaceData getFaceData() = 0;
  //virtual void drawBullet() = 0;

protected:
  std::string _name;
	int _lives;
  FaceData _faceData;
  cv::Mat _currentImg;
		
};
typedef struct std::shared_ptr<Player> PlayerPtr;

#endif //PLAYER_H_
