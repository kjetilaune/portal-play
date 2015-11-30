# Builds a application that statically links to the WebRtc libraries.
# More information: http://www.webrtc.org/native-code/development
# ('chromium_revision': 'ed2e3fb8a158183b2746fdaf9ad964cc1e5b9240')

cmake_minimum_required(VERSION 3.3)
project(WebRtcConnector)

# Set this to your built of WebRtc
set(webrtc_SOURCEPATH
  "/devel/git/google_webrtc/webrtc_Nov18/src")

# Application level Code
set(webrtcconnector_SRCS
  "WebRtcConnector.cpp")

add_executable(WebRtcConnector 
  ${webrtcconnector_SRCS})

# WebRtc dependency
include_directories(WebRtcConnector
  ${webrtc_SOURCEPATH}
  ${webrtc_SOURCEPATH}/third_party
  ${webrtc_SOURCEPATH}/third_party/webrtc
  ${webrtc_SOURCEPATH}/webrtc
  ${webrtc_SOURCEPATH}/third_party/libsrtp/srtp
  ${webrtc_SOURCEPATH}/chromium/src/testing/gtest/include
  ${webrtc_SOURCEPATH}/chromium/src/third_party/jsoncpp/overrides/include
  ${webrtc_SOURCEPATH}/chromium/src/third_party/jsoncpp/source/include
  ${webrtc_SOURCEPATH}/chromium/src/third_party/expat/files/lib
  ${webrtc_SOURCEPATH}/testing/gtest/include
  ${webrtc_SOURCEPATH}/third_party/libyuv/include
  ${webrtc_SOURCEPATH}/testing/gtest
  ${webrtc_SOURCEPATH}/chromium/src/third_party/libsrtp/config
  ${webrtc_SOURCEPATH}/chromium/src/third_party/libsrtp/srtp/include
  ${webrtc_SOURCEPATH}/chromium/src/third_party/libsrtp/srtp/crypto/include)

