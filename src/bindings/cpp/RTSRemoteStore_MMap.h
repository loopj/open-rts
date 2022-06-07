#ifndef RTS_REMOTE_STORE_MMAP_CPP_H
#define RTS_REMOTE_STORE_MMAP_CPP_H

#include "RTSRemoteStore.h"

class RTSRemoteStore_MMap : public RTSRemoteStore
{
  public:
    RTSRemoteStore_MMap(const char *filepath);
};

#endif // RTS_REMOTE_STORE_MMAP_CPP_H