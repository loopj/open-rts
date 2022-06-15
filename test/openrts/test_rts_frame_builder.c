#include <unity.h>

#include "../fixtures.h"

#include <openrts/rts_frame_builder.h>
#include <openrts/rts_remote.h>

static void TEST_ASSERT_EQUAL_RTS_FRAME_BYTES(struct rts_frame *expected,
                                              struct rts_frame *actual)
{
    uint8_t expectedBytes[RTS_FRAME_BYTES];
    rts_frame_to_bytes(expected, expectedBytes, false);

    uint8_t actualBytes[RTS_FRAME_BYTES];
    rts_frame_to_bytes(actual, actualBytes, false);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedBytes, actualBytes, RTS_FRAME_BYTES);
}

static uint16_t callback_count = 0;
static void _frame_callback_expected_frame(struct rts_frame *frame,
                                           uint8_t repeatCount,
                                           uint32_t repeatDuration,
                                           void *userData)
{
    TEST_ASSERT_EQUAL_RTS_FRAME_BYTES((struct rts_frame *)userData, frame);
    callback_count++;
}

static void _test_recorded_pulses(const struct recorded_pulse *pulses,
                                  size_t size, struct rts_frame *expected,
                                  size_t repeat_count)
{
    callback_count = 0;

    struct rts_frame_builder frame_builder;
    rts_frame_builder_init(&frame_builder, RTS_TIMINGS_DEFAULT);
    rts_frame_builder_set_callback(&frame_builder,
                                   _frame_callback_expected_frame, expected);

    // Replay recorded pulses
    for (size_t i = 0; i < size; i++) {
        rts_frame_builder_handle_pulse(&frame_builder, pulses[i].state,
                                       pulses[i].micros);
    }

    TEST_ASSERT_EQUAL(repeat_count, callback_count);
}

static void _send_pulse_to_frame_builder(struct rts_pulse_output *pulse_output,
                                         bool state, uint32_t micros)
{
    rts_frame_builder_handle_pulse(
        (struct rts_frame_builder *)pulse_output->user_data_ptr, state, micros);
}

static void test_replay_recorded_pulse_up()
{
    struct rts_frame frame;
    rts_frame_init(&frame, RTS_COMMAND_UP, 0x1E63, 0x421FEE);
    frame.encryption_key = 0xA6;

    _test_recorded_pulses(RECORDED_PULSES_UP, 88, &frame, 1);
}

static void test_replay_recorded_pulse_my()
{
    struct rts_frame frame;
    rts_frame_init(&frame, RTS_COMMAND_MY, 0x1E65, 0x421FEE);
    frame.encryption_key = 0xA8;

    _test_recorded_pulses(RECORDED_PULSES_MY, 90, &frame, 1);
}

static void test_replay_recorded_pulse_down()
{
    struct rts_frame frame;
    rts_frame_init(&frame, RTS_COMMAND_DOWN, 0x001E, 0x421FEF);
    frame.encryption_key = 0xAA;

    _test_recorded_pulses(RECORDED_PULSES_DOWN, 90, &frame, 1);
}

static void test_replay_recorded_pulse_prog()
{
    struct rts_frame frame;
    rts_frame_init(&frame, RTS_COMMAND_PROG, 0x0003, 0x3C00B5);
    frame.encryption_key = 0xA9;

    _test_recorded_pulses(RECORDED_PULSES_PROG, 86, &frame, 1);
}

void test_replay_recorded_pulse_bad_encoding()
{
    _test_recorded_pulses(RECORDED_PULSES_BAD_ENCODING, 86, NULL, 0);
}

static void test_replay_recorded_pulse_up_repeat()
{
    struct rts_frame frame;
    rts_frame_init(&frame, RTS_COMMAND_UP, 0x0790, 0x421FEF);
    frame.encryption_key = 0xAD;

    _test_recorded_pulses(RECORDED_PULSES_UP_REPEAT, 192, &frame, 2);
}

static void test_remote_loopback()
{
    callback_count = 0;

    struct rts_frame frame;
    rts_frame_init(&frame, RTS_COMMAND_MY, 0x04D2, 0xC0FFEE);

    struct rts_frame_builder frame_builder;
    rts_frame_builder_init(&frame_builder, RTS_TIMINGS_DEFAULT);
    rts_frame_builder_set_callback(&frame_builder,
                                   _frame_callback_expected_frame, &frame);

    struct rts_pulse_output pulse_output = {
        .send_pulse    = _send_pulse_to_frame_builder,
        .user_data_ptr = &frame_builder,
    };

    struct rts_remote remote;
    rts_remote_init(&remote, &pulse_output, NULL, RTS_TIMINGS_DEFAULT);
    rts_remote_send_frame(&remote, &frame, false);

    TEST_ASSERT_EQUAL(1, callback_count);
}

static void test_remote_loopback_repeated()
{
    callback_count = 0;

    struct rts_frame frame;
    rts_frame_init(&frame, RTS_COMMAND_MY, 0x04D2, 0xC0FFEE);

    struct rts_frame_builder frame_builder;
    rts_frame_builder_init(&frame_builder, RTS_TIMINGS_DEFAULT);
    rts_frame_builder_set_callback(&frame_builder,
                                   _frame_callback_expected_frame, &frame);

    struct rts_pulse_output pulse_output = {
        .send_pulse    = _send_pulse_to_frame_builder,
        .user_data_ptr = &frame_builder,
    };

    struct rts_remote remote;
    rts_remote_init(&remote, &pulse_output, NULL, RTS_TIMINGS_DEFAULT);
    rts_remote_send_frame(&remote, &frame, false);
    rts_remote_send_frame(&remote, &frame, true);

    TEST_ASSERT_EQUAL(2, callback_count);
}

static void test_remote_loopback_zero_key()
{
    callback_count = 0;

    struct rts_frame frame;
    rts_frame_init(&frame, RTS_COMMAND_MY, 0x0000, 0x000000);
    frame.encryption_key = 0x00;

    struct rts_frame_builder frame_builder;
    rts_frame_builder_init(&frame_builder, RTS_TIMINGS_DEFAULT);
    rts_frame_builder_set_callback(&frame_builder,
                                   _frame_callback_expected_frame, &frame);

    struct rts_pulse_output pulse_output = {
        .send_pulse    = _send_pulse_to_frame_builder,
        .user_data_ptr = &frame_builder,
    };

    struct rts_remote remote;
    rts_remote_init(&remote, &pulse_output, NULL, RTS_TIMINGS_DEFAULT);
    rts_remote_send_frame(&remote, &frame, false);

    TEST_ASSERT_EQUAL(1, callback_count);
}

void test_rts_frame_builder()
{
    Unity.TestFile = __FILE__;

    RUN_TEST(test_replay_recorded_pulse_up);
    RUN_TEST(test_replay_recorded_pulse_my);
    RUN_TEST(test_replay_recorded_pulse_down);
    RUN_TEST(test_replay_recorded_pulse_prog);
    RUN_TEST(test_replay_recorded_pulse_bad_encoding);
    RUN_TEST(test_replay_recorded_pulse_up_repeat);

    RUN_TEST(test_remote_loopback);
    RUN_TEST(test_remote_loopback_repeated);
    RUN_TEST(test_remote_loopback_zero_key);
}
