#pragma once

#include "Arduino.h"
#include "TinyGPS++.h"
#include "peripheral/gpio/LL_esp32.h"
#include "peripheral/communication/gsm/sim900a_mqtt.h"
#include "peripheral/tools/tools.h"
#include "peripheral/uart/GPSUblox.h"
#include "systems/deviceStatus/deviceStatus.h"
#include "taskHandler.h"


class sleep_handler : taskHandler {
  private:
    GPSUblox ublox;
    LL_esp32 _gpio;
    sim900a _sim;

    bool gps_sleep   = false;
    bool gps_wake_up = false;

    bool sim_sleep   = false;
    bool sim_wake_up = false;
#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex


  public:
    sleep_handler (/* args */);
    void entrypoint ();
    bool initialize ();
    void start ();

    static void HandlerWrapper (void* _this) {
        static_cast<sleep_handler*> (_this)->entrypoint ();
    }
};
