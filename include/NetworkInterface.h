#pragma once

class NetworkInterface {
  public:
    virtual bool init ()           = 0;
    virtual bool wakeup ()         = 0;
    virtual bool sleep ()          = 0;
    virtual bool powerOff ()       = 0;
    virtual bool powerOn ()        = 0;
    virtual bool sendBinaryData () = 0;
    virtual bool sendTextData ()   = 0;
    // virtual bool sendReceiveBinaryData ();
    // virtual bool sendReceiveTextData ();
};