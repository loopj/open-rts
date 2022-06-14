#include "config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS && OPENRTS_HAS_NVS

#include "espidf/rts_remote_store_nvs.h"

#include "RTSRemoteStore_NVS.hpp"

RTSRemoteStore_NVS::RTSRemoteStore_NVS()
{
    rts_remote_store_init_nvs(this);
}

#endif // OPENRTS_HAS_NVS