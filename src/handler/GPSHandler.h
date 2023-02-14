#pragma once

#include "Arduino.h"
#include "TinyGPS++.h"
#include "peripheral/tools/tools.h"
#include "peripheral/uart/GPSUblox.h"
#include "systems/deviceStatus/deviceStatus.h"
#include "peripheral/gpio/LL_esp32.h"
#include "taskHandler.h"


class GPSHandler : taskHandler {
  private:
    GPSUblox ublox;
    LL_esp32 _gpio;

    bool sleep = false;
    bool wake_up = false;

  public:
    GPSHandler (/* args */);
    void entrypoint ();
    bool initialize ();
    void start ();

    static void HandlerWrapper (void* _this) {
        static_cast<GPSHandler*> (_this)->entrypoint ();
    }
};
