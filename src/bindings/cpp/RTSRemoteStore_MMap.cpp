#include "config.h"

#if OPENRTS_HAS_POSIX

#include "rts_remote_store_memory.h"

#include "RTSRemoteStore_MMap.h"

RTSRemoteStore_MMap::RTSRemoteStore_MMap(const char *filepath)
{
    rts_remote_store_init_mmap(this, filepath);
}

#endif // OPENRTS_HAS_POSIX