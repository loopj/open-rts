#ifndef RTS_REMOTE_STORE_HPP
#define RTS_REMOTE_STORE_HPP

#include <openrts/rts_remote_store.h>

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
    ~RTSRemoteStore();

    /**
     * Set the rolling code for this remote, create if doesn't exist
     *
     * @param remoteAddress the address of the remote control
     * @param rollingCode the rolling code to set
     */
    void setCode(uint32_t remoteAddress, uint16_t rollingCode);

    /**
     * Get the rolling code for this remote
     *
     * @param remoteAddress the address of the remote control
     *
     * @return the rolling code for this remote
     */
    uint16_t getCode(uint32_t remoteAddress);

    /**
     * Get the rolling code for this remote, then increment and persist
     *
     * @param remoteAddress the address of the remote control
     *
     * @return the rolling code for this remote
     */
    uint16_t nextCode(uint32_t remoteAddress);

    /**
     * Check if this is a known remote address
     *
     * @param remoteAddress the address of the remote control
     */
    bool knownRemote(uint32_t remoteAddress);

    /**
     * Forget a specific remote
     *
     * @param remoteAddress the address of the remote control to forget
     */
    void forget(uint32_t remoteAddress);

    /**
     * Clear all remotes and rolling codes
     */
    void clear();

  protected:
    RTSRemoteStore();

    friend class RTSRemote;
    friend class RTSReceiver;
};

/**
 * @}
 */

#endif // RTS_REMOTE_STORE_HPP