#include <unity.h>

#include <openrts/rts_frame.h>

static void test_from_bytes()
{
    uint8_t bytes[] = {0xAB, 0x2F, 0x00, 0x7B, 0xDE, 0xCA, 0xFA};

    struct rts_frame frame;
    rts_frame_from_bytes(&frame, bytes);

    TEST_ASSERT_EQUAL_HEX8(frame.command, RTS_COMMAND_UP);
    TEST_ASSERT_EQUAL_HEX16(frame.rolling_code, 0x007B);
    TEST_ASSERT_EQUAL_HEX32(frame.remote_address, 0xFACADE);
}

void test_to_bytes()
{
    struct rts_frame frame;
    rts_frame_init(&frame, RTS_COMMAND_UP, 123, 0xFACADE);

    uint8_t bytes[RTS_FRAME_BYTES];
    rts_frame_to_bytes(&frame, bytes, false);

    uint8_t expected[] = {0xAB, 0x2F, 0x00, 0x7B, 0xDE, 0xCA, 0xFA};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, bytes, RTS_FRAME_BYTES);
}

void test_obfuscate_bytes()
{
    uint8_t bytes[] = {0xA3, 0x29, 0x1E, 0x63, 0xEE, 0x1F, 0x42};
    rts_frame_obfuscate_bytes(bytes);

    uint8_t expected[] = {0xA3, 0x8A, 0x94, 0xF7, 0x19, 0x06, 0x44};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, bytes, RTS_FRAME_BYTES);
}

void test_deobfuscate_bytes()
{
    uint8_t deobfuscated[RTS_FRAME_BYTES];
    uint8_t obfuscated[] = {0xA3, 0x8A, 0x94, 0xF7, 0x19, 0x06, 0x44};
    rts_frame_deobfuscate_bytes(deobfuscated, obfuscated);

    uint8_t expected[] = {0xA3, 0x29, 0x1E, 0x63, 0xEE, 0x1F, 0x42};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, deobfuscated, RTS_FRAME_BYTES);
}

void test_generate_checksum()
{
    uint8_t frame[] = {0xA3, 0x29, 0x1E, 0x63, 0xEE, 0x1F, 0x42};
    TEST_ASSERT_EQUAL_UINT8(0, rts_frame_generate_checksum(frame));
}

void test_rts_frame()
{
    Unity.TestFile = __FILE__;

    RUN_TEST(test_from_bytes);
    RUN_TEST(test_to_bytes);
    RUN_TEST(test_obfuscate_bytes);
    RUN_TEST(test_deobfuscate_bytes);
    RUN_TEST(test_generate_checksum);
}