set_target_properties(WebRtcConnector PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;CLD_VERSION=2;EXPAT_RELATIVE_PATH;FEATURE_ENABLE_VOICEMAIL;GTEST_RELATIVE_PATH;JSONCPP_RELATIVE_PATH;LOGGING=1;SRTP_RELATIVE_PATH;FEATURE_ENABLE_SSL;FEATURE_ENABLE_PSTN;HAVE_SCTP;HAVE_SRTP;HAVE_WEBRTC_VIDEO;HAVE_WEBRTC_VOICE;__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORE=0;CHROMIUM_BUILD;CR_CLANG_REVISION=247874-1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;DONT_EMBED_BUILD_METADATA;FIELDTRIAL_TESTING_ENABLED;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PDF=1;ENABLE_PLUGIN_INSTALLATION=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_THEMES=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;ENABLE_GOOGLE_NOW=1;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_SPELLCHECK=1;USE_BROWSER_SPELLCHECKER=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;OSX;WEBRTC_MAC;CARBON_DEPRECATED=YES;HASH_NAMESPACE=__gnu_cxx;WEBRTC_POSIX;DISABLE_DYNAMIC_CAST;_REENTRANT;GTEST_HAS_POSIX_RE=0;GTEST_LANG_CXX11=0;UNIT_TEST;GTEST_HAS_RTTI=0;XML_STATIC;USE_LIBPCI=1;USE_OPENSSL=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;")

set_target_properties(WebRtcConnector PROPERTIES COMPILE_FLAGS "-std=c++11 -stdlib=libc++ -fstack-protector --param=ssp-buffer-size=4 -Wheader-hygiene -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wstring-conversion -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -Wno-shift-negative-value -Wno-bitfield-width -Wno-unused-variable -Wno-undefined-bool-conversion -Wno-tautological-undefined-compare")

set_target_properties(WebRtcConnector PROPERTIES LINK_FLAGS "-Wl")

set(webrtc_build_debug ${webrtc_SOURCEPATH}/out/Debug)
target_link_libraries(WebRtcConnector
  ${webrtc_build_debug}/libgmock.a
  ${webrtc_build_debug}/librtc_base_tests_utils.a
  ${webrtc_build_debug}/libwebrtc_common.a
  ${webrtc_build_debug}/libjingle_p2p.a
  ${webrtc_build_debug}/libjingle_peerconnection.a
  ${webrtc_build_debug}/libjingle_unittest_main.a
  ${webrtc_build_debug}/libgtest.a
  ${webrtc_build_debug}/librtc_base.a
  ${webrtc_build_debug}/librtc_base_approved.a
  ${webrtc_build_debug}/libjsoncpp.a
  ${webrtc_build_debug}/libboringssl.a
  ${webrtc_build_debug}/libfield_trial.a
  ${webrtc_build_debug}/libsystem_wrappers.a
  ${webrtc_build_debug}/libexpat.a
  ${webrtc_build_debug}/libjingle_media.a
  ${webrtc_build_debug}/libvideo_render_module.a
  ${webrtc_build_debug}/libwebrtc_utility.a
  ${webrtc_build_debug}/libaudio_coding_module.a
  ${webrtc_build_debug}/libcng.a
  ${webrtc_build_debug}/libcommon_audio.a
  ${webrtc_build_debug}/libopenmax_dl.a
  ${webrtc_build_debug}/libcommon_audio_sse2.a
  ${webrtc_build_debug}/libaudio_encoder_interface.a
  ${webrtc_build_debug}/libg711.a
  ${webrtc_build_debug}/libpcm16b.a
  ${webrtc_build_debug}/libwebrtc_opus.a
  ${webrtc_build_debug}/libopus.a
  ${webrtc_build_debug}/libg722.a
  ${webrtc_build_debug}/libisac.a
  ${webrtc_build_debug}/libaudio_decoder_interface.a
  ${webrtc_build_debug}/libisac_common.a
  ${webrtc_build_debug}/libilbc.a
  ${webrtc_build_debug}/libred.a
  ${webrtc_build_debug}/librtc_event_log.a
  ${webrtc_build_debug}/librtc_event_log_proto.a
  ${webrtc_build_debug}/libprotobuf_lite.a
  ${webrtc_build_debug}/libneteq.a
  ${webrtc_build_debug}/librent_a_codec.a
  ${webrtc_build_debug}/libmedia_file.a
  ${webrtc_build_debug}/libcommon_video.a
  ${webrtc_build_debug}/libyuv.a
  ${webrtc_build_debug}/libjpeg_turbo.a
  ${webrtc_build_debug}/libwebrtc.a
  ${webrtc_build_debug}/libvoice_engine.a
  ${webrtc_build_debug}/libaudio_conference_mixer.a
  ${webrtc_build_debug}/libaudio_processing.a
  ${webrtc_build_debug}/libaudioproc_debug_proto.a
  ${webrtc_build_debug}/libaudio_processing_sse2.a
  ${webrtc_build_debug}/libaudio_device.a
  ${webrtc_build_debug}/libbitrate_controller.a
  ${webrtc_build_debug}/librtp_rtcp.a
  ${webrtc_build_debug}/libremote_bitrate_estimator.a
  ${webrtc_build_debug}/libpaced_sender.a
  ${webrtc_build_debug}/libvideo_capture_module.a
  ${webrtc_build_debug}/libvideo_processing.a
  ${webrtc_build_debug}/libvideo_processing_sse2.a
  ${webrtc_build_debug}/libwebrtc_video_coding.a
  ${webrtc_build_debug}/libwebrtc_h264.a
  ${webrtc_build_debug}/libwebrtc_i420.a
  ${webrtc_build_debug}/libvideo_coding_utility.a
  ${webrtc_build_debug}/libwebrtc_vp8.a
  ${webrtc_build_debug}/libvpx_new.a
  ${webrtc_build_debug}/libvpx_intrinsics_mmx.a
  ${webrtc_build_debug}/libvpx_intrinsics_sse2.a
  ${webrtc_build_debug}/libvpx_intrinsics_ssse3.a
  ${webrtc_build_debug}/libvpx_intrinsics_sse4_1.a
  ${webrtc_build_debug}/libvpx_intrinsics_avx2.a
  ${webrtc_build_debug}/libwebrtc_vp9.a
  ${webrtc_build_debug}/librtc_sound.a
  ${webrtc_build_debug}/libmetrics_default.a
  ${webrtc_build_debug}/librtc_xmllite.a
  ${webrtc_build_debug}/librtc_xmpp.a
  ${webrtc_build_debug}/librtc_p2p.a
  ${webrtc_build_debug}/libusrsctplib.a
  ${webrtc_build_debug}/libvideo_capture_module_internal_impl.a
  ${webrtc_build_debug}/libvideo_render_module_internal_impl.a
  ${webrtc_build_debug}/libsrtp.a

  /System/Library/Frameworks/Foundation.framework
  /System/Library/Frameworks/ApplicationServices.framework
  /System/Library/Frameworks/AudioToolbox.framework
  /System/Library/Frameworks/CoreAudio.framework
)
