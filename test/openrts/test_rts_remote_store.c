#include <unity.h>

#include <openrts/config.h>
#include <openrts/rts_remote_store.h>

#if OPENRTS_HAS_NVS
#include <openrts/espidf/rts_remote_store_nvs.h>
#elif OPENRTS_HAS_MMAP
#include <openrts/linux/rts_remote_store_mmap.h>
#else
#include <openrts/rts_remote_store_memory.h>
#endif

struct rts_remote_store remote_store;

static void remote_store_setUp()
{
#if OPENRTS_HAS_NVS
    rts_remote_store_init_nvs(&remote_store);
#elif OPENRTS_HAS_MMAP
    rts_remote_store_init_mmap(&remote_store, "remotes.dat");
#else
    rts_remote_store_init_memory(&remote_store);
#endif

    rts_remote_store_clear(&remote_store);
}

static void remote_store_tearDown()
{
    rts_remote_store_close(&remote_store);
}

static void test_known_remote()
{
    remote_store_setUp();

    rts_remote_store_set_code(&remote_store, 0xC0FFEE, 123);
    TEST_ASSERT_TRUE(rts_remote_store_known_remote(&remote_store, 0xC0FFEE));

    remote_store_tearDown();
}

static void test_get_code()
{
    remote_store_setUp();

    rts_remote_store_set_code(&remote_store, 0xC0FFEE, 0x1234);
    TEST_ASSERT_EQUAL_HEX16(0x1234,
                            rts_remote_store_get_code(&remote_store, 0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(0x1234,
                            rts_remote_store_get_code(&remote_store, 0xC0FFEE));

    remote_store_tearDown();
}

static void test_get_code_new_remote()
{
    remote_store_setUp();

    TEST_ASSERT_EQUAL_HEX16(0x0000,
                            rts_remote_store_get_code(&remote_store, 0xC0FFEE));

    remote_store_tearDown();
}

static void test_next_code()
{
    remote_store_setUp();

    rts_remote_store_set_code(&remote_store, 0xC0FFEE, 0x1234);
    TEST_ASSERT_EQUAL_HEX16(
        0x1234, rts_remote_store_next_code(&remote_store, 0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(
        0x1235, rts_remote_store_next_code(&remote_store, 0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(
        0x1236, rts_remote_store_next_code(&remote_store, 0xC0FFEE));

    remote_store_tearDown();
}

static void test_next_code_new_remote()
{
    remote_store_setUp();

    TEST_ASSERT_EQUAL_HEX16(
        0x0000, rts_remote_store_next_code(&remote_store, 0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(
        0x0001, rts_remote_store_next_code(&remote_store, 0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(
        0x0002, rts_remote_store_next_code(&remote_store, 0xC0FFEE));

    remote_store_tearDown();
}

static void test_forget()
{
    remote_store_setUp();

    rts_remote_store_set_code(&remote_store, 0xC0FFEE, 123);
    TEST_ASSERT_TRUE(rts_remote_store_known_remote(&remote_store, 0xC0FFEE));

    rts_remote_store_forget(&remote_store, 0xC0FFEE);
    TEST_ASSERT_FALSE(rts_remote_store_known_remote(&remote_store, 0xC0FFEE));

    remote_store_tearDown();
}

static void test_clear()
{
    remote_store_setUp();

    rts_remote_store_set_code(&remote_store, 0xC0FFEE, 123);
    TEST_ASSERT_TRUE(rts_remote_store_known_remote(&remote_store, 0xC0FFEE));

    rts_remote_store_set_code(&remote_store, 0xFACADE, 123);
    TEST_ASSERT_TRUE(rts_remote_store_known_remote(&remote_store, 0xFACADE));

    rts_remote_store_clear(&remote_store);
    TEST_ASSERT_FALSE(rts_remote_store_known_remote(&remote_store, 0xC0FFEE));
    TEST_ASSERT_FALSE(rts_remote_store_known_remote(&remote_store, 0xFACADE));

    remote_store_tearDown();
}

// TODO: Test multiple remotes

void test_rts_remote_store()
{
    Unity.TestFile = __FILE__;

    RUN_TEST(test_known_remote);
    RUN_TEST(test_get_code);
    RUN_TEST(test_get_code_new_remote);
    RUN_TEST(test_next_code);
    RUN_TEST(test_next_code_new_remote);
    RUN_TEST(test_forget);
    RUN_TEST(test_clear);
}