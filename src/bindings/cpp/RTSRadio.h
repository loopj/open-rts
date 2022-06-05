#pragma once

#include "rts_radio.h"

class RTSRadio : protected rts_radio {
  public:
    void setMode(rts_radio_mode mode) {
		rts_radio_set_mode(this, mode);
	}
};