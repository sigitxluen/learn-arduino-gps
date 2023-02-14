#pragma once

#include "Arduino.h"
#include "handler/GPSHandler.h"
#include "handler/LLHandler.h"
#include "handler/hoursCountHandler.h"
#include "handler/msg_handler.h"
#include "handler/sending_handler.h"
#include "handler/sleep_handler.h"
#include "handler/webServerHandler.h"
#include "peripheral/storage/localSpiffs.h"
#include "systems/deviceStatus/deviceStatus.h"

class start_task {
  private:
    localSpiffs _spiffs;
    GPSHandler _gps;
    hoursCountHandler _run_hours;
    msg_handler _msg_sending;
    LLHandler _ll;
    sleep_handler _sleep;


    deviceStatus _status;


    sending_handler _sending;
    webServerHandler _web_server;

  public:
    bool init_task ();
};