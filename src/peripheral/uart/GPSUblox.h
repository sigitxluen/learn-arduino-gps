#pragma once

#include "Arduino.h"
#include "GPSInterface.h"
#include "HardwareSerial.h"
#include "TinyGPS++.h"
#include "peripheral/config_esp32.h"
#include "peripheral/tools/tools.h"
#include "systems/deviceStatus/deviceStatus.h"
#include <sys/time.h>
#include <time.h>


class GPSUblox : public GPSInterface {
  private:
#define SerialGPS Serial1

    TinyGPSPlus gps;
    // static struct timeval tv;
    // static struct tm timeSync;

    // deviceStatus _status;
    bool firstlock = false;

  public:
    bool initialize ();
    float getLongitude ();
    float getLatitude ();
    int getSpeed ();
    int getHeading ();
    int getGeoRadius ();
    int getSatteliteValue ();
    uint32_t getAltitude ();

    uint32_t getTimeStamp ();
    void getAllData ();
    void waitDataDelay (unsigned long ms);
    void setTimeNow (uint32_t time);

    void set_gps_power();
    void set_wake_up_gps();
    void set_sleep_gps();
};