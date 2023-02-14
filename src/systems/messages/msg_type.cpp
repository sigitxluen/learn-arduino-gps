#include "msg_type.h"

// msg_type::msg_type (/* args */) {}

std::string msg_type::get_msg_tracker () { return _msg_tracker; }
std::string msg_type::get_msg_sos () { return _msg_sos; }
std::string msg_type::get_msg_alert () { return _msg_alert; }

std::string msg_type::get_msg_json_tracker () {
    std::lock_guard<std::mutex> guard (_gen_json_mtx);
    auto _status = deviceStatus::GetInstance ();
    _msg_json_tracker.clear ();
    StaticJsonDocument<1024> root;
    JsonObject doc             = root.to<JsonObject> ();
    doc["TimeStamp"]           = get_time_cube ();
    JsonObject device_info     = doc.createNestedObject ("device_info");
    device_info["SN"]          = WiFi.macAddress ();
    device_info["device_type"] = "1111";
    JsonObject heavy_data      = doc.createNestedObject ("heavy_data");
    heavy_data["run_hours"]    = _status->get_running_time ();
    heavy_data["last_usage"]   = _status->get_last_usage ();
    JsonObject power_status    = heavy_data.createNestedObject ("power_status");
    power_status["volt_battery"]    = _status->get_val_battery ();
    power_status["percent_battery"] = _status->get_percent_battery ();
    power_status["volt_source"]     = (int)12;
    JsonObject tamper_status = heavy_data.createNestedObject ("tamper_status");
    tamper_status["ldr_value"]  = _status->get_val_tamper ();
    tamper_status["ldr_status"] = _status->get_status_tamper ();
    JsonObject location         = heavy_data.createNestedObject ("location");
    location["lat"]             = _status->get_latitude ();
    location["lon"]             = _status->get_longitude ();
    location["sog"]             = _status->get_speed ();
    location["cog"]             = _status->get_course ();
    location["altitude"]        = _status->get_altitude ();
    location["geo_fen"]         = _status->get_radius ();
    location["satelitte"]       = _status->get_sat_value ();
    JsonObject env_status       = heavy_data.createNestedObject ("env_status");
    env_status["temp"]          = _status->get_temperature ();
    env_status["humi"]          = _status->get_humidity ();
    JsonObject input_status = heavy_data.createNestedObject ("input_status");
    input_status["pwr_standby"] = _status->get_pwr_standby ();
    input_status["pwr_acc"]     = _status->get_pwr_acc ();
    input_status["pwr_engine"]  = _status->get_pwr_engine ();
    serializeJson (doc, _msg_json_tracker);
    return _msg_json_tracker;
}
