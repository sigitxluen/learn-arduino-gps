#include "sending_handler.h"

sending_handler::sending_handler () {}

void sending_handler::start () {
    xTaskCreatePinnedToCore (HandlerWrapper, "sending_handler", 6 * 1024, this, 3, NULL, 0);
}

bool sending_handler::initialize () { return 1; }

void sending_handler::entrypoint () {
    long previousMillis = 0;    // will store last time LED was updated
    long interval       = 1000; // interval at which to blink (milliseconds)
    while (1) {
        unsigned long currentMillis = millis ();

        if (currentMillis - previousMillis > interval) {
            // save the last time you blinked the LED
            previousMillis = currentMillis;
            // _fs.checkListDir
            // CUBE_LOG_SERIAL ("_msg.get_msg_json_tracker : %s",
            //                  _msg.get_msg_json_tracker ().c_str ());
        }
        // CUBE_LOG_SERIAL ("%s", _msg.get_msg_json_tracker ().c_str ());

        delay (1000);
    }
}