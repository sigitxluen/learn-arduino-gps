#include "callback_cmd.h"

void callback_cmd::mqttCallback (char* topic, byte* payload, unsigned int len) {
    std::string messageTemp;
    for (int i = 0; i < len; i++) {
        // Serial.print ((char)payload[i]);
        messageTemp += (char)payload[i];
    }
    CUBE_LOG_SERIAL ("%s", messageTemp.c_str ());

    // // Only proceed if incoming message's topic matches
    // if (String (topic) == topicLed) {
    //     ledStatus = !ledStatus;
    //     digitalWrite (LED_PIN, ledStatus);
    //     mqtt.publish (topicLedStatus, ledStatus ? "1" : "0");
    // }
}