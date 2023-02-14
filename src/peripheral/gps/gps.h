#pragma once

#include "Arduino.h"
#include "config.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include <TinyGPSPlus.h>

class gps {
  private:
    TinyGPSPlus _gps;
    static const int RX_BUF_SIZE = 1024;


  public:
    gps (/* args */);

    void gps_init ();
    void gps_get_raw ();
};
