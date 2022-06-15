#include <unity.h>

#include <openrts/rts_receiver.h>

static int callback_count = 0;

static void _mode_callback(enum rts_receiver_mode mode, void *user_data)
{
    callback_count++;
}

static void test_mode_callback()
{
    callback_count = 0;

    struct rts_pulse_source pulse_source = {};
    struct rts_remote_store remote_store = {};

    struct rts_receiver receiver;
    rts_receiver_init(&receiver, &pulse_source, &remote_store);
    rts_receiver_set_mode_callback(&receiver, _mode_callback, NULL);
    rts_receiver_set_mode(&receiver, RTS_RECEIVER_MODE_COMMAND);

    TEST_ASSERT_EQUAL(1, callback_count);
}

void test_rts_receiver()
{
    Unity.TestFile = __FILE__;

    RUN_TEST(test_mode_callback);
}
