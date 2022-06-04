#include <unity.h>

void test_RTSFrame();
void test_RTSFrameBuilder();
void test_RTSRemote();
void test_RTSRemoteStore();

static void RUN_UNITY_TESTS() {
    UNITY_BEGIN();

    test_RTSFrame();
    test_RTSFrameBuilder();
    test_RTSRemote();
    test_RTSRemoteStore();

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