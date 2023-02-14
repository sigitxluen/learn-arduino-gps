#pragma once

#if defined(ESP32)

#define TAMPER_PIN (gpio_num_t)36
#define STANDBY_PIN (gpio_num_t)39
#define ACC_PIN (gpio_num_t)34
#define ENGINE_PIN (gpio_num_t)35
#define BATTERY_PIN (gpio_num_t)33
#define NC1_PIN (gpio_num_t)33
#define NC2_PIN (gpio_num_t)25
#define SOS_PIN (gpio_num_t)26
#define BUZZER_PIN (gpio_num_t)27
#define SIM_DTR (gpio_num_t)23
#define I2C_SCL (gpio_num_t)22
#define I2C_SDA (gpio_num_t)21

#define TXD_PIN (GPIO_NUM_19) // GPS
#define RXD_PIN (GPIO_NUM_18) // GPS

#define SIM_RST (gpio_num_t)4

// urgent data

#define LDR_TRHD 500
#define GEO_FEN 50

#define SLEEP_GPS_ENABLE
// #define SLEEP_SIM_ENABLE
#define SLEEP_ESP32_ENABLE


#endif // ESP32
