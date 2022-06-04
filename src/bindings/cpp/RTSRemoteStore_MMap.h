#include "RTSRemoteStore.h"

#include "rts_remote_store_memory.h"

class RTSRemoteStore_MMap : public RTSRemoteStore {
  public:
    RTSRemoteStore_MMap(const char *filepath) {
		rts_remote_store_init_mmap(this, filepath);
    }
};