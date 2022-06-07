#include "RTSRadio.h"

void RTSRadio::setMode(rts_radio_mode mode)
{
    rts_radio_set_mode(this, mode);
}