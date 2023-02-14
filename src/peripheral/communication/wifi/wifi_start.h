#pragma once
// #include "systems/deviceStatus/deviceStatus.h"
#include "systems/deviceStatus/deviceStatus.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

class wifi_start {
  private:
    // deviceStatus _status;

    String hostname = "cube-link";

  public:
    wifi_start (/* args */);

    void start_AP ();
    void start_STA ();
    void check_AP_connection ();

};
