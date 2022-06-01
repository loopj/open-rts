#if defined(OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY)
// SparkFun LoRa Gateway (w/RFM69 module)
#define RADIO_TYPE_RFM69
#define RADIO_MISO 12
#define RADIO_MOSI 13
#define RADIO_CS   16
#define RADIO_SCK  14
#define RADIO_RST  27
#define RADIO_DATA 32
#elif defined(OPENRTS_BOARD_TTGO_LORA32_V21)
// LILYGO TTGO LoRa32 (V2.1)
#define RADIO_TYPE_SX1278
#define RADIO_MISO 19
#define RADIO_MOSI 27
#define RADIO_CS   18
#define RADIO_SCK  5
#define RADIO_RST  23
#define RADIO_DATA 32
#elif defined(OPENRTS_BOARD_HELTEC_WIFI_LORA_32_V2)
// Heltec WiFi LoRa 32 (V2)
#define RADIO_TYPE_SX1278
#define RADIO_MISO 19
#define RADIO_MOSI 27
#define RADIO_CS   18
#define RADIO_SCK  5
#define RADIO_RST  14
#define RADIO_DATA 34
#endif