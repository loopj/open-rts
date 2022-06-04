#include "RTSRemoteStore.h"

#include "rts_remote_store_memory.h"

class RTSRemoteStore_Memory : public RTSRemoteStore {
  public:
    RTSRemoteStore_Memory() {
        rts_remote_store_init_memory(this);
    }
};