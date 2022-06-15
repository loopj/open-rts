add_executable(test_openrtsxx EXCLUDE_FROM_ALL
    ../fixtures.c
    test_main.cpp
    test_RTSFrameBuilder.cpp
    test_RTSFrame.cpp
    test_RTSRemoteStore.cpp
    test_RTSRemote.cpp
)

target_link_libraries(test_openrtsxx
    unity
    openrtsxx
)

target_include_directories(test_openrtsxx
    PRIVATE .
)

add_test(test_openrtsxx_test test_openrtsxx)