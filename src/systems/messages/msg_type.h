#pragma once

#include "ArduinoJson.h"
#include "WiFi.h"
#include "systems/deviceStatus/deviceStatus.h"
#include "peripheral/tools/tools.h"
#include "msg_interface.h"
#include "mutex"
#include "string"
#include <stdint.h>

class msg_type : public msg_interface {
  private:
    std::mutex _gen_json_mtx;
    std::string _msg_sos;
    std::string _msg_tracker;
    std::string _msg_alert;
    std::string _msg_json_sos;
    std::string _msg_json_tracker;
    std::string _msg_json_alert;

  public:
    std::string get_msg_sos ();
    std::string get_msg_tracker ();
    std::string get_msg_alert ();
    std::string get_msg_json_sos ();
    std::string get_msg_json_tracker ();
    std::string get_msg_json_alert ();
};
