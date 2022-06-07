#ifndef RTS_REMOTE_STORE_MEMORY_CPP_H
#define RTS_REMOTE_STORE_MEMORY_CPP_H

#include "RTSRemoteStore.h"

#include "rts_remote_store_memory.h"

class RTSRemoteStore_Memory : public RTSRemoteStore {
  public:
    RTSRemoteStore_Memory() {
        rts_remote_store_init_memory(this);
    }
};

#endif // RTS_REMOTE_STORE_MEMORY_CPP_H