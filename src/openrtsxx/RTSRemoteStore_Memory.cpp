#include "openrts/config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS

#include "openrts/rts_remote_store_memory.h"

#include "RTSRemoteStore_Memory.hpp"

RTSRemoteStore_Memory::RTSRemoteStore_Memory()
{
    rts_remote_store_init_memory(this);
}

#endif // OPENRTS_INCLUDE_CPP_BINDINGS