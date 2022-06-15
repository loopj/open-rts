#include "RTSRemoteStore.hpp"

RTSRemoteStore::RTSRemoteStore()
{
    rts_remote_store::set_code = nullptr;
    rts_remote_store::get_code = nullptr;
    rts_remote_store::forget   = nullptr;
    rts_remote_store::clear    = nullptr;
    rts_remote_store::close    = nullptr;
}

RTSRemoteStore::~RTSRemoteStore()
{
    rts_remote_store_close(this);
}

void RTSRemoteStore::setCode(uint32_t remoteAddress, uint16_t rollingCode)
{
    rts_remote_store_set_code(this, remoteAddress, rollingCode);
}

uint16_t RTSRemoteStore::getCode(uint32_t remoteAddress)
{
    return rts_remote_store_get_code(this, remoteAddress);
}

uint16_t RTSRemoteStore::nextCode(uint32_t remoteAddress)
{
    return rts_remote_store_next_code(this, remoteAddress);
}

bool RTSRemoteStore::knownRemote(uint32_t remoteAddress)
{
    return rts_remote_store_known_remote(this, remoteAddress);
}

void RTSRemoteStore::forget(uint32_t remoteAddress)
{
    rts_remote_store_forget(this, remoteAddress);
}

void RTSRemoteStore::clear()
{
    rts_remote_store_clear(this);
}