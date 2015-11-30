#include <stdio.h>

#include "talk/app/webrtc/peerconnection.h"
#include "talk/app/webrtc/peerconnectionfactory.h"
#include "talk/app/webrtc/peerconnectioninterface.h"

int main(void) {
  webrtc::PeerConnectionFactoryInterface* p;
  p = webrtc::CreatePeerConnectionFactory(
      NULL, NULL, NULL, NULL, NULL);

  return 0;
}
