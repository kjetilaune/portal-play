#ifndef NETWORKRECEIVER_H_
#define NETWORKRECEIVER_H_

#include "INetworkReceiver.h"
#include "IReceiverCallback.h"

#include <memory>
#include <thread>


/*
 * A class representing a Network Receiver that uses TCP as transport.
 */
class NetworkReceiver
  : public INetworkReceiver {
public:
  NetworkReceiver(int heigth, 
                  int width, 
                  IReceiverCallback* caller);
  virtual ~NetworkReceiver() {}

// INetworkReceiver
public:
  virtual void Listen(int serverPort);

private:
  void _Listen(int serverPort);

private:
  int _heigth;
  int _width;

  int _socket;
  std::thread _socketListenerThread;

  IReceiverCallback* _caller;

};
typedef std::shared_ptr<NetworkReceiver> NetworkReceiverPtr;

#endif //NETWORKRECEIVER_H_
