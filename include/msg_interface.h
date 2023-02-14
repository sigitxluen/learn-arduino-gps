#pragma once

#include "stdint.h"
#include "string"

class msg_interface {
  public:
    virtual std::string get_msg_sos ()     = 0;
    virtual std::string get_msg_tracker () = 0;
    virtual std::string get_msg_alert ()   = 0;
};
