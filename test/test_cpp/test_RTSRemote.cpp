#include <unity.h>

#include "fixtures.h"

#include "bindings/cpp/RTSPulseOutput.hpp"
#include "bindings/cpp/RTSRemote.hpp"
#include "bindings/cpp/RTSRemoteStore.hpp"

static uint16_t pulseCount = 0;

class DummyRemoteStore : public RTSRemoteStore
{
  public:
    DummyRemoteStore()
    {
        rts_remote_store::get_code = [](rts_remote_store *store,
                                        uint32_t remote_address,
                                        uint16_t *rolling_code) -> int8_t {
            *rolling_code = store->user_data_int;
            return RTS_ERR_NONE;
        };

        rts_remote_store::set_code = [](rts_remote_store *store,
                                        uint32_t remote_address,
                                        uint16_t rolling_code) -> int8_t {
            store->user_data_int = rolling_code;
            return RTS_ERR_NONE;
        };

        user_data_int = 0;
    }
};

class DummyPulseOutput : public RTSPulseOutput
{
  public:
    typedef void (*Callback)(bool, uint32_t);

    DummyPulseOutput(Callback callback = nullptr)
    {
        rts_pulse_output::send_pulse = [](rts_pulse_output *output, bool state,
                                          uint32_t micros) {
            if (output->user_data_ptr) {
                ((Callback)output->user_data_ptr)(state, micros);
            }
        };

        user_data_ptr = (void *)callback;
    }
};

static void test_sendCommand()
{
    pulseCount = 0;

    DummyPulseOutput pulseOutput([](bool state, uint32_t micros) {
        TEST_ASSERT_EQUAL(GENERATED_PULSES_UP[pulseCount].state, state);
        TEST_ASSERT_EQUAL(GENERATED_PULSES_UP[pulseCount].micros, micros);

        pulseCount++;
    });

    RTSRemote remote(&pulseOutput, new DummyRemoteStore());
    remote.sendCommand(0xC0FFEE, RTS_COMMAND_UP);

    TEST_ASSERT_EQUAL(121, pulseCount);
}

static void test_sendCommand_repeated()
{
    pulseCount = 0;

    DummyPulseOutput pulseOutput([](bool state, uint32_t micros) {
        TEST_ASSERT_EQUAL(GENERATED_PULSES_UP_REPEAT[pulseCount].state, state);
        TEST_ASSERT_EQUAL(GENERATED_PULSES_UP_REPEAT[pulseCount].micros,
                          micros);

        pulseCount++;
    });

    DummyRemoteStore remoteStore;
    remoteStore.setCode(0xF00DEE, 0x04D2);

    RTSRemote remote(&pulseOutput, &remoteStore);
    remote.sendCommand(0xF00DEE, RTS_COMMAND_UP);
    remote.sendCommand(0xF00DEE, RTS_COMMAND_UP, true);

    TEST_ASSERT_EQUAL(250, pulseCount);
}

static void test_sendFrame()
{
    pulseCount = 0;

    DummyPulseOutput pulseOutput([](bool state, uint32_t micros) {
        TEST_ASSERT_EQUAL(GENERATED_PULSES_UP[pulseCount].state, state);
        TEST_ASSERT_EQUAL(GENERATED_PULSES_UP[pulseCount].micros, micros);

        pulseCount++;
    });

    RTSRemote remote(&pulseOutput);
    RTSFrame expected(RTS_COMMAND_UP, 0x0000, 0xC0FFEE);
    remote.sendFrame(&expected);

    TEST_ASSERT_EQUAL(121, pulseCount);
}

static void test_sendFrame_repeated()
{
    pulseCount = 0;

    DummyPulseOutput pulseOutput([](bool state, uint32_t micros) {
        TEST_ASSERT_EQUAL(GENERATED_PULSES_UP_REPEAT[pulseCount].state, state);
        TEST_ASSERT_EQUAL(GENERATED_PULSES_UP_REPEAT[pulseCount].micros,
                          micros);

        pulseCount++;
    });

    RTSRemote remote(&pulseOutput);
    RTSFrame expected(RTS_COMMAND_UP, 0x04D2, 0xF00DEE);
    remote.sendFrame(&expected);
    remote.sendFrame(&expected, true);

    TEST_ASSERT_EQUAL(250, pulseCount);
}

void test_RTSRemote()
{
    Unity.TestFile = __FILE__;

    RUN_TEST(test_sendCommand);
    RUN_TEST(test_sendCommand_repeated);
    RUN_TEST(test_sendFrame);
    RUN_TEST(test_sendFrame_repeated);
}