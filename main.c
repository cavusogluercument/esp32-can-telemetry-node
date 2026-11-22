#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "can_bus.h"
#include "bme280.h"
#include "adc_telemetry.h"
#include "telemetry.h"
#include "project_config.h"
static const char*TAG="APP";
void app_main(void){
 ESP_LOGI(TAG,"ESP32 CAN Telemetry Node FW %d.%d",FW_VERSION_MAJOR,FW_VERSION_MINOR);
 ESP_ERROR_CHECK(can_bus_init()); xTaskCreate(can_rx_task,"can_rx",3072,NULL,8,NULL); xTaskCreate(can_alert_task,"can_alert",3072,NULL,9,NULL);
 esp_err_t se=bme280_init(); ESP_ERROR_CHECK(adc_telemetry_init()); uint8_t c=0;
 for(;;){
  uint8_t d[8]; bme280_sample_t s={0}; uint16_t raw=0,mv=0; uint8_t err=0;
  if(se==ESP_OK && bme280_read(&s)==ESP_OK){ telemetry_pack_environment(d,s.temperature_c,s.humidity_pct,s.pressure_pa,c); can_bus_send(0x100,d,8); } else err|=1;
  if(adc_telemetry_read(&raw,&mv)==ESP_OK){ telemetry_pack_analog(d,raw,mv,se==ESP_OK,1,err,c); can_bus_send(0x101,d,8); } else err|=2;
  telemetry_pack_heartbeat(d,(uint32_t)(esp_timer_get_time()/1000),err?1:0,c); can_bus_send(0x110,d,8);
  can_diag_t dg; can_bus_get_diag(&dg); d[0]=dg.tx_ok>>8;d[1]=dg.tx_ok;d[2]=dg.tx_fail>>8;d[3]=dg.tx_fail;d[4]=dg.rx_ok>>8;d[5]=dg.rx_ok;d[6]=dg.bus_off;d[7]=c;can_bus_send(0x120,d,8);
  ESP_LOGI(TAG,"T=%.2fC H=%.2f%% P=%.0fPa ADC=%u Vin=%umV",s.temperature_c,s.humidity_pct,s.pressure_pa,raw,mv);
  c++; vTaskDelay(pdMS_TO_TICKS(TELEMETRY_PERIOD_MS));
 }
}
