/**
 * @file deviceStatus.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "deviceStatus.h"
deviceStatus* deviceStatus::instance = NULL;
deviceStatus* deviceStatus::GetInstance () {
    if (!instance) {
        instance = new deviceStatus ();
        return instance;
    } else {
        return instance;
    }
}
deviceStatus::deviceStatus (/* args */) {}
//-----------get device data--------------

uint8_t deviceStatus::get_p_wifi () { return _p_wifi; }
void deviceStatus::set_p_wifi (uint8_t p_wifi) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _p_wifi = p_wifi;
}

uint8_t deviceStatus::get_p_gsm () { return _p_gsm; }
void deviceStatus::set_p_gsm (uint8_t p_gsm) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _p_gsm = p_gsm;
}

uint8_t deviceStatus::get_p_gps () { return _p_gps; }
void deviceStatus::set_p_gps (uint8_t p_gps) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _p_gps = p_gps;
}

uint8_t deviceStatus::get_p_s_env () { return _p_s_env; }
void deviceStatus::set_p_s_env (uint8_t p_s_env) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _p_s_env = p_s_env;
}

uint8_t deviceStatus::get_p_s_gyro () { return _p_s_gyro; }
void deviceStatus::set_p_s_gyro (uint8_t p_s_gyro) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _p_s_gyro = p_s_gyro;
}

uint8_t deviceStatus::get_p_s_vibra () { return _p_s_vibra; }
void deviceStatus::set_p_s_vibra (uint8_t p_s_vibra) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _p_s_vibra = p_s_vibra;
}

uint8_t deviceStatus::get_p_s_ldr () { return _p_s_ldr; }
void deviceStatus::set_p_s_ldr (uint8_t p_s_ldr) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _p_s_ldr = p_s_ldr;
}

uint8_t deviceStatus::get_p_s_batt_devider () { return _p_s_batt_devider; }
void deviceStatus::set_p_s_batt_devider (uint8_t p_s_batt_devider) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _p_s_batt_devider = p_s_batt_devider;
}

uint8_t deviceStatus::get_p_o_buzzer () { return _p_o_buzzer; }
void deviceStatus::set_p_o_buzzer (uint8_t p_o_buzzer) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _p_o_buzzer = p_o_buzzer;
}
//---------------------------------------------------------
uint32_t deviceStatus::get_i_msg_tracker () { return _i_msg_tracker; }
void deviceStatus::set_i_msg_tracker (uint32_t i_msg_tracker) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _i_msg_tracker = i_msg_tracker;
}
uint32_t deviceStatus::get_i_msg_alert () { return _i_msg_alert; }
void deviceStatus::set_i_msg_alert (uint32_t i_msg_alert) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _i_msg_alert = i_msg_alert;
}
uint32_t deviceStatus::get_i_msg_sos () { return _i_msg_sos; }
void deviceStatus::set_i_msg_sos (uint32_t i_msg_sos) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _i_msg_sos = i_msg_sos;
}

//---------------------------------------------------------
std::string deviceStatus::get_serial_number () { return _serial_number; }
void deviceStatus::set_serial_number (std::string serial_number) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _serial_number = serial_number;
}
std::string deviceStatus::get_heavy_type () { return _heavy_type; }
void deviceStatus::set_heavy_type (std::string heavy_type) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _heavy_type = heavy_type;
}
uint32_t deviceStatus::get_device_type () { return _device_type; }
void deviceStatus::set_device_type (uint32_t device_type) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _device_type = device_type;
}
uint32_t deviceStatus::get_production_date () { return _production_date; }
void deviceStatus::set_production_date (uint32_t production_date) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _production_date = production_date;
}
uint32_t deviceStatus::get_runTime () { return _runTime; }
void deviceStatus::set_runTime (uint32_t runTime) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _runTime = runTime;
}
uint32_t deviceStatus::get_last_usage () { return _last_usage; }
void deviceStatus::set_last_usage (uint32_t last_usage) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _last_usage = last_usage;
}
//---------------------------------------------------------

std::string deviceStatus::get_imei () { return _imei; }
void deviceStatus::set_imei (std::string imei) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _imei = imei;
}

std::string deviceStatus::get_wifi_ap_ssid () { return _wifi_AP_ssid; }
void deviceStatus::set_wifi_ap_ssid (std::string wifi_AP_ssid) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _wifi_AP_ssid = wifi_AP_ssid;
}

