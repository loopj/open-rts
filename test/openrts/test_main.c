#include <unity.h>

void test_rts_frame();
void test_rts_frame_builder();
void test_rts_receiver();
void test_rts_remote();
void test_rts_remote_store();

void setUp (void) {}
void tearDown (void) {}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    test_rts_frame();
    test_rts_frame_builder();
    test_rts_receiver();
    test_rts_remote();
    test_rts_remote_store();

    return UNITY_END();
}
