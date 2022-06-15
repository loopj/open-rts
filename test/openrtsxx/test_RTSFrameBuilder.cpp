#include <unity.h>

#include <openrtsxx/RTSFrameBuilder.hpp>
#include <openrtsxx/RTSRemote.hpp>

#include "../fixtures.h"

static int callbackCount = 0;

class FrameBuilderPulseOutput : public RTSPulseOutput
{
  public:
    FrameBuilderPulseOutput(RTSFrameBuilder *builder)
    {
        user_data_ptr                = builder;
        rts_pulse_output::send_pulse = [](rts_pulse_output *pulse_output,
                                          bool state, uint32_t micros) {
            ((RTSFrameBuilder *)pulse_output->user_data_ptr)
                ->handlePulse(state, micros);
        };
    }
};

static void TEST_ASSERT_EQUAL_RTS_FRAME_BYTES(RTSFrame *expected,
                                              RTSFrame *actual)
{
    uint8_t expectedBytes[RTS_FRAME_BYTES];
    expected->toBytes(expectedBytes);

    uint8_t actualBytes[RTS_FRAME_BYTES];
    actual->toBytes(actualBytes);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedBytes, actualBytes, RTS_FRAME_BYTES);
}

static void _test_recorded_pulses(recorded_pulse *pulses, size_t size,
                                  RTSFrame *expected, size_t numFrames = 1)
{
    callbackCount = 0;
    RTSFrameBuilder frameBuilder;
    frameBuilder.setFrameCallback(
        [](RTSFrame *actual, uint8_t, uint32_t, void *expected) {
            TEST_ASSERT_EQUAL_RTS_FRAME_BYTES((RTSFrame *)expected, actual);
            callbackCount++;
        },
        expected);

    // Replay recorded pulses
    for (size_t i = 0; i < size; i++) {
        frameBuilder.handlePulse(pulses[i].state, pulses[i].micros);
    }

    TEST_ASSERT_EQUAL(numFrames, callbackCount);
}

static void test_replay_recorded_pulse_up()
{
    RTSFrame expected(RTS_COMMAND_UP, 0x1E63, 0x421FEE);
    expected.encryption_key = 0xA6;

    _test_recorded_pulses(RECORDED_PULSES_UP, 88, &expected);
}

static void test_replay_recorded_pulse_my()
{
    RTSFrame expected(RTS_COMMAND_MY, 0x1E65, 0x421FEE);
    expected.encryption_key = 0xA8;

    _test_recorded_pulses(RECORDED_PULSES_MY, 90, &expected);
}

static void test_replay_recorded_pulse_down()
{
    RTSFrame expected(RTS_COMMAND_DOWN, 0x001E, 0x421FEF);
    expected.encryption_key = 0xAA;

    _test_recorded_pulses(RECORDED_PULSES_DOWN, 90, &expected);
}

static void test_replay_recorded_pulse_prog()
{
    RTSFrame expected(RTS_COMMAND_PROG, 0x0003, 0x3C00B5);
    expected.encryption_key = 0xA9;

    _test_recorded_pulses(RECORDED_PULSES_PROG, 86, &expected);
}

static void test_replay_recorded_pulse_bad_encoding()
{
    _test_recorded_pulses(RECORDED_PULSES_BAD_ENCODING, 86, NULL, 0);
}

static void test_replay_recorded_pulse_up_repeat()
{
    RTSFrame expected(RTS_COMMAND_UP, 0x0790, 0x421FEF);
    expected.encryption_key = 0xAD;

    _test_recorded_pulses(RECORDED_PULSES_UP_REPEAT, 192, &expected, 2);
}

static void test_frame_builder_loopback()
{
    callbackCount = 0;
    RTSFrame expected(RTS_COMMAND_MY, 0x04D2, 0xC0FFEE);
    RTSFrameBuilder frameBuilder;
    frameBuilder.setFrameCallback(
        [](RTSFrame *actual, uint8_t, uint32_t, void *expected) {
            TEST_ASSERT_EQUAL_RTS_FRAME_BYTES((RTSFrame *)expected, actual);
            callbackCount++;
        },
        &expected);

    FrameBuilderPulseOutput pulseOutput(&frameBuilder);
    RTSRemote remote(&pulseOutput);
    remote.sendFrame(&expected);

    TEST_ASSERT_EQUAL(1, callbackCount);
}

static void test_frame_builder_loopback_repeat()
{
    callbackCount = 0;
    RTSFrame expected(RTS_COMMAND_MY, 0x04D2, 0xC0FFEE);
    RTSFrameBuilder frameBuilder;
    frameBuilder.setFrameCallback(
        [](RTSFrame *actual, uint8_t, uint32_t, void *expected) {
            TEST_ASSERT_EQUAL_RTS_FRAME_BYTES((RTSFrame *)expected, actual);
            callbackCount++;
        },
        &expected);

    FrameBuilderPulseOutput pulseOutput(&frameBuilder);
    RTSRemote remote(&pulseOutput);
    remote.sendFrame(&expected);
    remote.sendFrame(&expected, true);

    TEST_ASSERT_EQUAL(2, callbackCount);
}

static void test_frame_builder_loopback_zero_key()
{
    RTSFrame expected(RTS_COMMAND_MY, 0x0000, 0x000000);
    expected.encryption_key = 0x00;

    callbackCount = 0;
    RTSFrameBuilder frameBuilder;
    frameBuilder.setFrameCallback(
        [](RTSFrame *actual, uint8_t, uint32_t, void *expected) {
            TEST_ASSERT_EQUAL_RTS_FRAME_BYTES((RTSFrame *)expected, actual);
            callbackCount++;
        },
        &expected);

    FrameBuilderPulseOutput pulseOutput(&frameBuilder);
    RTSRemote remote(&pulseOutput);
    remote.sendFrame(&expected);

    TEST_ASSERT_EQUAL(1, callbackCount);
}

void test_RTSFrameBuilder()
{
    Unity.TestFile = __FILE__;

    RUN_TEST(test_replay_recorded_pulse_up);
    RUN_TEST(test_replay_recorded_pulse_my);
    RUN_TEST(test_replay_recorded_pulse_down);
    RUN_TEST(test_replay_recorded_pulse_prog);
    RUN_TEST(test_replay_recorded_pulse_bad_encoding);
    RUN_TEST(test_replay_recorded_pulse_up_repeat);

    RUN_TEST(test_frame_builder_loopback);
    RUN_TEST(test_frame_builder_loopback_repeat);
    RUN_TEST(test_frame_builder_loopback_zero_key);
}