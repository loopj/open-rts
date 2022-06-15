#include <openrts/config.h>

#if OPENRTS_HAS_NVS

#include <openrts/espidf/rts_remote_store_nvs.h>

#include "RTSRemoteStore_NVS.hpp"

RTSRemoteStore_NVS::RTSRemoteStore_NVS()
{
    rts_remote_store_init_nvs(this);
}

#endif // OPENRTS_HAS_NVS