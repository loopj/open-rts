add_library(openrtsxx STATIC)

target_sources(openrtsxx PRIVATE
    RTSFrame.cpp
    RTSFrameBuilder.cpp
    RTSPulseOutput.cpp
    RTSPulseSource.cpp
    RTSReceiver.cpp
    RTSRemote.cpp
    RTSRemoteStore_Memory.cpp
    RTSRemoteStore.cpp
)

target_include_directories(openrtsxx
    INTERFACE ..
    PRIVATE .
)

target_link_libraries(openrtsxx
    PRIVATE openrts
)

# Include ESP-IDF NVS remote_store when available
if(ESP_PLATFORM)
    target_sources(openrtsxx PRIVATE
        espidf/RTSRemoteStore_NVS.cpp
    )
endif()

# Include memory-mapped remote_store when available
include(CheckSymbolExists)
check_symbol_exists(mmap "sys/mman.h" OPENRTS_HAVE_MMAP)
if(OPENRTS_HAVE_MMAP)
    target_sources(openrtsxx PRIVATE
        linux/RTSRemoteStore_MMap.cpp
    )
endif()