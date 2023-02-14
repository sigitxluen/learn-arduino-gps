#include "start_task.h"
#include <Arduino.h>
start_task _start_task;

void setup () {
    Serial.begin (115200);
    _start_task.init_task ();

    // put your setup code here, to run once:
}

void loop () {
    Serial.println ("heart beat...");
    delay (60000);
}