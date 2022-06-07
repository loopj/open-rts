#ifndef RTS_REMOTE_STORE_CPP_H
#define RTS_REMOTE_STORE_CPP_H

#include "rts_remote_store.h"

class RTSRemoteStore : protected rts_remote_store
{
  public:
    ~RTSRemoteStore()
    {
        rts_remote_store_close(this);
    }

    void setCode(uint32_t remoteAddress, uint16_t rollingCode)
    {
        rts_remote_store_set_code(this, remoteAddress, rollingCode);
    }

    uint16_t getCode(uint32_t remoteAddress)
    {
        return rts_remote_store_get_code(this, remoteAddress);
    }

    uint16_t nextCode(uint32_t remoteAddress)
    {
        return rts_remote_store_next_code(this, remoteAddress);
    }

    bool knownRemote(uint32_t remoteAddress)
    {
        return rts_remote_store_known_remote(this, remoteAddress);
    }

    void forget(uint32_t remoteAddress)
    {
        rts_remote_store_forget(this, remoteAddress);
    }

    void clear()
    {
        rts_remote_store_clear(this);
    }

  protected:
    RTSRemoteStore()
    {
        rts_remote_store::set_code = nullptr;
        rts_remote_store::get_code = nullptr;
        rts_remote_store::forget   = nullptr;
        rts_remote_store::clear    = nullptr;
        rts_remote_store::close    = nullptr;
    }

    friend class RTSRemote;
    friend class RTSReceiver;
};

#endif // RTS_REMOTE_STORE_CPP_H