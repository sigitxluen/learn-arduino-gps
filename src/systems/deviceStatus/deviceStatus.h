/**
 * @file deviceStatus.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "mutex"
#include "stdint.h"
#include "string"

class deviceStatus {
  public:
    // deviceStatus (/* args */);
    deviceStatus ();

    static deviceStatus* GetInstance ();

    uint8_t get_p_wifi ();
    void set_p_wifi (uint8_t p_wifi);
    uint8_t get_p_gsm ();
    void set_p_gsm (uint8_t p_gsm);
    uint8_t get_p_gps ();
    void set_p_gps (uint8_t p_gps);
    uint8_t get_p_s_env ();
    void set_p_s_env (uint8_t p_s_env);
    uint8_t get_p_s_gyro ();
    void set_p_s_gyro (uint8_t p_s_gyro);
    uint8_t get_p_s_vibra ();
    void set_p_s_vibra (uint8_t p_s_vibra);
    uint8_t get_p_s_ldr ();
    void set_p_s_ldr (uint8_t p_s_ldr);
    uint8_t get_p_s_batt_devider ();
    void set_p_s_batt_devider (uint8_t p_s_batt_devider);
    uint8_t get_p_o_buzzer ();
    void set_p_o_buzzer (uint8_t p_o_buzzer);

    std::string get_serial_number ();
    void set_serial_number (std::string serial_number);
    std::string get_heavy_type ();
    void set_heavy_type (std::string heavy_type);
    uint32_t get_device_type ();
    void set_device_type (uint32_t device_type);
    uint32_t get_production_date ();
    void set_production_date (uint32_t production_date);
    uint32_t get_runTime ();
    void set_runTime (uint32_t runTime);
    uint32_t get_last_usage ();
    void set_last_usage (uint32_t last_usage);
    // esp data
    std::string get_imei ();
    void set_imei (std::string imei);

    std::string get_wifi_ap_ssid ();
    void set_wifi_ap_ssid (std::string wifi_AP_ssid);

    std::string get_wifi_ap_pswd ();
    void set_wifi_ap_pswd (std::string wifi_AP_pswd);

    std::string get_wifi_sta_ssid ();
    void set_wifi_sta_ssid (std::string wifi_STA_ssid);

    std::string get_wifi_sta_pswd ();
    void set_wifi_sta_pswd (std::string wifi_STA_pswd);

    uint8_t get_percent_battery ();
    void set_percent_battery (uint8_t percent_battery);

    uint16_t get_val_battery ();
    void set_val_battery (uint16_t val_battery);

    uint16_t get_val_tamper ();
    void set_val_tamper (uint16_t val_tamper);

    bool get_status_tamper ();
    void set_status_tamper (bool status_tamper);

    // power data
    bool get_pwr_standby ();
    void set_pwr_standby (bool pwr_standby);

    bool get_pwr_acc ();
    void set_pwr_acc (bool pwr_acc);

    bool get_pwr_engine ();
    void set_pwr_engine (bool pwr_engine);

    // uint32_t get_time_now ();
    // void set_time_now (uint32_t time_now);

    uint32_t get_running_time ();
    void set_running_time (uint32_t running_time);

    uint32_t get_interval_sending ();
    void set_interval_sending (uint32_t interval_sending);

    // gps data
    double get_latitude ();
    void set_latitude (double latitude);

    double get_longitude ();
    void set_longitude (double longitude);

    double get_point_latitude ();
    void set_point_latitude (double point_latitude);

    double get_point_longitude ();
    void set_point_longitude (double point_longitude);

    double get_speed ();
    void set_speed (double speed);

    double get_course ();
    void set_course (double course);

    uint32_t get_radius ();
    void set_radius (uint32_t radius);

    uint32_t get_altitude ();
    void set_altitude (uint32_t altitude);

    uint32_t get_sat_value ();
    void set_sat_value (uint32_t sat_value);


    // env data
    float get_temperature ();
    void set_temperature (float temperature);

    float get_humidity ();
    void set_humidity (float humidity);

    // interval

    uint32_t get_i_msg_tracker ();
    void set_i_msg_tracker (uint32_t i_msg_tracker);
    uint32_t get_i_msg_alert ();
    void set_i_msg_alert (uint32_t i_msg_tracker);
    uint32_t get_i_msg_sos ();
    void set_i_msg_sos (uint32_t i_msg_sos);


  private:
    static deviceStatus* instance;

    // device_data
    uint8_t _p_wifi           = 0;
    uint8_t _p_gsm            = 0;
    uint8_t _p_gps            = 0;
    uint8_t _p_s_env          = 0;
    uint8_t _p_s_gyro         = 0;
    uint8_t _p_s_vibra        = 0;
    uint8_t _p_s_ldr          = 0;
    uint8_t _p_s_batt_devider = 0;
    uint8_t _p_o_buzzer       = 0;


    // interval

    uint32_t _i_msg_tracker = 0;
    uint32_t _i_msg_alert   = 0;
    uint32_t _i_msg_sos     = 0;
    // heavy_data
    std::string _serial_number;
    std::string _heavy_type;
    uint32_t _device_type     = 0;
    uint32_t _production_date = 0;
    uint32_t _runTime         = 0;
    uint32_t _last_usage      = 0;
    //------------------------------

    std::string _imei          = "";
    std::string _wifi_AP_ssid  = "cube-link";
    std::string _wifi_AP_pswd  = "linkingpark";
    std::string _wifi_STA_ssid = "cantik";
    std::string _wifi_STA_pswd = "12345678";

    // esp data
    uint16_t _val_battery      = 0;
    uint8_t _percent_battery   = 0;
    uint16_t _val_tamper       = 0;
    bool _status_tamper        = false;
    bool _pwr_standby          = false;
    bool _pwr_acc              = false;
    bool _pwr_engine           = false;
    uint32_t _time_now         = 0;
    uint32_t _running_time     = 0;
    uint32_t _interval_sending = 0;


    // gps data
    double _latitude        = 0.0; //-6.2788284;//0.0;
    double _longitude       = 0.0; // 106.816666;//0.0;
    double _point_latitude  = 0.0; //-6.2788284;//0.0;
    double _point_longitude = 0.0; // 106.816666;//0.0;
    double _speed           = 0.0;
    double _course          = 0.0;
    uint32_t _radius        = 0;
    uint32_t _altitude      = 0;
    uint32_t _sat_value     = 0;

    // env data
    float _temperature = 0.0;
    float _humidity    = 0.0;

    std::mutex _config_vals_mtx;
};
