#include "rts_command.h"
#include "rts_frame.h"
#include "rts_frame_builder.h"
#include "rts_pulse_output.h"
#include "rts_receiver.h"
#include "rts_remote.h"
#include "rts_remote_store.h"
#include "rts_timings.h"

#if defined(ESP_PLATFORM)
    #include "rts_remote_store_nvs.h"
#endif

#if defined(ARDUINO)
    #include "cpplib/RTSFrame.h"
    #include "cpplib/RTSFrameBuilder.h"
    #include "cpplib/RTSPulseOutput.h"
    #include "cpplib/RTSPulseOutput_GPIO.h"
    #include "cpplib/RTSPulseSource.h"
    #include "cpplib/RTSPulseSource_GPIO.h"
    #include "cpplib/RTSRemote.h"
    #include "cpplib/RTSRemoteStore.h"
    #include "cpplib/RTSRemoteStore_EEPROM.h"

    #if defined(ESP_PLATFORM)
        #include "cpplib/RTSRemoteStore_NVS.h"
    #endif
#endif

