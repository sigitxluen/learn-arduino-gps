#pragma once


#include "peripheral/communication/webserver/webServer.h"
#include "peripheral/communication/wifi/wifi_start.h"
#include "peripheral/tools/tools.h"
#include "stdint.h"
#include "taskHandler.h"
#include <Arduino.h>
#include <WiFi.h>


class webServerHandler : public taskHandler {
  private:
    const char* ssid     = "cantik";    // Your WiFi SSID
    const char* password = "12345678";  // Your WiFi Password
    const char* hostname = "netracube"; // Your WiFi Password

    webServer webSer;
    wifi_start wifiStart;

  public:
    webServerHandler ();
    void entrypoint ();
    void start ();
    bool initialize ();
    static void handlerWrapper (void* _this) {
        static_cast<webServerHandler*> (_this)->entrypoint ();
    }
};