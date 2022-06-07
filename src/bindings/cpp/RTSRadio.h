#ifndef RTS_RADIO_CPP_H
#define RTS_RADIO_CPP_H

#include "rts_radio.h"

class RTSRadio : protected rts_radio
{
  public:
    void setMode(rts_radio_mode mode);
};

#endif // RTS_RADIO_CPP_H