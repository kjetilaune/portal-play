#include "Util.h"

#include <stdio.h>
#include <iostream>


//-------------------------------------------------------------------------
void Error(std::string errorStr) {

  std::cout << "----- Error: " << errorStr << " -----" << std::endl;
}

//-------------------------------------------------------------------------
void Info(std::string infoStr) {

  std::cout << "----- Info: " << infoStr << " -----" << std::endl;
}

//-------------------------------------------------------------------------
void BlockUntilKeypress() {
  while(std::cin.get() != '\n') {
  }
}
