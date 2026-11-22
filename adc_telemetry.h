#pragma once
#include <stdint.h>
#include "esp_err.h"
esp_err_t adc_telemetry_init(void);
esp_err_t adc_telemetry_read(uint16_t *raw,uint16_t *input_mv);
