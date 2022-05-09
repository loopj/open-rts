#if defined(ARDUINO)
#include <Arduino.h>
#endif

#include <unity.h>

extern "C" {
    void test_rts_frame();
    void test_rts_frame_builder();
    void test_rts_receiver();
    void test_rts_remote();
    void test_rts_remote_store();
}

void run_tests() {
    UNITY_BEGIN();

    test_rts_frame();
    test_rts_frame_builder();
    test_rts_receiver();
    test_rts_remote();
    test_rts_remote_store();

    UNITY_END();
}

#if defined(ARDUINO)
void setup() {
    delay(2000);
    run_tests();
}

void loop() {

}
#else
int main() {
    run_tests();

    return 0;
}
#endif