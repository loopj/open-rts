#ifndef RTS_REMOTE_STORE_EEPROM_HPP
#define RTS_REMOTE_STORE_EEPROM_HPP

#include "bindings/cpp/RTSRemoteStore.hpp"

class RTSRemoteStore_EEPROM : public RTSRemoteStore
{
  public:
    RTSRemoteStore_EEPROM(uint8_t maxRemotes = 16, uint16_t baseAddress = 0);
};

#endif // RTS_REMOTE_STORE_EEPROM_HPP