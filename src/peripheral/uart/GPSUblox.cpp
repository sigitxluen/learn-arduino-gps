#include "GPSUblox.h"

bool GPSUblox::initialize () {
    SerialGPS.begin (9600, SERIAL_8N1, RXD_PIN, TXD_PIN);
    return 1;
}
void GPSUblox::getAllData () {
    while (SerialGPS.available ()) {
        char c = SerialGPS.read ();
        // Serial.print (c);
        gps.encode (c);
    }

    if (gps.location.isValid () == true) {
        return;
    }

    if (gps.location.isUpdated ()) {
        firstlock = true;
    }

    if (millis () > 5000 && gps.charsProcessed () < 10)
        CUBE_LOG_SERIAL (("No GPS data received: check wiring"));

    delay (100);
}
void GPSUblox::waitDataDelay (unsigned long ms) {
    unsigned long start = millis ();
    do {
        while (SerialGPS.available ())
            gps.encode (SerialGPS.read ());
    } /*while (millis () - start < ms);
       */
    while (millis () - start < ms);
}

float GPSUblox::getLatitude () {
    waitDataDelay (0);
    return gps.location.lat ();
}

float GPSUblox::getLongitude () {
    waitDataDelay (0);
    return gps.location.lng ();
}

int GPSUblox::getSpeed () {
    waitDataDelay (0);
    return gps.speed.kmph ();
}

int GPSUblox::getHeading () {
    waitDataDelay (0);
    return gps.course.deg ();
}

int GPSUblox::getSatteliteValue () {
    waitDataDelay (0);
    return gps.satellites.value ();
}
uint32_t GPSUblox::getAltitude () {
    waitDataDelay (0);
    return gps.altitude.meters ();
}

uint32_t GPSUblox::getTimeStamp () {
    waitDataDelay (0);
    struct tm timeSync;

    timeSync.tm_year  = gps.date.year () - 1900; // since 1900 (2018 - 1900)
    timeSync.tm_mon   = gps.date.month () - 1;   // 0-based
    timeSync.tm_mday  = gps.date.day ();
    timeSync.tm_hour  = gps.time.hour ();
    timeSync.tm_min   = gps.time.minute ();
    timeSync.tm_sec   = gps.time.second ();
    timeSync.tm_isdst = -1;

    time_t t = mktime (&timeSync);
    struct timeval now;
    now.tv_sec = t;
    settimeofday (&now, NULL);
    // uint32_t timeis = (uint32_t)gps.time;
    return (uint32_t)t;
}

int GPSUblox::getGeoRadius () {
    static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
    auto _status = deviceStatus::GetInstance ();

    unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween (gps.location.lat (),
                                                 gps.location.lng (),
                                                 _status->get_point_latitude (),
                                                 _status->get_point_longitude ()) /
    1000;
    return distanceKmToLondon;
}

void GPSUblox::setTimeNow (uint32_t time) {
    if ((gps.time.isValid ())) {
        struct timeval nowa;
        nowa.tv_sec = time;
        settimeofday (&nowa, NULL);
        // CUBE_LOG_SERIAL ("set time %d", time);
    }
}
void sendUBX (uint8_t* MSG, uint8_t len) {
    for (int i = 0; i < len; i++) {
        SerialGPS.write (MSG[i]);
    }
    Serial.println ("write to gps");
}
void GPSUblox::set_gps_power () {
    // Set GPS ot Power Save Mode
    uint8_t setPSM[] = { 0xB5, 0x62, 0x06, 0x11, 0x02,
                         0x00, 0x08, 0x01, 0x22, 0x92 }; // Setup for Power Save Mode (Default Cyclic 1s)

    sendUBX (setPSM, sizeof (setPSM) / sizeof (uint8_t));
}

void GPSUblox::set_wake_up_gps () {
    set_gps_power ();
    // Restart GPS
    uint8_t GPSon[] = { 0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4C, 0x37 };
    sendUBX (GPSon, sizeof (GPSon) / sizeof (uint8_t));
    Serial.println ("GPS_ON");
}

void GPSUblox::set_sleep_gps () {
    set_gps_power ();
    uint8_t GPSoff[] = { 0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x4D, 0x3B };
    sendUBX (GPSoff, sizeof (GPSoff) / sizeof (uint8_t));
    Serial.println ("GPS_OFF");
}