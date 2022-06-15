add_library(openrtsxx STATIC)

target_sources(openrtsxx PRIVATE
    RTSFrame.cpp
    RTSFrameBuilder.cpp
    RTSPulseOutput.cpp
    RTSPulseSource.cpp
    RTSRadio.cpp
    RTSReceiver.cpp
    RTSRemote.cpp
)

if(ESP_PLATFORM)
    target_sources(openrtsxx PRIVATE
        espidf/RTSRemoteStore_NVS.cpp
    )
endif()

include(CheckSymbolExists)
check_symbol_exists(mmap "sys/mman.h" OPENRTS_HAVE_MMAP)
if(OPENRTS_HAVE_MMAP)
    target_sources(openrtsxx PRIVATE
        linux/RTSRemoteStore_MMap.cpp
    )
endif()

target_link_libraries(openrtsxx openrts)
target_include_directories(openrtsxx
    INTERFACE ..
    PRIVATE .
)