#include <unity.h>

#include "fixtures.h"
#include "rts_remote.h"

static uint16_t dummy_store_rolling_code = 0;
static error_t _get_code_dummy(rts_remote_store_t *store, uint32_t remote_address, uint16_t *rolling_code) {
    *rolling_code = dummy_store_rolling_code;
    return SOMFYSUITE_ERR_NONE;
}

static error_t _set_code_dummy(rts_remote_store_t *store, uint32_t remote_address, uint16_t rolling_code) {
    dummy_store_rolling_code = rolling_code;
    return SOMFYSUITE_ERR_NONE;
}

static uint16_t pulse_count = 0;
static void _send_pulse_expected_pulse(rts_pulse_output_t *output, bool state, uint32_t micros) {
    recorded_pulse_t *expected_pulses = (recorded_pulse_t *)output->user_data_ptr;

    TEST_ASSERT_EQUAL(expected_pulses[pulse_count].state, state);
    TEST_ASSERT_EQUAL(expected_pulses[pulse_count].micros, micros);

    pulse_count++;
}

static void test_send_command() {
    pulse_count = 0;

    rts_remote_store_t remote_store = {
        .get_code_fn = _get_code_dummy,
        .set_code_fn = _set_code_dummy,
    };
    rts_remote_store_set_code(&remote_store, 0xC0FFEE, 0);

    rts_pulse_output_t pulse_output = {
        .send_pulse_fn = _send_pulse_expected_pulse,
        .user_data_ptr = GENERATED_PULSES_UP,
    };

    rts_remote_t remote;
    rts_remote_init(&remote, &pulse_output, &remote_store, RTS_TIMINGS_DEFAULT);
    rts_remote_send_command(&remote, 0xC0FFEE, RTS_COMMAND_UP, false);

    TEST_ASSERT_EQUAL(121, pulse_count);
}

static void test_send_command_repeated() {
    pulse_count = 0;

    rts_remote_store_t remote_store = {
        .get_code_fn = _get_code_dummy,
        .set_code_fn = _set_code_dummy,
    };
    rts_remote_store_set_code(&remote_store, 0xF00DEE, 0x04D2);

    rts_pulse_output_t pulse_output = {
        .send_pulse_fn = _send_pulse_expected_pulse,
        .user_data_ptr = GENERATED_PULSES_UP_REPEAT,
    };

    rts_remote_t remote;
    rts_remote_init(&remote, &pulse_output, &remote_store, RTS_TIMINGS_DEFAULT);
    rts_remote_send_command(&remote, 0xF00DEE, RTS_COMMAND_UP, false);
    rts_remote_send_command(&remote, 0xF00DEE, RTS_COMMAND_UP, true);

    TEST_ASSERT_EQUAL(250, pulse_count);
}

static void test_send_frame() {
    pulse_count = 0;

    rts_pulse_output_t pulse_output = {
        .send_pulse_fn = _send_pulse_expected_pulse,
        .user_data_ptr = GENERATED_PULSES_UP,
    };

    rts_frame_t frame;
    rts_frame_init(&frame, RTS_COMMAND_UP, 0x0000, 0xC0FFEE);

    rts_remote_t remote;
    rts_remote_init(&remote, &pulse_output, NULL, RTS_TIMINGS_DEFAULT);
    rts_remote_send_frame(&remote, &frame, false);

    TEST_ASSERT_EQUAL(121, pulse_count);
}

static void test_send_frame_repeated() {
    pulse_count = 0;

    rts_pulse_output_t pulse_output = {
        .send_pulse_fn = _send_pulse_expected_pulse,
        .user_data_ptr = GENERATED_PULSES_UP_REPEAT,
    };

    rts_frame_t frame;
    rts_frame_init(&frame, RTS_COMMAND_UP, 0x04D2, 0xF00DEE);

    rts_remote_t remote;
    rts_remote_init(&remote, &pulse_output, NULL, RTS_TIMINGS_DEFAULT);
    rts_remote_send_frame(&remote, &frame, false);
    rts_remote_send_frame(&remote, &frame, true);

    TEST_ASSERT_EQUAL(250, pulse_count);
}

void test_rts_remote() {
    Unity.TestFile = __FILE__;

    RUN_TEST(test_send_command);
    RUN_TEST(test_send_command_repeated);
    RUN_TEST(test_send_frame);
    RUN_TEST(test_send_frame_repeated);
}