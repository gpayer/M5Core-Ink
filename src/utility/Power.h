#pragma once

#include <Arduino.h>
#include <esp_adc_cal.h>
#include <soc/adc_channel.h>
#include "hal/gpio_types.h"

class Power {
  public:
    Power();

    int32_t getBatteryLevel(void);
    int16_t getBatteryVoltage(void);

  private:
    float _adc_ratio = 25.1f / 5.1f;
    uint8_t _wakeupPin = GPIO_NUM_27;
    uint8_t _rtcIntPin = GPIO_NUM_19;
    // pmic_t _pmic = pmic_t::pmic_unknown;
    uint8_t _batAdcCh = ADC1_GPIO35_CHANNEL;
    uint8_t _batAdcUnit = 1;
};
