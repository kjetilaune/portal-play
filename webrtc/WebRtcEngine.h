#include "WebRtcDefinitions.h"

#include "talk/app/webrtc/peerconnectionfactory.h"
#include "talk/app/webrtc/peerconnectioninterface.h"

#include <memory>


namespace rtcapp {

/*
 * A class representing a WebRtc Media Engine.
 */
class WebRtcEngine
  : public webrtc::PeerConnectionObserver,
    public webrtc::CreateSessionDescriptionObserver {
      
public:
  WebRtcEngine();
  virtual ~WebRtcEngine();

// Interface webrtc::PeerConnectionObserver
public:
  virtual void OnStateChange(
      webrtc::PeerConnectionObserver::StateType state_changed) {}
  virtual void OnAddStream(webrtc::MediaStreamInterface* stream) {}
  virtual void OnRemoveStream(webrtc::MediaStreamInterface* stream) {}
  virtual void OnDataChannel(webrtc::DataChannelInterface* channel) {}
  virtual void OnRenegotiationNeeded() {}
  virtual void OnIceChange() {}
  virtual void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);

// Interface webrtc::CreateSessionDescriptionObserver
public:
  virtual void OnSuccess(webrtc::SessionDescriptionInterface* desc);
  virtual void OnFailure(const std::string& error);

// Interface rtc::RefCountInterface
public:
  virtual int AddRef() const { return 1; }
  virtual int Release() const {return 1; }

// Member methods
public:
  bool CreatePeerConnectionFactory();
  bool CreatePeerConnection();
  bool Initialize();
  bool CreateVideoCapturer();
  bool AddStreams();

  bool CreateOffer();

private:
  void _SendMessage(const std::string& json_object);

private:
  PeerConnectionFactoryInterfaceRefPtr _peerConnectionFactoryPtr;
  PeerConnectionInterfaceRefPtr _peerConnectionPtr;
  std::map<std::string, MediaStreamRefPtr> _activeStreams;
  VideoCapturerPtr _videoCapturerPtr;

};
typedef std::shared_ptr<WebRtcEngine> WebRtcEnginePtr;

} // rtc namespace 
