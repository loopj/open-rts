#include "config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS

#include "rts_remote_store_memory.h"

#include "RTSRemoteStore_Memory.h"

RTSRemoteStore_Memory::RTSRemoteStore_Memory()
{
    rts_remote_store_init_memory(this);
}

#endif // OPENRTS_INCLUDE_CPP_BINDINGS