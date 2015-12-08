#ifndef INETWORKRECEIVER_H_
#define INETWORKRECEIVER_H_

#include <memory>

/*
 * A Interface representing a Network Receiver.
 */
class INetworkReceiver {

public:
  virtual void Listen(int serverPort) = 0;

};
typedef std::shared_ptr<INetworkReceiver> INetworkReceiverPtr;

#endif //INETWORKRECEIVER_H_
