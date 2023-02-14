#pragma once

#include "Arduino.h"
#include "peripheral/config_esp32.h"
#include "peripheral/gpio/LL_esp32.h"
#include "peripheral/tools/tools.h"
#include "peripheral/uart/GPSUblox.h"
#include "systems/deviceStatus/deviceStatus.h"

#include "taskHandler.h"


class LLHandler : public taskHandler {
  private:
    LL_esp32 _gpio;
    deviceStatus _status;
    GPSUblox _ublox;

  public:
    LLHandler ();
    void entrypoint ();
    bool initialize ();
    void start ();

    static void HandlerWrapper (void* _this) {
        static_cast<LLHandler*> (_this)->entrypoint ();
    }
};
