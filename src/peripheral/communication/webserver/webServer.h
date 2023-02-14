#pragma once

#include "ArduinoJson.h"
#include "SPIFFS.h"
// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include <WiFi.h>
// #include "peripheral/config_esp32.h"
#include  "peripheral/config_esp32.h"

#include "systems/deviceStatus/deviceStatus.h"
#include "peripheral/tools/tools.h"
#include"WiFi.h"

class webServer {
  public:
    webServer (/* args */);
    // Webserver (MessageBox& msgbox, Settings& settings, DeviceStatus& status, OTA& ota);
    bool startAccessPoint ();
    void init ();
    void registerHandler ();
    void processDNSRequest ();

  private:
    webServer* web;
    // Create AsyncWebServer object on port 80
    AsyncWebServer server{ 80 };
    AsyncEventSource events{ "/events" };
};