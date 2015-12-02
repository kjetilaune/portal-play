#include "talk/app/webrtc/peerconnectionfactory.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "webrtc/base/scoped_ptr.h"

namespace  rtcapp {
  
  typedef rtc::scoped_refptr<webrtc::PeerConnectionInterface> 
    PeerConnectionInterfaceRefPtr;
  typedef rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> 
    PeerConnectionFactoryInterfaceRefPtr;
  typedef rtc::scoped_refptr<webrtc::MediaStreamInterface> 
    MediaStreamRefPtr;
  typedef std::shared_ptr<cricket::VideoCapturer> 
    VideoCapturerPtr;

} //  rtcapp namespace 
