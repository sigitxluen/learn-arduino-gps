#pragma once

#include "stdint.h"
#include "string"
#include "Arduino.h"
#include "peripheral/tools/tools.h"

class callback_cmd {
  private:
    std::string tpc_set_geo;
  public:
    static void mqttCallback (char* topic, byte* payload, unsigned int len);
};
