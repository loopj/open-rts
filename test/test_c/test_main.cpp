#if defined(ARDUINO)

#endif

#include <unity.h>

extern "C" {
    void test_rts_frame();
    void test_rts_frame_builder();
    void test_rts_receiver();
    void test_rts_remote();
    void test_rts_remote_store();
}

static void RUN_UNITY_TESTS() {
    UNITY_BEGIN();

    // C tests
    test_rts_frame();
    test_rts_frame_builder();
    test_rts_receiver();
    test_rts_remote();
    test_rts_remote_store();

    UNITY_END();
}

#if defined(ARDUINO)

#include <Arduino.h>

void setup() {
    delay(2000);
    RUN_UNITY_TESTS();
}

void loop() {

}

#elif defined(ESP_PLATFORM)

extern "C" void app_main() {
	RUN_UNITY_TESTS();
}

#else

int main(int argc, char **argv) {
    RUN_UNITY_TESTS();
    return 0;
}

#endif