#include "localSpiffs.h"

void localSpiffs::init () {

    if (!SPIFFS.begin ()) {
        Serial.println ("Card Mount Failed");
        return;
    }

    get_device_config ("/config.json");
    get_interval_data ("/interval.json");
    get_heavy_data ("/heavy_data.json");

    checkListDir (SPIFFS, "/outbox/LOW", 0);


    // listDir (SPIFFS, "/", 0);
    // removeDir (SPIFFS, "/mydir");
    // createDir (SPIFFS, "/mydir");
    // deleteFile (SPIFFS, "/hello.txt");
    // writeFile (SPIFFS, "/hello.txt", "Hello ");
    // appendFile (SPIFFS, "/hello.txt", "World!\n");
    // listDir (SPIFFS, "/", 0);
    // readFile (SPIFFS, "/running_data.json");
}

void localSpiffs::get_device_config (const char* path) {
    std::string data = readFileString (SPIFFS, path);
    CUBE_LOG_SERIAL ("%s", data.data ());
    DynamicJsonDocument doc (1024);
    deserializeJson (doc, data);
    JsonObject obj    = doc.as<JsonObject> ();
    uint8_t p_wifi    = obj[String ("peripheral")][String ("wifi")];
    uint8_t p_gsm     = obj[String ("peripheral")][String ("gsm")];
    uint8_t p_gps     = obj[String ("peripheral")][String ("gps")];
    uint8_t p_s_env   = obj[String ("peripheral")][String ("s_env")];
    uint8_t p_s_gyro  = obj[String ("peripheral")][String ("s_gyro")];
    uint8_t p_s_vibra = obj[String ("peripheral")][String ("s_vibra")];
    uint8_t p_s_ldr   = obj[String ("peripheral")][String ("s_ldr")];
    uint8_t p_s_batt_devider =
    obj[String ("peripheral")][String ("s_batt_devider")];
    uint8_t p_o_buzzer =
    obj[String ("peripheral")][String ("o_buzzerp_o_buzzer")];
    auto _status = deviceStatus::GetInstance ();

    _status->set_p_wifi (p_wifi);
    _status->set_p_gsm (p_gsm);
    _status->set_p_gps (p_gps);
    _status->set_p_s_env (p_s_env);
    _status->set_p_s_gyro (p_s_gyro);
    _status->set_p_s_vibra (p_s_vibra);
    _status->set_p_s_ldr (p_s_ldr);
    _status->set_p_s_batt_devider (p_s_batt_devider);
    _status->set_p_o_buzzer (p_o_buzzer);

    CUBE_LOG_SERIAL ("get_p_wifi: %d", _status->get_p_wifi ());
}

void localSpiffs::get_interval_data (const char* path) {
    std::string data = readFileString (SPIFFS, path);
    CUBE_LOG_SERIAL ("%s", data.data ());
    DynamicJsonDocument doc (1024);
    deserializeJson (doc, data);
    JsonObject obj         = doc.as<JsonObject> ();
    uint32_t i_msg_tracker = obj[String ("interval")][String ("msg_tracker")];
    uint32_t i_msg_alert   = obj[String ("interval")][String ("msg_alert")];
    uint32_t i_msg_sos     = obj[String ("interval")][String ("msg_sos")];
    auto _status           = deviceStatus::GetInstance ();

    _status->set_i_msg_tracker (i_msg_tracker);
    _status->set_i_msg_alert (i_msg_alert);
    _status->set_i_msg_sos (i_msg_sos);

    CUBE_LOG_SERIAL ("get_i_msg_tracker: %d", _status->get_i_msg_tracker ());
}

void localSpiffs::get_heavy_data (const char* path) {
    std::string data = readFileString (SPIFFS, path);
    CUBE_LOG_SERIAL ("%s", data.data ());
    DynamicJsonDocument doc (1024);
    deserializeJson (doc, data);
    JsonObject obj            = doc.as<JsonObject> ();
    std::string serial_number = obj[String ("serial_number")];
    std::string heavy_type    = obj[String ("heavy_type")];
    uint32_t device_type      = obj[String ("device_type")];
    uint32_t production_date  = obj[String ("production_date")];
    uint32_t runTime          = obj[String ("runTime")];
    uint32_t last_usage       = obj[String ("last_usage")];
    auto _status              = deviceStatus::GetInstance ();

    _status->set_serial_number (serial_number);
    _status->set_heavy_type (heavy_type);
    _status->set_device_type (device_type);
    _status->set_production_date (production_date);
    _status->set_runTime (runTime);
    _status->set_last_usage (last_usage);

    CUBE_LOG_SERIAL ("set_heavy_type: %d", _status->get_device_type ());
}

void localSpiffs::set_outbox_data (const char* path) {
    listDir (SPIFFS, "/outbox/LOW/1.json", 0);
}