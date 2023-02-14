#pragma once

#include "Arduino.h"
#include "LLInterface.h"
#include "driver/gpio.h"
#include "esp_adc_cal.h"
#include  "peripheral/config_esp32.h"


class LL_esp32 : public LLInterface {
  private:
    uint8_t s_led_state = 0;
    bool sos;
    bool tamper;

    unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
    unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers
    unsigned long debounceDelaySOS = 3000; // the debounce time; increase if the output flickers

    int ledState = LOW;         // current state of the output pin
    int buttonState;            // current reading from the input pin
    int lastButtonState = HIGH; // previous reading from the input pin

  public:
    bool initialize ();
    void set_buzzer_ON ();
    void set_buzzer_OFF ();
    void set_DTR_OFF ();
    void set_RST_OFF ();
    void set_DTR_ON ();
    void set_RST_ON ();
    uint16_t get_battery_val ();
    uint8_t get_battery_percent ();
    bool get_sos ();
    uint16_t get_tamper_val ();
    bool get_acc_status ();
    bool get_engine_status ();
    bool get_standby_status ();
};
