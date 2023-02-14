#pragma once

#include "Arduino.h"
#include "callback_cmd.h"
#include "systems/deviceStatus/deviceStatus.h"
#include "peripheral/gpio/LL_esp32.h"
#include "stdint.h"
#include "string"

class sim900a {
  private:
    deviceStatus _status;
    callback_cmd _cmd;
    LL_esp32 _gpio;


    // Your GPRS credentials, if any
    std::string apn      = "internet";
    std::string gprsUser = "";
    std::string gprsPass = "";
    // MQTT details
    // const char* broker = "52.69.255.27";

    // const char* topicLed       = "zotak/GsmClientTest/led";
    // const char* topicInit      = "zotak/GsmClientTest/init";
    // const char* topicLedStatus = "zotak/GsmClientTest/ledStatus";

  public:
    sim900a (/* args */);
    void start_gsm ();
    void initialize ();
    void check_network ();
    void publish_data (const char* topic, const char* payload);
    void check_mqtt ();

    void sim_sleep ();
    void sim_wake_up ();

};
