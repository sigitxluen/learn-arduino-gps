#include "msg_handler.h"

msg_handler::msg_handler () {}

void msg_handler::start () {
    xTaskCreatePinnedToCore (HandlerWrapper, "msg_handler", 6 * 1024, this, 25, NULL, 1);
}

bool msg_handler::initialize () { return 1; }

void msg_handler::entrypoint () {
    auto _status = deviceStatus::GetInstance ();

    _sim.initialize ();
    long previousMillis = 0;     // will store last time LED was updated
    long interval       = 60000; // interval at which to blink (milliseconds)

    while (1) {
        _sim.check_mqtt ();
        _sim.check_network ();

        unsigned long currentMillis = millis ();

        if (currentMillis - previousMillis > SENDING_INTERVAL) {
            // save the last time you blinked the LED
            previousMillis = currentMillis;

            if (_gpio.get_standby_status ()) {
                _sim.publish_data ("tracker_data", _msg.get_msg_json_tracker ().c_str ());
                // CUBE_LOG_SERIAL ("_msg.get_msg_json_tracker : %s",
                //                  _msg.get_msg_json_tracker ().c_str ());
            }
        }

        delay (100);
    }
}