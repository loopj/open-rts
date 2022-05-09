#include <unity.h>

#include "rts_receiver.h"

static int callback_count = 0;

static void _mode_change_callback(rts_receiver_mode_t mode, void *user_data) {
    callback_count++;
}

static void test_mode_change_callback() {
    callback_count = 0;

    rts_pulse_source_t pulse_source = {};
    rts_remote_store_t remote_store = {};

    rts_receiver_t receiver;
    rts_receiver_init(&receiver, &pulse_source, &remote_store);
    rts_receiver_set_mode_change_callback(&receiver, _mode_change_callback, NULL);
    rts_receiver_set_mode(&receiver, RTS_RECEIVER_MODE_COMMAND);

    TEST_ASSERT_EQUAL(1, callback_count);
}

void test_rts_receiver() {
    Unity.TestFile = __FILE__;

    RUN_TEST(test_mode_change_callback);
}
