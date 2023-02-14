#include "start_task.h"

// start_task::start_task (/* args */) {}
bool start_task::init_task () {
    _spiffs.init ();
    _ll.start ();
    _run_hours.start ();
    _gps.start ();


    _msg_sending.start ();

    delay (10000);
    
    _sleep.start ();

    return 1;
}
