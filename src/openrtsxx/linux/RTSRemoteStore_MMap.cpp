#include "openrts/config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS && OPENRTS_HAS_MMAP

#include "openrts/linux/rts_remote_store_mmap.h"

#include "RTSRemoteStore_MMap.hpp"

RTSRemoteStore_MMap::RTSRemoteStore_MMap(const char *filepath)
{
    rts_remote_store_init_mmap(this, filepath);
}

#endif // OPENRTS_HAS_MMAP