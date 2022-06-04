#include "RTSRemoteStore.h"

class RTSRemoteStore_EEPROM : public RTSRemoteStore {
  public:
    RTSRemoteStore_EEPROM(uint8_t maxRemotes=16, uint16_t baseAddress=0);
};