#ifndef RTS_REMOTE_STORE_MMAP_HPP
#define RTS_REMOTE_STORE_MMAP_HPP

#include "../RTSRemoteStore.hpp"

class RTSRemoteStore_MMap : public RTSRemoteStore
{
  public:
    RTSRemoteStore_MMap(const char *filepath);
};

#endif // RTS_REMOTE_STORE_MMAP_HPP