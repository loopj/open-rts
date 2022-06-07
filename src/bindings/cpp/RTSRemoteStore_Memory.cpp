#include "rts_remote_store_memory.h"

#include "RTSRemoteStore_Memory.h"

RTSRemoteStore_Memory::RTSRemoteStore_Memory()
{
    rts_remote_store_init_memory(this);
}