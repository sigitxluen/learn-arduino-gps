#pragma once

#include "Arduino.h"
#include "TinyGPS++.h"
#include "systems/deviceStatus/deviceStatus.h"
#include "peripheral/communication/gsm/sim900a_mqtt.h"
#include "peripheral/gpio/LL_esp32.h"
#include "peripheral/uart/GPSUblox.h"
#include "peripheral/tools/tools.h"
#include "systems/messages/msg_type.h"
#include "taskHandler.h"
#include "peripheral/storage/localSpiffs.h"

class msg_handler : taskHandler {
  private:
    LL_esp32 _gpio;
    GPSUblox _ublox;
    msg_type _msg;
    sim900a _sim;
    localSpiffs _fs;

  public:
    msg_handler (/* args */);
    void entrypoint ();
    bool initialize ();
    void start ();

    static void HandlerWrapper (void* _this) {
        static_cast<msg_handler*> (_this)->entrypoint ();
    }
};
