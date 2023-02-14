#include "LLHandler.h"

LLHandler::LLHandler () {}

void LLHandler::start () {
    xTaskCreatePinnedToCore (HandlerWrapper, "LL", 6 * 1024, this, 3, NULL, 0);
}

bool LLHandler::initialize () { return 1; }

void LLHandler::entrypoint () {

    _gpio.initialize ();
    auto _status = deviceStatus::GetInstance ();

    while (1) {
        _status->set_pwr_acc (_gpio.get_acc_status ());
        _status->set_pwr_engine (_gpio.get_engine_status ());
        _status->set_pwr_standby (_gpio.get_standby_status ());
        _status->set_val_tamper (_gpio.get_tamper_val ());
        _status->set_percent_battery (_gpio.get_battery_percent ());
        _status->set_val_battery (_gpio.get_battery_val ());

        if (_gpio.get_tamper_val () > LDR_TRHD || _gpio.get_sos () ||
            _ublox.getGeoRadius () > GEO_FEN) {
            // _gpio.set_buzzer_ON ();
            _status->set_status_tamper (true);
        } else if (_gpio.get_tamper_val () <= LDR_TRHD && !_gpio.get_sos () &&
                   _ublox.getGeoRadius () <= GEO_FEN) {
            _gpio.set_buzzer_OFF ();
            _status->set_status_tamper (false);
        }

        // CUBE_LOG_SERIAL ("%d", _gpio.get_tamper_val ());
        vTaskDelay (300 / portTICK_PERIOD_MS);
    }
}