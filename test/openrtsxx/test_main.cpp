#include <unity.h>

void test_RTSFrame();
void test_RTSFrameBuilder();
void test_RTSRemote();
void test_RTSRemoteStore();

void setUp (void) {}
void tearDown (void) {}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    test_RTSFrame();
    test_RTSFrameBuilder();
    test_RTSRemote();
    test_RTSRemoteStore();

    return UNITY_END();
}