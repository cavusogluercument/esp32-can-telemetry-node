#include <string.h>
#include "can_bus.h"
#include "project_config.h"
#include "driver/twai.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
static const char *TAG="CAN";
static can_diag_t d;

esp_err_t can_bus_init(void){
 twai_general_config_t g=TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX_GPIO,CAN_RX_GPIO,TWAI_MODE_NORMAL);
 g.alerts_enabled=TWAI_ALERT_RX_DATA|TWAI_ALERT_TX_SUCCESS|TWAI_ALERT_TX_FAILED|TWAI_ALERT_BUS_ERROR|TWAI_ALERT_BUS_OFF|TWAI_ALERT_BUS_RECOVERED;
 g.tx_queue_len=10; g.rx_queue_len=20;
 twai_timing_config_t t=TWAI_TIMING_CONFIG_500KBITS();
 twai_filter_config_t f=TWAI_FILTER_CONFIG_ACCEPT_ALL();
 esp_err_t e=twai_driver_install(&g,&t,&f); if(e!=ESP_OK) return e;
 return twai_start();
}
esp_err_t can_bus_send(uint32_t id,const uint8_t *data,uint8_t len){
 if(len>8) return ESP_ERR_INVALID_ARG;
 twai_message_t m={0}; m.identifier=id; m.data_length_code=len; memcpy(m.data,data,len);
 esp_err_t e=twai_transmit(&m,pdMS_TO_TICKS(100));
 if(e==ESP_OK)d.tx_ok++; else d.tx_fail++;
 return e;
}
void can_bus_get_diag(can_diag_t *out){ if(out)*out=d; }
void can_rx_task(void *arg){
 twai_message_t m;
 for(;;){ if(twai_receive(&m,pdMS_TO_TICKS(250))==ESP_OK){ d.rx_ok++; ESP_LOGI(TAG,"RX id=0x%03lX dlc=%u",(unsigned long)m.identifier,m.data_length_code); } }
}
void can_alert_task(void *arg){
 uint32_t a;
 for(;;){
  if(twai_read_alerts(&a,pdMS_TO_TICKS(500))==ESP_OK){
   if(a&TWAI_ALERT_TX_FAILED)d.tx_fail++;
   if(a&TWAI_ALERT_BUS_ERROR)d.bus_error++;
   if(a&TWAI_ALERT_BUS_OFF){ d.bus_off++; ESP_LOGW(TAG,"BUS-OFF; initiating recovery"); if(twai_initiate_recovery()==ESP_OK)d.recovery++; }
   if(a&TWAI_ALERT_BUS_RECOVERED)ESP_LOGI(TAG,"Bus recovered");
  }
 }
}
