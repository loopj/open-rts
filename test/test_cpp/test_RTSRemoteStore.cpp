#include <unity.h>

#include "config.h"
#include "bindings/cpp/RTSRemoteStore.h"

#if OPENRTS_HAS_NVS
#include "bindings/cpp/espidf/RTSRemoteStore_NVS.h"
#elif OPENRTS_HAS_EEPROM
#include "bindings/cpp/arduino/RTSRemoteStore_EEPROM.h"
#elif OPENRTS_HAS_MMAP
#include "bindings/cpp/linux/RTSRemoteStore_MMap.h"
#else
#include "bindings/cpp/RTSRemoteStore_Memory.h"
#endif

RTSRemoteStore *store;

static void RTSRemoteStore_setUp()
{
#if OPENRTS_HAS_NVS
    store = new RTSRemoteStore_NVS();
#elif OPENRTS_HAS_EEPROM
#if defined(ESP_PLATFORM)
    EEPROM.begin(512);
#endif
    store = new RTSRemoteStore_EEPROM();
#elif OPENRTS_HAS_MMAP
    store = new RTSRemoteStore_MMap("remotes.dat");
#else
    store = new RTSRemoteStore_Memory();
#endif

    store->clear();
}

static void RTSRemoteStore_tearDown()
{
    delete store;
}

static void test_knownRemote()
{
    RTSRemoteStore_setUp();

    store->setCode(0xC0FFEE, 123);
    TEST_ASSERT_TRUE(store->knownRemote(0xC0FFEE));

    RTSRemoteStore_tearDown();
}

static void test_getCode()
{
    RTSRemoteStore_setUp();

    store->setCode(0xC0FFEE, 0x1234);
    TEST_ASSERT_EQUAL_HEX16(0x1234, store->getCode(0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(0x1234, store->getCode(0xC0FFEE));

    RTSRemoteStore_tearDown();
}

static void test_getCode_newRemote()
{
    RTSRemoteStore_setUp();

    TEST_ASSERT_EQUAL_HEX16(0x0000, store->getCode(0xC0FFEE));

    RTSRemoteStore_tearDown();
}

static void test_nextCode()
{
    RTSRemoteStore_setUp();

    store->setCode(0xC0FFEE, 0x1234);
    TEST_ASSERT_EQUAL_HEX16(0x1234, store->nextCode(0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(0x1235, store->nextCode(0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(0x1236, store->nextCode(0xC0FFEE));

    RTSRemoteStore_tearDown();
}

static void test_nextCode_newRemote()
{
    RTSRemoteStore_setUp();

    TEST_ASSERT_EQUAL_HEX16(0x0000, store->nextCode(0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(0x0001, store->nextCode(0xC0FFEE));
    TEST_ASSERT_EQUAL_HEX16(0x0002, store->nextCode(0xC0FFEE));

    RTSRemoteStore_tearDown();
}

static void test_forget()
{
    RTSRemoteStore_setUp();

    store->setCode(0xC0FFEE, 123);
    TEST_ASSERT_TRUE(store->knownRemote(0xC0FFEE));

    store->forget(0xC0FFEE);
    TEST_ASSERT_FALSE(store->knownRemote(0xC0FFEE));

    RTSRemoteStore_tearDown();
}

static void test_clear()
{
    RTSRemoteStore_setUp();

    store->setCode(0xC0FFEE, 123);
    TEST_ASSERT_TRUE(store->knownRemote(0xC0FFEE));

    store->setCode(0xFACADE, 123);
    TEST_ASSERT_TRUE(store->knownRemote(0xFACADE));

    store->clear();
    TEST_ASSERT_FALSE(store->knownRemote(0xC0FFEE));
    TEST_ASSERT_FALSE(store->knownRemote(0xFACADE));

    RTSRemoteStore_tearDown();
}

void test_RTSRemoteStore()
{
    Unity.TestFile = __FILE__;

    RUN_TEST(test_knownRemote);
    RUN_TEST(test_getCode);
    RUN_TEST(test_getCode_newRemote);
    RUN_TEST(test_nextCode);
    RUN_TEST(test_nextCode_newRemote);
    RUN_TEST(test_forget);
    RUN_TEST(test_clear);
}