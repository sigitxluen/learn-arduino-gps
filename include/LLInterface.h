#pragma once

#include "stdint.h"

class LLInterface {
  public:
    virtual void set_buzzer_ON ()  = 0;
    virtual void set_buzzer_OFF () = 0;

    virtual bool get_sos () = 0;

    virtual uint16_t get_tamper_val () = 0;
    virtual bool get_acc_status ()     = 0;
    virtual bool get_engine_status ()  = 0;
    virtual bool get_standby_status () = 0;

    virtual bool initialize () = 0;
};