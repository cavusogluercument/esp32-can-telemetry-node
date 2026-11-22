#include <stdint.h>
#include "bme280.h"
#include "project_config.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define PORT I2C_NUM_0
static struct { uint16_t T1; int16_t T2,T3; uint16_t P1; int16_t P2,P3,P4,P5,P6,P7,P8,P9; uint8_t H1,H3; int16_t H2,H4,H5; int8_t H6; int32_t tfine; } c;
static esp_err_t rd(uint8_t reg,uint8_t *b,size_t n){ return i2c_master_write_read_device(PORT,BME280_ADDR,&reg,1,b,n,pdMS_TO_TICKS(100)); }
static esp_err_t wr(uint8_t reg,uint8_t v){ uint8_t b[2]={reg,v}; return i2c_master_write_to_device(PORT,BME280_ADDR,b,2,pdMS_TO_TICKS(100)); }
static uint16_t u16(const uint8_t*p){return (uint16_t)p[0]|((uint16_t)p[1]<<8);} static int16_t s16(const uint8_t*p){return (int16_t)u16(p);}
esp_err_t bme280_init(void){
 i2c_config_t ic={.mode=I2C_MODE_MASTER,.sda_io_num=I2C_SDA_GPIO,.scl_io_num=I2C_SCL_GPIO,.sda_pullup_en=GPIO_PULLUP_DISABLE,.scl_pullup_en=GPIO_PULLUP_DISABLE,.master.clk_speed=100000};
 ESP_ERROR_CHECK(i2c_param_config(PORT,&ic)); ESP_ERROR_CHECK(i2c_driver_install(PORT,ic.mode,0,0,0));
 uint8_t id; ESP_ERROR_CHECK(rd(0xD0,&id,1)); if(id!=0x60)return ESP_ERR_NOT_FOUND;
 uint8_t a[26],h[7]; ESP_ERROR_CHECK(rd(0x88,a,26)); ESP_ERROR_CHECK(rd(0xE1,h,7));
 c.T1=u16(a);c.T2=s16(a+2);c.T3=s16(a+4);c.P1=u16(a+6);c.P2=s16(a+8);c.P3=s16(a+10);c.P4=s16(a+12);c.P5=s16(a+14);c.P6=s16(a+16);c.P7=s16(a+18);c.P8=s16(a+20);c.P9=s16(a+22);c.H1=a[25];
 c.H2=s16(h);c.H3=h[2];c.H4=(int16_t)((h[3]<<4)|(h[4]&0x0F));c.H5=(int16_t)((h[5]<<4)|(h[4]>>4));c.H6=(int8_t)h[6];
 ESP_ERROR_CHECK(wr(0xF2,0x01)); ESP_ERROR_CHECK(wr(0xF4,0x27)); ESP_ERROR_CHECK(wr(0xF5,0xA0)); return ESP_OK;
}
esp_err_t bme280_read(bme280_sample_t*out){
 if(!out)return ESP_ERR_INVALID_ARG; uint8_t b[8]; ESP_ERROR_CHECK(rd(0xF7,b,8));
 int32_t ap=(b[0]<<12)|(b[1]<<4)|(b[2]>>4), at=(b[3]<<12)|(b[4]<<4)|(b[5]>>4), ah=(b[6]<<8)|b[7];
 int32_t v1=((((at>>3)-((int32_t)c.T1<<1)))*c.T2)>>11; int32_t v2=(((((at>>4)-(int32_t)c.T1)*((at>>4)-(int32_t)c.T1))>>12)*c.T3)>>14; c.tfine=v1+v2; out->temperature_c=((c.tfine*5+128)>>8)/100.0f;
 int64_t p1=(int64_t)c.tfine-128000, p2=p1*p1*c.P6; p2+=((p1*c.P5)<<17); p2+=((int64_t)c.P4<<35); p1=((p1*p1*c.P3)>>8)+((p1*c.P2)<<12); p1=((((int64_t)1<<47)+p1)*c.P1)>>33;
 if(p1==0)out->pressure_pa=0; else { int64_t p=1048576-ap; p=(((p<<31)-p2)*3125)/p1; p1=((int64_t)c.P9*(p>>13)*(p>>13))>>25; p2=((int64_t)c.P8*p)>>19; p=((p+p1+p2)>>8)+((int64_t)c.P7<<4); out->pressure_pa=p/256.0f; }
 int32_t h=c.tfine-76800; h=(((((ah<<14)-((int32_t)c.H4<<20)-((int32_t)c.H5*h))+16384)>>15)*(((((((h*c.H6)>>10)*(((h*c.H3)>>11)+32768))>>10)+2097152)*c.H2+8192)>>14)); h-=((((h>>15)*(h>>15))>>7)*c.H1)>>4; if(h<0)h=0; if(h>419430400)h=419430400; out->humidity_pct=(h>>12)/1024.0f;
 return ESP_OK;
}
