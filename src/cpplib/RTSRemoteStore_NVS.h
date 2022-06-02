#include "RTSRemoteStore.h"

#include "rts_remote_store_nvs.h"

class RTSRemoteStore_NVS : public RTSRemoteStore {
  public:
    RTSRemoteStore_NVS() {
        rts_remote_store_init_nvs(this);
    }
};