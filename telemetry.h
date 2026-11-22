#pragma once
#include <stdint.h>
void telemetry_pack_environment(uint8_t d[8],float t,float h,float p,uint8_t counter);
void telemetry_pack_analog(uint8_t d[8],uint16_t raw,uint16_t mv,uint8_t sensor,uint8_t can,uint8_t errors,uint8_t counter);
void telemetry_pack_heartbeat(uint8_t d[8],uint32_t uptime,uint8_t state,uint8_t counter);
