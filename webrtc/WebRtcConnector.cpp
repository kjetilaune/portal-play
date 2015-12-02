#include "WebRtcEngine.h"

#include <stdio.h>
#include <iostream>


// Blocks until key is pressed
void block() {
  while(std::cin.get() != '\n') {
  }
}

//-------------------------------------------------------------------------
int main(void) {
  
  rtcapp::WebRtcEngine engine;
  
  engine.Initialize();
  block();

  engine.CreateVideoCapturer();
  block();

  engine.AddStreams();
  block();  

  return 0;
}
