#pragma once

#include "Arduino.h"
#include "TinyGPS++.h"
#include "peripheral/gpio/LL_esp32.h"
#include "peripheral/storage/localSpiffs.h"
#include "peripheral/tools/tools.h"
#include "peripheral/uart/GPSUblox.h"
#include "systems/deviceStatus/deviceStatus.h"
#include "systems/messages/msg_type.h"
#include "taskHandler.h"


class sending_handler : taskHandler {
  private:
    // deviceStatus _status;
    LL_esp32 _gpio;
    GPSUblox _ublox;
    msg_type _msg;
    localSpiffs _fs;

  public:
    sending_handler (/* args */);
    void entrypoint ();
    bool initialize ();
    void start ();

    static void HandlerWrapper (void* _this) {
        static_cast<sending_handler*> (_this)->entrypoint ();
    }
};
