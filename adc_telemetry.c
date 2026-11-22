#include "adc_telemetry.h"
#include "project_config.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
static adc_oneshot_unit_handle_t u; static adc_cali_handle_t cal; static int calibrated;
esp_err_t adc_telemetry_init(void){
 adc_oneshot_unit_init_cfg_t uc={.unit_id=ADC_UNIT_1}; ESP_ERROR_CHECK(adc_oneshot_new_unit(&uc,&u));
 adc_oneshot_chan_cfg_t cc={.atten=ADC_ATTEN_DB_11,.bitwidth=ADC_BITWIDTH_DEFAULT}; ESP_ERROR_CHECK(adc_oneshot_config_channel(u,ADC_CHANNEL_6,&cc));
 adc_cali_line_fitting_config_t lc={.unit_id=ADC_UNIT_1,.atten=ADC_ATTEN_DB_11,.bitwidth=ADC_BITWIDTH_DEFAULT}; calibrated=(adc_cali_create_scheme_line_fitting(&lc,&cal)==ESP_OK); return ESP_OK;
}
esp_err_t adc_telemetry_read(uint16_t*raw,uint16_t*input_mv){
 if(!raw||!input_mv)return ESP_ERR_INVALID_ARG; int r,mv; ESP_ERROR_CHECK(adc_oneshot_read(u,ADC_CHANNEL_6,&r));
 if(calibrated)ESP_ERROR_CHECK(adc_cali_raw_to_voltage(cal,r,&mv)); else mv=(r*3300)/4095;
 float vin=mv*(ADC_DIVIDER_R_TOP_OHM+ADC_DIVIDER_R_BOTTOM_OHM)/ADC_DIVIDER_R_BOTTOM_OHM; *raw=(uint16_t)r; *input_mv=(uint16_t)(vin+0.5f); return ESP_OK;
}
