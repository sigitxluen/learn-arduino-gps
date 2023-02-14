#include "sim900a_mqtt.h"

/**************************************************************
 *
 * For this example, you need to install PubSubClient library:
 *   https://github.com/knolleary/pubsubclient
 *   or from http://librarymanager/all#PubSubClient
 *
 * TinyGSM Getting Started guide:
 *   https://tiny.cc/tinygsm-readme
 *
 * For more MQTT examples, see PubSubClient library
 *
 **************************************************************
 * This example connects to HiveMQ's showcase broker.
 *
 * You can quickly test sending and receiving messages from the HiveMQ webclient
 * available at http://www.hivemq.com/demos/websocket-client/.
 *
 * Subscribe to the topic GsmClientTest/ledStatus
 * Publish "toggle" to the topic GsmClientTest/led and the LED on your board
 * should toggle and you should see a new message published to
 * GsmClientTest/ledStatus with the newest LED status.
 *
 **************************************************************/

// Select your modem:
// #define TINY_GSM_MODEM_SIM800
// #define TINY_GSM_MODEM_SIM808
// #define TINY_GSM_MODEM_SIM868
#define TINY_GSM_MODEM_SIM900
// #define TINY_GSM_MODEM_SIM7000
// #define TINY_GSM_MODEM_SIM7000SSL
// #define TINY_GSM_MODEM_SIM7080
// #define TINY_GSM_MODEM_SIM5360
// #define TINY_GSM_MODEM_SIM7600
// #define TINY_GSM_MODEM_UBLOX
// #define TINY_GSM_MODEM_SARAR4
// #define TINY_GSM_MODEM_M95
// #define TINY_GSM_MODEM_BG96
// #define TINY_GSM_MODEM_A6
// #define TINY_GSM_MODEM_A7
// #define TINY_GSM_MODEM_M590
// #define TINY_GSM_MODEM_MC60
// #define TINY_GSM_MODEM_MC60E
// #define TINY_GSM_MODEM_ESP8266
// #define TINY_GSM_MODEM_XBEE
// #define TINY_GSM_MODEM_SEQUANS_MONARCH

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#ifndef __AVR_ATmega328P__
#define SerialAT Serial2

// or Software Serial on Uno, Nano
#else
#include <SoftwareSerial.h>
SoftwareSerial SerialAT (2, 3); // RX, TX
#endif

// See all AT commands, if wanted
// #define DUMP_AT_COMMANDS

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon

// Range to attempt to autobaud
// NOTE:  DO NOT AUTOBAUD in production code.  Once you've established
// communication, set a fixed baud rate using modem.setBaud(#).
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 230400

// Add a reception delay, if needed.
// This may be needed for a fast processor at a slow baud rate.
// #define TINY_GSM_YIELD() { delay(2); }

// Define how you're planning to connect to the internet.
// This is only needed for this example, not in other code.
#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false


// set GSM PIN, if any
#define GSM_PIN ""

// Your GPRS credentials, if any
const char apn[]      = "internet";
const char gprsUser[] = "";
const char gprsPass[] = "";

// Your WiFi connection credentials, if applicable
const char wifiSSID[] = "YourSSID";
const char wifiPass[] = "YourWiFiPass";

// MQTT details
// const char* broker = "broker.hivemq.com";

const char* broker = "52.69.255.27";

const char* topicLed       = "zotak/GsmClientTest/led";
const char* topicInit      = "zotak/GsmClientTest/init";
const char* topicLedStatus = "zotak/GsmClientTest/ledStatus";

#include <PubSubClient.h>
#include <TinyGsmClient.h>

// Just in case someone defined the wrong thing..
#if TINY_GSM_USE_GPRS && not defined TINY_GSM_MODEM_HAS_GPRS
#undef TINY_GSM_USE_GPRS
#undef TINY_GSM_USE_WIFI
#define TINY_GSM_USE_GPRS false
#define TINY_GSM_USE_WIFI true
#endif
#if TINY_GSM_USE_WIFI && not defined TINY_GSM_MODEM_HAS_WIFI
#undef TINY_GSM_USE_GPRS
#undef TINY_GSM_USE_WIFI
#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false
#endif

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger (SerialAT, SerialMon);
TinyGsm modem (debugger);
#else
TinyGsm modem (SerialAT);
#endif
TinyGsmClient client (modem);
PubSubClient mqtt (client);

#define LED_PIN 13
int ledStatus = LOW;

uint32_t lastReconnectAttempt = 0;

void mqttCallback (char* topic, byte* payload, unsigned int len) {
    SerialMon.print ("Message arrived [");
    SerialMon.print (topic);
    SerialMon.print ("]: ");
    SerialMon.write (payload, len);
    SerialMon.println ();

    // Only proceed if incoming message's topic matches
    if (String (topic) == topicLed) {
        ledStatus = !ledStatus;
        digitalWrite (LED_PIN, ledStatus);
        mqtt.publish (topicLedStatus, ledStatus ? "1" : "0");
    }
}

boolean mqttConnect () {
    SerialMon.print ("Connecting to ");
    SerialMon.print (broker);

    // Connect to MQTT Broker
    // boolean status = mqtt.connect ("GsmClientTest-zotak");

    // Or, if you want to authenticate MQTT:
    // boolean status = mqtt.connect("GsmClientName", "mqtt_user", "mqtt_pass");
    String client_name = "cube-link-" + WiFi.macAddress ();
    boolean status = mqtt.connect (client_name.c_str (), "ahaalink", "kopiitem");


    if (status == false) {
        SerialMon.println (" fail");
        return false;
    }
    SerialMon.println (" success");
    mqtt.publish (topicInit, "GsmClientTest started");
    mqtt.subscribe (topicLed);
    return mqtt.connected ();
}


