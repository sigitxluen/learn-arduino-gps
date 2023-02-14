#pragma once

#include "Arduino.h"
#include "TinyGPS++.h"
#include "peripheral/gpio/LL_esp32.h"
#include "peripheral/storage/localSpiffs.h"
#include "peripheral/uart/GPSUblox.h"
#include "systems/deviceStatus/deviceStatus.h"
#include "peripheral/tools/tools.h"
#include "taskHandler.h"
#include "time.h"
#include <ArduinoJson.h>

class hoursCountHandler : taskHandler {
  private:
    localSpiffs fs;
    LL_esp32 gpio;

  public:
    hoursCountHandler (/* args */);
    void entrypoint ();
    bool initialize ();
    void start ();

    static void HandlerWrapper (void* _this) {
        static_cast<hoursCountHandler*> (_this)->entrypoint ();
    }
};
