#include "wifi_start.h"


wifi_start::wifi_start (/* args */) {}

void wifi_start::start_STA () {
    auto _status = deviceStatus::GetInstance ();

    WiFi.mode (WIFI_STA);
    WiFi.config (INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname (hostname.c_str ()); // define hostname
    WiFi.begin (_status->get_wifi_sta_ssid ().c_str (),
                _status->get_wifi_sta_pswd ().c_str ());
    Serial.print ("Connecting to WiFi ..");
    while (WiFi.status () != WL_CONNECTED) {
        Serial.print ('.');
        delay (1000);
    }
    Serial.println (WiFi.localIP ());
}

void wifi_start::start_AP () {
    WiFi.mode (WIFI_AP);

    auto _status = deviceStatus::GetInstance ();

    // Connect to Wi-Fi network with SSID and password
    Serial.print ("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP (_status->get_wifi_ap_ssid ().c_str (),
                 _status->get_wifi_ap_pswd ().c_str ());

    IPAddress IP = WiFi.softAPIP ();
    Serial.print ("AP IP address: ");
    Serial.println (IP);
}

void wifi_start::check_AP_connection(){

    
}