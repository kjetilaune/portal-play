#ifndef ISENDERCALLBACK_H_
#define ISENDERCALLBACK_H_

#include <string>


/*
 * A Callback interface for the NetworkSender Class
 */
class ISenderCallback {
public:
  virtual void OnSentCompleted(bool sendResult) = 0;
};

#endif //ISENDERCALLBACK_H_
