#include "NetworkReceiver.h"
#include "NetworkSender.h"
#include "IReceiverCallback.h"
#include "ISenderCallback.h"
#include "IReceiverCallback.h"
#include "Util.h"

#include<stdio.h>
#include <chrono>
#include <thread>


const int kPortNumber = 22514;

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
    cv::imshow("stream_client", mat);
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
    _receiver.reset(new NetworkReceiver(320, 240, this));
    _receiver->Listen(kPortNumber);

    _sender.reset(new NetworkSender(kPortNumber, "127.0.0.1", this));

    // Open Capture.
    _capture.open(0);
    _capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    _capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    // Capture image and Show it.
    cv::Mat image;
    _capture >> image;

    cv::namedWindow("stream_client", CV_WINDOW_AUTOSIZE);     
    cv::imshow("stream_client", image);    

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
