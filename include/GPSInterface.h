#pragma once

#include "stdint.h"

class GPSInterface {
  private:
    /* data */
  public:
    virtual bool initialize ()       = 0;
    virtual float getLongitude ()    = 0;
    virtual float getLatitude ()     = 0;
    virtual int getSpeed ()          = 0;
    virtual int getHeading ()        = 0;
    virtual int getGeoRadius ()      = 0;
    virtual int getSatteliteValue () = 0;
    virtual uint32_t getTimeStamp () = 0;
};