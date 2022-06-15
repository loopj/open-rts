#ifndef RTS_REMOTE_STORE_HPP
#define RTS_REMOTE_STORE_HPP

#include "openrts/rts_remote_store.h"

/**
 * @file
 */

/**
 * @addtogroup openrtsxx
 * @{
 */

/**
 * Provides an interface for a datastore which contains details about remote
 * controls and rolling codes.
 *
 * Implementations must define the get_code, set_code, forget, and clear
 * functions and set the function pointers in the rts_remote_store struct.
 */
class RTSRemoteStore : protected rts_remote_store
{
  public:
    ~RTSRemoteStore()
    {
        rts_remote_store_close(this);
    }

    /**
     * Set the rolling code for this remote, create if doesn't exist
     *
     * @param remoteAddress the address of the remote control
     * @param rollingCode the rolling code to set
     */
    void setCode(uint32_t remoteAddress, uint16_t rollingCode)
    {
        rts_remote_store_set_code(this, remoteAddress, rollingCode);
    }

    /**
     * Get the rolling code for this remote
     *
     * @param remoteAddress the address of the remote control
     *
     * @return the rolling code for this remote
     */
    uint16_t getCode(uint32_t remoteAddress)
    {
        return rts_remote_store_get_code(this, remoteAddress);
    }

    /**
     * Get the rolling code for this remote, then increment and persist
     *
     * @param remoteAddress the address of the remote control
     *
     * @return the rolling code for this remote
     */
    uint16_t nextCode(uint32_t remoteAddress)
    {
        return rts_remote_store_next_code(this, remoteAddress);
    }

    /**
     * Check if this is a known remote address
     *
     * @param remoteAddress the address of the remote control
     */
    bool knownRemote(uint32_t remoteAddress)
    {
        return rts_remote_store_known_remote(this, remoteAddress);
    }

    /**
     * Forget a specific remote
     *
     * @param remoteAddress the address of the remote control to forget
     */
    void forget(uint32_t remoteAddress)
    {
        rts_remote_store_forget(this, remoteAddress);
    }

    /**
     * Clear all remotes and rolling codes
     */
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

/**
 * @}
 */

#endif // RTS_REMOTE_STORE_HPP