#include "NetworkReceiver.h"
#include "NetworkSender.h"
#include "IReceiverCallback.h"
#include "ISenderCallback.h"
#include "IReceiverCallback.h"
#include "Util.h"

#include<stdio.h>
#include <chrono>
#include <thread>


const std::string kIpAddress = "127.0.0.1";
const int kPortNumber = 11224;
const int kWidth = 320;
const int kHeight = 240;

//-------------------------------------------------------------------------
class NetworkTest
  : public IReceiverCallback,
    public ISenderCallback {

public:
  NetworkTest() {}
  virtual ~NetworkTest() {}

//IReceiverCallback
public:
  virtual void OnReceived(cv::Mat mat, Message msg) {
    Info("OnReceived()");

    // Show image we just received.
    cv::imshow("NetworkTest", mat);
  }

//ISenderCallback
public:
  virtual void OnSentCompleted(bool sendResult) {
    Info("OnSendCompleted()");

    // Now that the sending is completed we can send the next image.
    cv::Mat image;
    _capture >> image; 
    _sender->Send(image);
  }

public:
  void StartTest() {
    // Set up network.
    _receiver.reset(new NetworkReceiver(kWidth, kHeight, this));
    _receiver->Listen(kPortNumber);

    _sender.reset(new NetworkSender(kWidth, kHeight, kPortNumber, kIpAddress, this));

    // Capture image and Show it.    
    _capture.open(0);
    cv::Mat image;
    _capture >> image;

    cv::namedWindow("NetworkTest", CV_WINDOW_AUTOSIZE);     
    cv::imshow("NetworkTest", image);    

    // Init transmission storm.
    _sender->Send(image);
  }

private:
  NetworkReceiverPtr _receiver;
  NetworkSenderPtr _sender;
  cv::VideoCapture _capture;

};

//-------------------------------------------------------------------------
int main(int argc, char** argv) {

  NetworkTest* test = new NetworkTest();
  test->StartTest();

  BlockUntilKeypress();
  
  return 0;
}
