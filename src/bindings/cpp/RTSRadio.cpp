#include "config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS

#include "RTSRadio.h"

void RTSRadio::setMode(rts_radio_mode mode)
{
    rts_radio_set_mode(this, mode);
}

#endif // OPENRTS_INCLUDE_CPP_BINDINGS