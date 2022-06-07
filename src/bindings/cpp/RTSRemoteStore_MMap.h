#ifndef RTS_REMOTE_STORE_MMAP_CPP_H
#define RTS_REMOTE_STORE_MMAP_CPP_H

#include "RTSRemoteStore.h"

#include "rts_remote_store_memory.h"

class RTSRemoteStore_MMap : public RTSRemoteStore {
  public:
    RTSRemoteStore_MMap(const char *filepath) {
		rts_remote_store_init_mmap(this, filepath);
    }
};

#endif // RTS_REMOTE_STORE_MMAP_CPP_H