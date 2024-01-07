#include "Power.h"

static int32_t getBatteryAdcRaw(uint8_t adc_ch, uint8_t adc_unit) {
    static constexpr int BASE_VOLATAGE = 3600;

    static esp_adc_cal_characteristics_t* adc_chars = nullptr;
    if (adc_chars == nullptr)
    {
      if (adc_unit == 2) {
        adc2_config_channel_atten((adc2_channel_t)adc_ch, ADC_ATTEN_DB_11);
      } else {
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten((adc1_channel_t)adc_ch, ADC_ATTEN_DB_11);
      }
      adc_chars = (esp_adc_cal_characteristics_t*)calloc(1, sizeof(esp_adc_cal_characteristics_t));
      esp_adc_cal_characterize((adc_unit_t)adc_unit, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, BASE_VOLATAGE, adc_chars);
    }
    int raw;
    if (adc_unit == 2) {
      adc2_get_raw((adc2_channel_t)adc_ch, adc_bits_width_t::ADC_WIDTH_BIT_12, &raw);
    } else {
      raw = adc1_get_raw((adc1_channel_t)adc_ch);
    }
    return esp_adc_cal_raw_to_voltage(raw, adc_chars);
}

Power::Power() {
}

int16_t Power::getBatteryVoltage(void) {
    int32_t raw = getBatteryAdcRaw(_batAdcCh, _batAdcUnit);
    return raw * _adc_ratio;
}

int32_t Power::getBatteryLevel(void) {
  float mv = getBatteryVoltage();
  int32_t level = (mv - 3300) * 100 / (float)(4150 - 3350);

    return (level < 0) ? 0
         : (level >= 100) ? 100
         : level;
}