sim900a::sim900a (/* args */) {}
void sim900a::initialize () {
    // Serial2.begin (57600, SERIAL_8N1, 16, 17);

    TinyGsmAutoBaud (SerialAT, 0, 115200);

    // SerialAT.begin (115200);

    delay (6000);

    // Restart takes quite some time
    // To skip it, call init() instead of restart()
    SerialMon.println ("Initializing modem...");
    // modem.restart();
    modem.init ();

    String modemInfo = modem.getModemInfo ();
    SerialMon.print ("Modem Info: ");
    SerialMon.println (modemInfo);

#if TINY_GSM_USE_GPRS
    // Unlock your SIM card with a PIN if needed
    if (GSM_PIN && modem.getSimStatus () != 3) {
        modem.simUnlock (GSM_PIN);
    }
#endif

#if TINY_GSM_USE_WIFI
    // Wifi connection parameters must be set before waiting for the network
    SerialMon.print (F ("Setting SSID/password..."));
    if (!modem.networkConnect (wifiSSID, wifiPass)) {
        SerialMon.println (" fail");
        delay (10000);
        return;
    }
    SerialMon.println (" success");
#endif

#if TINY_GSM_USE_GPRS && defined TINY_GSM_MODEM_XBEE
    // The XBee must run the gprsConnect function BEFORE waiting for network!
    modem.gprsConnect (apn, gprsUser, gprsPass);
#endif

    SerialMon.print ("Waiting for network...");
    if (!modem.waitForNetwork ()) {
        SerialMon.println (" fail");
        delay (10000);
        return;
    }
    SerialMon.println (" success");

    if (modem.isNetworkConnected ()) {
        SerialMon.println ("Network connected");
    }

#if TINY_GSM_USE_GPRS
    // GPRS connection parameters are usually set after network registration
    SerialMon.print (F ("Connecting to "));
    SerialMon.print (apn.c_str ());
    if (!modem.gprsConnect (apn.c_str (), gprsUser.c_str (), gprsPass.c_str ())) {
        SerialMon.println (" fail");
        delay (10000);
        return;
    }
    SerialMon.println (" success");

    if (modem.isGprsConnected ()) {
        SerialMon.println ("GPRS connected");
    }
#endif

    // MQTT Broker setup
    mqtt.setServer (broker, 1883);
    // mqtt.setCallback (mqttCallback);
    mqtt.setCallback (_cmd.mqttCallback);
}

void sim900a::start_gsm () {}
void sim900a::check_mqtt () {
    if (!mqtt.connected ()) {
        SerialMon.println ("=== MQTT NOT CONNECTED ===");
        // Reconnect every 10 seconds
        uint32_t t = millis ();
        if (t - lastReconnectAttempt > 10000L) {
            lastReconnectAttempt = t;
            if (mqttConnect ()) {
                lastReconnectAttempt = 0;
            }
        }
        delay (100);
        return;
    }
    mqtt.loop ();
}
void sim900a::check_network () {
    // Make sure we're still registered on the network
    if (!modem.isNetworkConnected ()) {
        SerialMon.println ("Network disconnected");
        if (!modem.waitForNetwork (180000L, true)) {
            SerialMon.println (" fail");
            delay (10000);
            return;
        }
        if (modem.isNetworkConnected ()) {
            SerialMon.println ("Network re-connected");
        }

        // #if TINY_GSM_USE_GPRS
        // and make sure GPRS/EPS is still connected
        if (!modem.isGprsConnected ()) {
            SerialMon.println ("GPRS disconnected!");
            SerialMon.print (F ("Connecting to "));
            SerialMon.print (apn.c_str ());
            if (!modem.gprsConnect (apn.c_str (), gprsUser.c_str (), gprsPass.c_str ())) {
                SerialMon.println (" fail");
                delay (10000);
                return;
            }
            if (modem.isGprsConnected ()) {
                SerialMon.println ("GPRS reconnected");
            }
        }
        // #endif
    }
}

void sim900a::publish_data (const char* topic, const char* payload) {
    // Connect to MQTT Broker
    // boolean status = mqtt.connect ("GsmClientTest-zotak");

    // modem.sendAT ();
    // Or, if you want to authenticate MQTT:
    // boolean status = mqtt.connect("GsmClientName", "mqtt_user", "mqtt_pass");
    // boolean status = mqtt.connect ("GsmClientTest-zotak", "ahaalink", "kopiitem");
    String client_name = "cube-link-" + WiFi.macAddress ();
    boolean status = mqtt.connect (client_name.c_str (), "ahaalink", "kopiitem");

    if (status == false) {
        SerialMon.println (" fail");
        // return false;
    }
    SerialMon.println ("sending -> success");
    mqtt.publish (topic, payload);
    mqtt.subscribe (topicLed);


    delay (1000);
    // modem.sleepEnable ();
    // modem.poweroff ();
}

void sim900a::sim_sleep () {

    modem.testAT ();
    modem.waitResponse ();
    _gpio.set_DTR_ON ();
    modem.sendAT (GF ("+CSCLK=2"));
    modem.waitResponse ();
    _gpio.set_DTR_OFF ();

}

void sim900a::sim_wake_up () {

    modem.testAT ();
    modem.waitResponse ();
    // _gpio.set_DTR_ON();
    modem.sendAT (GF ("+CSCLK=0"));
    modem.waitResponse ();
    modem.testAT ();
    modem.waitResponse ();
}