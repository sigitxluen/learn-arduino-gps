#include "sleep_handler.h"
RTC_DATA_ATTR int bootCount = 0;

sleep_handler::sleep_handler () {}

void sleep_handler::start () {
    xTaskCreatePinnedToCore (HandlerWrapper, "sleep_handler", 6 * 1024, this, 3, NULL, 0);
}

bool sleep_handler::initialize () { return 1; }


void print_wakeup_reason () {
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause ();

    switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println ("Wakeup caused by external signal using RTC_IO");
        break;
    case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println ("Wakeup caused by external signal using RTC_CNTL");
        break;
    case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println ("Wakeup caused by timer");
        break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        Serial.println ("Wakeup caused by touchpad");
        break;
    case ESP_SLEEP_WAKEUP_ULP:
        Serial.println ("Wakeup caused by ULP program");
        break;
    default:
        Serial.printf ("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
        break;
    }
}

void sleep_handler::entrypoint () {
    while (1) {
#if defined(SLEEP_GPS_ENABLE)

        if (!_gpio.get_standby_status ()) {
            if (!gps_sleep) {
                ublox.set_sleep_gps ();
                gps_sleep   = true;
                gps_wake_up = false;
            }

        } else {
            if (!gps_wake_up) {
                ublox.set_wake_up_gps ();
                gps_wake_up = true;
                gps_sleep   = false;
            }
        }

#endif // SLEEP_GPS_ENABLE


#if defined(SLEEP_ESP32_ENABLE)


        if (!_gpio.get_standby_status ()) {
            // Serial.println ("heart_beat");
            // Increment boot number and print it every reboot
            ++bootCount;
            Serial.println ("Boot number: " + String (bootCount));

            // Print the wakeup reason for ESP32
            print_wakeup_reason ();

            /*
            First we configure the wake up source
            We set our ESP32 to wake up for an external trigger.
            There are two types for ESP32, ext0 and ext1 .
            ext0 uses RTC_IO to wakeup thus requires RTC peripherals
            to be on while ext1 uses RTC Controller so doesnt need
            peripherals to be powered on.
            Note that using internal pullups/pulldowns also requires
            RTC peripherals to be turned on.
            */
            esp_sleep_enable_ext0_wakeup (GPIO_NUM_39, 0); // 1 = High, 0 = Low

            // If you were to use ext1, you would use it like
            // esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

            // Go to sleep now
            Serial.println ("Going to sleep now");
            delay (10000);

#if defined(SLEEP_SIM_ENABLE)

            if (!_gpio.get_standby_status ()) {
                if (!sim_sleep) {
                    _sim.sim_sleep ();
                    sim_sleep   = true;
                    sim_wake_up = false;
                }

            } else {
                if (!sim_wake_up) {
                    _sim.sim_wake_up ();
                    sim_wake_up = true;
                    sim_sleep   = false;
                }
            }

#endif // SLEEP_SIM_ENABLE
            Serial.flush ();
            if (!_gpio.get_standby_status ()) {
                // esp_deep_sleep_start ();
                esp_light_sleep_start ();
            }

            Serial.println ("This will never be printed");
        }

#endif // SLEEP_ESP32_ENABLE


        // check GPIO status only
        // Serial.println (_gpio.get_standby_status ());
        // Serial.println (_gpio.get_acc_status ());
        // Serial.println (_gpio.get_engine_status ());

        delay (1000);
    }
}