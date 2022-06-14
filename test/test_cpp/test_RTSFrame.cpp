#include <unity.h>

#include "bindings/cpp/RTSFrame.hpp"

static void test_fromBytes()
{
    uint8_t bytes[] = {0xAB, 0x2F, 0x00, 0x7B, 0xDE, 0xCA, 0xFA};

    RTSFrame frame(bytes);

    TEST_ASSERT_EQUAL_HEX8(frame.command, RTS_COMMAND_UP);
    TEST_ASSERT_EQUAL_HEX16(frame.rolling_code, 0x007B);
    TEST_ASSERT_EQUAL_HEX32(frame.remote_address, 0xFACADE);
}

static void test_toBytes()
{
    RTSFrame frame(RTS_COMMAND_UP, 0x7B, 0xFACADE);

    uint8_t bytes[RTS_FRAME_BYTES];
    frame.toBytes(bytes);

    uint8_t expected[] = {0xAB, 0x2F, 0x00, 0x7B, 0xDE, 0xCA, 0xFA};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, bytes, RTS_FRAME_BYTES);
}

void test_obfuscateBytes()
{
    uint8_t bytes[] = {0xA3, 0x29, 0x1E, 0x63, 0xEE, 0x1F, 0x42};
    RTSFrame::obfuscateBytes(bytes);

    uint8_t expected[] = {0xA3, 0x8A, 0x94, 0xF7, 0x19, 0x06, 0x44};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, bytes, RTS_FRAME_BYTES);
}

void test_deobfuscateBytes()
{
    uint8_t deobfuscated[RTS_FRAME_BYTES];
    uint8_t obfuscated[] = {0xA3, 0x8A, 0x94, 0xF7, 0x19, 0x06, 0x44};
    RTSFrame::deobfuscateBytes(deobfuscated, obfuscated);

    uint8_t expected[] = {0xA3, 0x29, 0x1E, 0x63, 0xEE, 0x1F, 0x42};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, deobfuscated, RTS_FRAME_BYTES);
}

void test_generateChecksum()
{
    uint8_t frame[] = {0xA3, 0x29, 0x1E, 0x63, 0xEE, 0x1F, 0x42};
    TEST_ASSERT_EQUAL_UINT8(0, RTSFrame::generateChecksum(frame));
}

void test_RTSFrame()
{
    Unity.TestFile = __FILE__;

    RUN_TEST(test_fromBytes);
    RUN_TEST(test_toBytes);
    RUN_TEST(test_obfuscateBytes);
    RUN_TEST(test_deobfuscateBytes);
    RUN_TEST(test_generateChecksum);
}