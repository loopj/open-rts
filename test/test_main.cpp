#if defined(ARDUINO)
#include <Arduino.h>
#endif

#include <unity.h>

// Stub out SPI for native tests (for now)
#if defined(__unix__)
#include "hal/spi.h"
void hal_spi_init(struct spi_module_t *spi) {}
void hal_spi_transfer(struct spi_module_t *spi, uint8_t *tx_buffer, uint8_t *rx_buffer, uint8_t length) {}
#endif

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
#elif defined(ESP_PLATFORM)
extern "C" {
    void app_main() {
        run_tests();
    }
}
#else

int main() {
    run_tests();

    return 0;
}
#endif