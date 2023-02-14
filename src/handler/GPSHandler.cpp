#include "GPSHandler.h"

GPSHandler::GPSHandler () {}

void GPSHandler::start () {
    xTaskCreatePinnedToCore (HandlerWrapper, "GPSHandler", 6 * 1024, this, 3, NULL, 0);
}

bool GPSHandler::initialize () { return 1; }

void GPSHandler::entrypoint () {
    ublox.initialize ();
    auto _status = deviceStatus::GetInstance ();

    long previousMillis = 0; // will store last time LED was updated

    // the follow variables is a long because the time, measured in miliseconds,
    // will quickly become a bigger number than can be stored in an int.
    long interval = 15000; // interval at which to blink (milliseconds)
    struct timeval tv;
    struct tm timeSync;
    while (1) {
        ublox.waitDataDelay (1000);

        _status->set_latitude (ublox.getLatitude ());
        _status->set_longitude (ublox.getLongitude ());
        _status->set_course (ublox.getHeading ());
        _status->set_speed (ublox.getSpeed ());
        _status->set_radius (ublox.getGeoRadius ());
        _status->set_altitude (ublox.getAltitude ());
        _status->set_sat_value (ublox.getSatteliteValue ());

        unsigned long currentMillis = millis ();

        if (currentMillis - previousMillis > interval) {
            // save the last time you blinked the LED
            previousMillis = currentMillis;
            ublox.setTimeNow (ublox.getTimeStamp ());

            // CUBE_LOG_SERIAL ("get time %d", ublox.getTimeStamp ());
        }

// #if defined(SLEEP_GPS_ENABLE)

//         if (!_gpio.get_standby_status ()) {
//             if (!sleep) {
//                 ublox.set_sleep_gps ();
//                 sleep   = true;
//                 wake_up = false;
//             }

//         } else {
//             if (!wake_up) {
//                 ublox.set_wake_up_gps ();
//                 wake_up = true;
//                 sleep   = false;
//             }
//         }

// #endif // SLEEP_GPS_ENABLE


        // check GPIO status only
        // Serial.println (_gpio.get_standby_status ());
        // Serial.println (_gpio.get_acc_status ());
        // Serial.println (_gpio.get_engine_status ());

        delay (100);
    }
}