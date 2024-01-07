#include "M5CoreInk.h"
#include "esp_sleep.h"

M5CoreInk::M5CoreInk(/* args */) {
}

M5CoreInk::~M5CoreInk() {
}

int M5CoreInk::begin(bool InkEnable, bool wireEnable, bool SpeakerEnable) {
    pinMode(POWER_HOLD_PIN, OUTPUT);
    digitalWrite(POWER_HOLD_PIN, HIGH);  // Hold power
    gpio_hold_en((gpio_num_t)POWER_HOLD_PIN);

    pinMode(1, OUTPUT);

    pinMode(LED_EXT_PIN, OUTPUT);

    Serial.begin(115200);
    Serial.printf("initializing.....OK\n");

    if (wireEnable) {
        Wire.begin(32, 33, 100000UL);
    }

    if (SpeakerEnable) {
        Speaker.begin();
    }

    rtc.begin();
    rtc.disableIRQ();

    if (InkEnable) {
        M5Ink.begin();
        // if (!M5.M5Ink.isInit()) {
        //     Serial.printf("Ink initializ is faild\n");
        //     return -1;
        // }
    }

    return 0;
}

void M5CoreInk::update() {
    BtnUP.read();
    BtnDOWN.read();
    BtnMID.read();
    BtnEXT.read();
    BtnPWR.read();
    Speaker.update();
}

void M5CoreInk::shutdown() {
    M5Ink.deepSleep();
    delay(50);
    gpio_hold_dis((gpio_num_t)POWER_HOLD_PIN);
    esp_deep_sleep_start();
    digitalWrite(POWER_HOLD_PIN, LOW);
}
int M5CoreInk::shutdown(int seconds) {
    M5Ink.deepSleep();
    rtc.clearIRQ();
    rtc.SetAlarmIRQ(seconds);
    delay(10);
    esp_deep_sleep_start();

    return 0;
}
int M5CoreInk::shutdown(const RTC_TimeTypeDef &RTC_TimeStruct) {
    M5Ink.deepSleep();
    rtc.clearIRQ();
    rtc.SetAlarmIRQ(RTC_TimeStruct);
    delay(10);
    esp_deep_sleep_start();
    return 0;
}
int M5CoreInk::shutdown(const RTC_DateTypeDef &RTC_DateStruct,
                        const RTC_TimeTypeDef &RTC_TimeStruct) {
    M5Ink.deepSleep();
    rtc.clearIRQ();
    rtc.SetAlarmIRQ(RTC_DateStruct, RTC_TimeStruct);
    delay(10);
    esp_deep_sleep_start();
    return 0;
}

M5CoreInk M5;
