#include "webServer.h"
#include <AsyncElegantOTA.h>


const int buttonPin = 18;  // Pushbutton
int ledState        = LOW; // current state of the output pin
int buttonState;           // current reading from the input pin
int lastButtonState = LOW; // previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers

const char* PARAM_INPUT_1 = "state";
// Web Server HTTP Authentication credentials
const char* http_username = "admin";
const char* http_password = "admin";
webServer::webServer (/* args */) {}

/* Message callback of WebSerial */
void recvMsg (uint8_t* data, size_t len) {
    WebSerial.println ("Received Data...");
    String d = "";
    for (int i = 0; i < len; i++) {
        d += char (data[i]);
    }
    WebSerial.println (d);
}

String outputState (int gpio) {
    if (digitalRead (gpio)) {
        return "checked";
    } else {
        return "";
    }
}

String processor (const String& var) {
    // Serial.println(var);
    if (var == "BUTTONPLACEHOLDER") {
        String buttons;
        String outputStateValue = outputState (32);
        buttons +=
        "<div class=\"card card-switch\"><h4><i class=\"fas "
        "fa-lightbulb\"></i> OUTPUT</h4><label class=\"switch\"><input "
        "type=\"checkbox\" onchange=\"controlOutput(this)\" id=\"output\" " +
        outputStateValue + "><span class=\"slider\"></span></label></div>";
        outputStateValue = outputState (19);
        buttons +=
        "<div class=\"card card-switch\"><h4><i class=\"fas "
        "fa-lightbulb\"></i> STATUS LED</h4><label class=\"switch\"><input "
        "type=\"checkbox\" onchange=\"toggleLed(this)\" id=\"led\" " +
        outputStateValue + "><span class=\"slider\"></span></label></div>";
        return buttons;
    }
    // else if (var == "MOTIONMESSAGE") {
    //     if (!clearMotionAlert) {
    //         return String (
    //         "<span style=\"color:#b30000;\">MOTION DETECTED!</span>");
    //     } else {
    //         return String ("No motion");
    //     }
    // }
    return String ();
}

void webServer::init () {
    // initialize the pushbutton pin as an input
    pinMode (buttonPin, INPUT);
}

void webServer::registerHandler () {
    // Route for root / web page
    // server.on ("/", HTTP_GET, [] (AsyncWebServerRequest* request) {
    //     if (!request->authenticate (http_username, http_password))
    //         return request->requestAuthentication ();
    //     // request->send_P (200, "text/html", index_html, processor);
    //     request->send (SPIFFS, "/index.html", String (), false, processor);
    // });
    // server.on ("/logged-out", HTTP_GET, [] (AsyncWebServerRequest* request) {
    //     // request->send_P (200, "text/html", logout_html, processor);
    //     request->send (SPIFFS, "/logout.html", String (), false, processor);
    // });
    // server.on ("/logout", HTTP_GET,
    //            [] (AsyncWebServerRequest* request) { request->send (401); });
    // // Send a GET request to control output socket <ESP_IP>/output?state=<inputMessage>
    // server.on ("/output", HTTP_GET, [] (AsyncWebServerRequest* request) {
    //     if (!request->authenticate (http_username, http_password))
    //         return request->requestAuthentication ();
    //     String inputMessage;
    //     // GET gpio and state value
    //     if (request->hasParam (PARAM_INPUT_1)) {
    //         inputMessage = request->getParam (PARAM_INPUT_1)->value ();
    //         // digitalWrite (output, inputMessage.toInt ());
    //         request->send (200, "text/plain", "OK");
    //     }
    //     request->send (200, "text/plain", "Failed");
    // });
    // // Send a GET request to control on board status LED <ESP_IP>/toggle
    // server.on ("/toggle", HTTP_GET, [] (AsyncWebServerRequest* request) {
    //     if (!request->authenticate (http_username, http_password))
    //         return request->requestAuthentication ();
    //     ledState = !ledState;
    //     // digitalWrite (ledPin, ledState);
    //     request->send (200, "text/plain", "OK");
    // });
    // // Send a GET request to clear the "Motion Detected" message <ESP_IP>/clear-motion
    // server.on ("/clear-motion", HTTP_GET, [] (AsyncWebServerRequest* request) {
    //     if (!request->authenticate (http_username, http_password))
    //         return request->requestAuthentication ();
    //     // clearMotionAlert = true;
    //     request->send (200, "text/plain", "OK");
    // });
    // events.onConnect ([] (AsyncEventSourceClient* client) {
    //     if (client->lastId ()) {
    //         Serial.printf ("Client reconnected! Last message ID that it got "
    //                        "is: %u\n",
    //                        client->lastId ());
    //     }
    //     // send event with message "hello!", id current millis and set reconnect delay to 1 second
    //     client->send ("hello!", NULL, millis (), 1000);
    // });
    // server.addHandler (&events);

    AsyncElegantOTA.begin (&server); // Start AsyncElegantOTA
    WebSerial.begin (&server);
    server.begin ();
}

void webServer::processDNSRequest () {
    // _dns.processNextRequest ();

    static unsigned long lastEventTime           = millis ();
    static const unsigned long EVENT_INTERVAL_MS = 10000;
    // read the state of the switch into a local variable
    int reading = digitalRead (buttonPin);

    // If the switch changed
    if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis ();
    }

    if ((millis () - lastDebounceTime) > debounceDelay) {
        // if the button state has changed:
        if (reading != buttonState) {
            buttonState = reading;
            // only toggle the LED if the new button state is HIGH
            if (buttonState == HIGH) {
                ledState = !ledState;
                // digitalWrite (ledPin, ledState);
                events.send (String (digitalRead (SOS_PIN)).c_str (),
                             "led_state", millis ());
            }
        }
    }

    if ((millis () - lastEventTime) > EVENT_INTERVAL_MS) {
        auto _status = deviceStatus::GetInstance ();
        events.send ("ping", NULL, millis ());
        events.send (String (get_time_cube ()).c_str (), "unixtime", millis ());
        events.send (String (WiFi.macAddress ()).c_str (), "macAddress", millis ());
        events.send (String (_status->get_running_time ()).c_str (), "run_hours", millis ());
        events.send (String (_status->get_last_usage ()).c_str (), "last_usage", millis ());
        events.send (String (_status->get_val_battery ()).c_str (),
                     "volt_battery", millis ());
        events.send (String (_status->get_percent_battery ()).c_str (),
                     "percent_battery", millis ());
        events.send (String (_status->get_latitude ()).c_str (), "latitude", millis ());
        events.send (String (_status->get_longitude ()).c_str (), "longitude", millis ());
        events.send (String (_status->get_speed ()).c_str (), "speed", millis ());
        events.send (String (_status->get_course ()).c_str (), "course", millis ());
        events.send (String (_status->get_status_tamper ()).c_str (),
                     "status_tamper", millis ());
        events.send (String (_status->get_val_tamper ()).c_str (), "val_tamper", millis ());
        events.send (String (_status->get_pwr_standby ()).c_str (),
                     "pwr_standby", millis ());
        events.send (String (_status->get_pwr_acc ()).c_str (), "pwr_acc", millis ());
        events.send (String (_status->get_pwr_engine ()).c_str (), "pwr_engine", millis ());
        lastEventTime = millis ();
    }

    // if (motionDetected & !clearMotionAlert) {
    //     events.send (String ("MOTION DETECTED!").c_str (), "motion", millis
    //     ()); motionDetected = false;
    // }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;
}