#include "hoursCountHandler.h"

hoursCountHandler::hoursCountHandler () {}

void hoursCountHandler::start () {
    xTaskCreatePinnedToCore (HandlerWrapper, "hoursCountHandler", 6 * 1024,
                             this, 3, NULL, 0);
}

bool hoursCountHandler::initialize () { return 1; }

void hoursCountHandler::entrypoint () {
    auto _status = deviceStatus::GetInstance ();

    std::string data = fs.readFileString (SPIFFS, "/running_data.json");
    CUBE_LOG_SERIAL ("%s", data.data ());
    DynamicJsonDocument doc (1024);
    deserializeJson (doc, data);
    JsonObject obj    = doc.as<JsonObject> ();
    uint32_t run_time = obj[String ("runTime")];

    _status->set_running_time (run_time);
    CUBE_LOG_SERIAL ("runTime: %d", run_time);

    time_t seconds;

    long timer = seconds;

    bool inputPower = false;
    inputPower      = true;

    while (1) {
        delay (500);
        if (gpio.get_acc_status () || gpio.get_engine_status ()) {
            delay (59500);
            run_time++;
            time (&seconds);

            obj[String ("runTime")]    = run_time;
            obj[String ("last_usage")] = seconds;
            _status->set_running_time (run_time);
            _status->set_last_usage (seconds);

            std::string output;
            serializeJson (doc, output);
            fs.writeFileString (SPIFFS, "/running_data.json", output.data ());
            // CUBE_LOG_SERIAL ("run time: %d", run_time);
            // CUBE_LOG_SERIAL ("last_usage: %d", seconds);
        }
    }
}