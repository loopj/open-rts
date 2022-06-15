add_executable(test_openrts EXCLUDE_FROM_ALL
    ../fixtures.c
    test_main.c
    test_rts_frame_builder.c
    test_rts_frame.c
    test_rts_receiver.c
    test_rts_remote_store.c
    test_rts_remote.c
)

target_link_libraries(test_openrts
    unity
    openrts
)

target_include_directories(test_openrts
    PRIVATE .
)

add_test(test_openrts_test test_openrts)