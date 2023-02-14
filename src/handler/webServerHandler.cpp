#include "webServerHandler.h"

webServerHandler::webServerHandler () {}

void webServerHandler::start () {
    xTaskCreatePinnedToCore (handlerWrapper, "webServerHandler", 15 * 1024,
                             this, 3, NULL, 1);
}

bool webServerHandler::initialize () { return 1; }

void webServerHandler::entrypoint () {
    wifiStart.start_AP ();
    // if (WiFi.waitForConnectResult () != WL_CONNECTED) {
    //     Serial.printf ("WiFi Failed!\n");
    //     return;
    // }
    webSer.registerHandler ();
    uint32_t lastConnectedStation = millis ();

    while (1) {
        // webSer.processDNSRequest ();

        int numberOfClients = WiFi.softAPgetStationNum ();
        if (numberOfClients > 0) {
            lastConnectedStation = millis ();
        }
        if (millis () - lastConnectedStation > 120000UL) {
            WiFi.mode (WIFI_OFF);
        }
        delay (1000);
        // CUBE_LOG_ALL ("New outbox found: %d", 1);
    }
}