std::string deviceStatus::get_wifi_ap_pswd () { return _wifi_AP_pswd; }
void deviceStatus::set_wifi_ap_pswd (std::string wifi_AP_pswd) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _wifi_AP_pswd = wifi_AP_pswd;
}

std::string deviceStatus::get_wifi_sta_ssid () { return _wifi_STA_ssid; }
void deviceStatus::set_wifi_sta_ssid (std::string wifi_STA_ssid) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _wifi_STA_ssid = wifi_STA_ssid;
}

std::string deviceStatus::get_wifi_sta_pswd () { return _wifi_STA_pswd; }
void deviceStatus::set_wifi_sta_pswd (std::string wifi_STA_pswd) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _wifi_STA_pswd = wifi_STA_pswd;
}

uint16_t deviceStatus::get_val_battery () { return _val_battery; }
void deviceStatus::set_val_battery (uint16_t val_battery) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _val_battery = val_battery;
}
uint8_t deviceStatus::get_percent_battery () { return _percent_battery; }
void deviceStatus::set_percent_battery (uint8_t percent_battery) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _percent_battery = percent_battery;
}


uint16_t deviceStatus::get_val_tamper () { return _val_tamper; }
void deviceStatus::set_val_tamper (uint16_t val_tamper) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _val_tamper = val_tamper;
}

bool deviceStatus::get_status_tamper () { return _status_tamper; }
void deviceStatus::set_status_tamper (bool status_tamper) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _status_tamper = status_tamper;
}

// power data
bool deviceStatus::get_pwr_standby () { return _pwr_standby; }
void deviceStatus::set_pwr_standby (bool pwr_standby) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _pwr_standby = pwr_standby;
}

bool deviceStatus::get_pwr_acc () { return _pwr_acc; }
void deviceStatus::set_pwr_acc (bool pwr_acc) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _pwr_acc = pwr_acc;
}

bool deviceStatus::get_pwr_engine () { return _pwr_engine; }
void deviceStatus::set_pwr_engine (bool pwr_engine) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _pwr_engine = pwr_engine;
}

// uint32_t deviceStatus::get_time_now () { return _time_now; }
// void deviceStatus::set_time_now (uint32_t time_now) {
//     std::lock_guard<std::mutex> locker (_config_vals_mtx);
//     _time_now = time_now;
// }

uint32_t deviceStatus::get_running_time () { return _running_time; }
void deviceStatus::set_running_time (uint32_t running_time) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _running_time = running_time;
}

uint32_t deviceStatus::get_interval_sending () { return _interval_sending; }
void deviceStatus::set_interval_sending (uint32_t interval_sending) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _interval_sending = interval_sending;
}

// gps data
double deviceStatus::get_latitude () { return _latitude; }
void deviceStatus::set_latitude (double latitude) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _latitude = latitude;
}

double deviceStatus::get_longitude () { return _longitude; }
void deviceStatus::set_longitude (double longitude) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _longitude = longitude;
}

double deviceStatus::get_point_latitude () { return _point_latitude; }
void deviceStatus::set_point_latitude (double point_latitude) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _point_latitude = point_latitude;
}

double deviceStatus::get_point_longitude () { return _longitude; }
void deviceStatus::set_point_longitude (double longitude) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _longitude = longitude;
}

double deviceStatus::get_speed () { return _speed; }
void deviceStatus::set_speed (double speed) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _speed = speed;
}

double deviceStatus::get_course () { return _course; }
void deviceStatus::set_course (double course) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _course = course;
}

uint32_t deviceStatus::get_radius () { return _radius; }
void deviceStatus::set_radius (uint32_t radius) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _radius = radius;
}

uint32_t deviceStatus::get_altitude () { return _altitude; }
void deviceStatus::set_altitude (uint32_t altitude) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _altitude = altitude;
}

uint32_t deviceStatus::get_sat_value () { return _sat_value; }
void deviceStatus::set_sat_value (uint32_t sat_value) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _sat_value = sat_value;
}
// env data
float deviceStatus::get_temperature () { return _temperature; }
void deviceStatus::set_temperature (float temperature) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _temperature = temperature;
}

float deviceStatus::get_humidity () { return _humidity; }
void deviceStatus::set_humidity (float humidity) {
    std::lock_guard<std::mutex> locker (_config_vals_mtx);
    _humidity = humidity;
}