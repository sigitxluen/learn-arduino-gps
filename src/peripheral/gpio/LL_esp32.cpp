#include "LL_esp32.h"

bool LL_esp32::initialize () {
    pinMode (TAMPER_PIN, INPUT);
    pinMode (STANDBY_PIN, INPUT_PULLUP);
    pinMode (ACC_PIN, INPUT_PULLUP);
    pinMode (ENGINE_PIN, INPUT_PULLUP);
    pinMode (BATTERY_PIN, INPUT);
    pinMode (SOS_PIN, INPUT_PULLUP);

    pinMode (BUZZER_PIN, OUTPUT);
    digitalWrite (BUZZER_PIN, LOW);

    pinMode (SIM_DTR, OUTPUT);
    digitalWrite (SIM_DTR, LOW);
    pinMode (SIM_RST, OUTPUT);
    digitalWrite (SIM_RST, LOW);

    return 1;
}

uint16_t LL_esp32::get_tamper_val () { return (analogRead (TAMPER_PIN)); }
uint16_t LL_esp32::get_battery_val () {
    uint16_t batteryADC  = analogRead (BATTERY_PIN);
    float batteryVoltage = ((batteryADC * 3300) / 65535) * 2;
    return (uint16_t)batteryVoltage;
}
uint8_t LL_esp32::get_battery_percent () {
    // We use voltage divider so naturally we need to multiply the
    // battery voltage by 2.
    uint16_t batteryADC  = analogRead (BATTERY_PIN);
    float batteryVoltage = ((batteryADC * 3300) / 65535) * 2;

    // A complex calculation to convert mV to %
    uint8_t batteryPercentage = (batteryVoltage - 3000) * 100 / 1200;

    return batteryPercentage;
}

bool LL_esp32::get_sos () { return digitalRead (SOS_PIN); }

void LL_esp32::set_buzzer_OFF () { digitalWrite (BUZZER_PIN, LOW); }
void LL_esp32::set_buzzer_ON () { digitalWrite (BUZZER_PIN, HIGH); }

void LL_esp32::set_DTR_OFF () { digitalWrite (SIM_DTR, LOW); }
void LL_esp32::set_DTR_ON () { digitalWrite (SIM_DTR, HIGH); }

void LL_esp32::set_RST_OFF () { digitalWrite (SIM_RST, LOW); }
void LL_esp32::set_RST_ON () { digitalWrite (SIM_RST, HIGH); }

bool LL_esp32::get_acc_status () { return !digitalRead (ACC_PIN); }
bool LL_esp32::get_engine_status () { return !digitalRead (ENGINE_PIN); }
bool LL_esp32::get_standby_status () { return !digitalRead (STANDBY_PIN); }
