typedef struct _IntrinsicCameraParameters IntrinsicCameraParameters;
struct _IntrinsicCameraParameters {
  float fovx;
  float fovy;
  float focalLength;
  float principalPointX;
  float principalPointY;
  float fx;
  float fy;
  float k1;
  float k2;
  float p1;
  float p2;
  cv::Mat cameraMatrix;
  std::vector<double> distCoeffs;
};