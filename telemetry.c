#include "telemetry.h"
#include "project_config.h"
static void be16(uint8_t*p,uint16_t v){p[0]=v>>8;p[1]=v;} static void be24(uint8_t*p,uint32_t v){p[0]=v>>16;p[1]=v>>8;p[2]=v;} static void be32(uint8_t*p,uint32_t v){p[0]=v>>24;p[1]=v>>16;p[2]=v>>8;p[3]=v;}
void telemetry_pack_environment(uint8_t d[8],float t,float h,float p,uint8_t c){int16_t ti=(int16_t)(t*100);uint16_t hi=(uint16_t)(h*100);uint32_t pi=(uint32_t)p;be16(d,(uint16_t)ti);be16(d+2,hi);be24(d+4,pi);d[7]=c;}
void telemetry_pack_analog(uint8_t d[8],uint16_t r,uint16_t mv,uint8_t s,uint8_t cs,uint8_t e,uint8_t c){be16(d,r);be16(d+2,mv);d[4]=s;d[5]=cs;d[6]=e;d[7]=c;}
void telemetry_pack_heartbeat(uint8_t d[8],uint32_t u,uint8_t s,uint8_t c){be32(d,u);d[4]=FW_VERSION_MAJOR;d[5]=FW_VERSION_MINOR;d[6]=s;d[7]=c;}
