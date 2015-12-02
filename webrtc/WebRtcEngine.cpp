#include "WebRtcEngine.h"

#include "talk/app/webrtc/peerconnection.h"
#include "talk/app/webrtc/peerconnectionfactory.h"
#include "talk/app/webrtc/test/fakeconstraints.h"
#include "talk/app/webrtc/mediaconstraintsinterface.h"
#include "talk/app/webrtc/videosourceinterface.h"
#include "talk/media/webrtc/webrtcvideocapturerfactory.h"
#include "webrtc/base/json.h"
#include "webrtc/test/field_trial.h"

#include <stdio.h>
#include <iostream>


namespace rtcapp {

// Stun Server for PeerConnection creation
const char kStunServer[] = "stun:stun.l.google.com:19302";

// Names used for MediaStream objects.
const char kAudioLabel[] = "audio_label";
const char kVideoLabel[] = "video_label";
const char kStreamLabel[] = "stream_label";

// Names used for a IceCandidate JSON object.
const char kCandidateSdpMidName[] = "sdpMid";
const char kCandidateSdpMlineIndexName[] = "sdpMLineIndex";
const char kCandidateSdpName[] = "candidate";

// Names used for a SessionDescription JSON object.
const char kSessionDescriptionTypeName[] = "type";
const char kSessionDescriptionSdpName[] = "sdp";

//-------------------------------------------------------------------------
WebRtcEngine::WebRtcEngine() {

}

//-------------------------------------------------------------------------
WebRtcEngine::~WebRtcEngine() {

}

// Interface webrtc::PeerConnectionObserver
//-------------------------------------------------------------------------
void WebRtcEngine::OnIceCandidate(const webrtc::IceCandidateInterface* candidate) {

  Json::StyledWriter writer;
  Json::Value jmessage;

  jmessage[kCandidateSdpMidName] = candidate->sdp_mid();
  jmessage[kCandidateSdpMlineIndexName] = candidate->sdp_mline_index();
  std::string sdp;
  if (!candidate->ToString(&sdp)) {
    return;
  }

  jmessage[kCandidateSdpName] = sdp;
  _SendMessage(writer.write(jmessage));
}

// Interface webrtc::CreateSessionDescriptionObserver
//-------------------------------------------------------------------------
void WebRtcEngine::OnSuccess(webrtc::SessionDescriptionInterface* desc) {

}

//-------------------------------------------------------------------------
void WebRtcEngine::OnFailure(const std::string& error) {

}

// Member methods
//-------------------------------------------------------------------------
bool WebRtcEngine::CreatePeerConnectionFactory() {

  // pass parameters (like enable100kbps)
  webrtc::test::InitFieldTrialsFromString("");
  
  _peerConnectionFactoryPtr =
    webrtc::CreatePeerConnectionFactory();

  return _peerConnectionFactoryPtr != NULL;
}

//-------------------------------------------------------------------------
bool WebRtcEngine::CreatePeerConnection() {

  // Ice Servers
  webrtc::PeerConnectionInterface::IceServers servers;
  webrtc::PeerConnectionInterface::IceServer server;
  server.uri = kStunServer;
  servers.push_back(server);

  // Media Constraints
  webrtc::FakeConstraints constraints;
  constraints.AddOptional(webrtc::MediaConstraintsInterface::kEnableDtlsSrtp,
                          "false");

  _peerConnectionPtr =
    _peerConnectionFactoryPtr->CreatePeerConnection(servers,
                                                    &constraints,
                                                    NULL,
                                                    NULL,
                                                    this);

  return _peerConnectionPtr != NULL;
}

//-------------------------------------------------------------------------
bool WebRtcEngine::Initialize() {

  if(CreatePeerConnectionFactory() != true)
    return false;

  if(CreatePeerConnection() != true)
    return false;

  return true;
}

//-------------------------------------------------------------------------
bool WebRtcEngine::CreateVideoCapturer() {

  // Init DeviceManager
  rtc::scoped_ptr<cricket::DeviceManagerInterface> dev_manager(
      cricket::DeviceManagerFactory::Create());
  if (!dev_manager->Init()) {
    return false;
  }
  dev_manager->SetVideoDeviceCapturerFactory(
      new cricket::WebRtcVideoDeviceCapturerFactory());

  // Find Devices
  std::vector<cricket::Device> devs;
  if (!dev_manager->GetVideoCaptureDevices(&devs)) {
    return false;
  }

  // Assign first found device to member
  std::vector<cricket::Device>::iterator dev_it = devs.begin();
  for (; dev_it != devs.end(); ++dev_it) {
    cricket::VideoCapturer* c = NULL;
    c = dev_manager->CreateVideoCapturer(*dev_it);
    if (c != NULL) {
      _videoCapturerPtr.reset(c);
      break;
    }
  }

  return _videoCapturerPtr != NULL;
}

//-------------------------------------------------------------------------
bool WebRtcEngine::AddStreams() {

  // Check if already added
  if (_activeStreams.find(kStreamLabel) != _activeStreams.end())
    return false;
  
  rtc::scoped_refptr<webrtc::AudioTrackInterface> audio_track(
      _peerConnectionFactoryPtr->CreateAudioTrack(
          kAudioLabel, _peerConnectionFactoryPtr->CreateAudioSource(NULL)));
  
  rtc::scoped_refptr<webrtc::VideoTrackInterface> video_track(
      _peerConnectionFactoryPtr->CreateVideoTrack(
          kVideoLabel,
          _peerConnectionFactoryPtr->CreateVideoSource(_videoCapturerPtr.get(),
                                                      NULL)));

  rtc::scoped_refptr<webrtc::MediaStreamInterface> stream =
      _peerConnectionFactoryPtr->CreateLocalMediaStream(kStreamLabel);

  stream->AddTrack(audio_track);
  stream->AddTrack(video_track);

  return true;
}

//-------------------------------------------------------------------------
bool WebRtcEngine::CreateOffer() {

//  _peerConnectionPtr->CreateOffer(this, NULL);
  return true;
}

//-------------------------------------------------------------------------
void WebRtcEngine::_SendMessage(const std::string& json_object) {
  
  std::string message(json_object);
  std::cout << "--- " << message << std::endl;
}

} // rtc namespace 
