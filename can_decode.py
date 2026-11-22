#!/usr/bin/env python3
import sys
def u16(b): return (b[0]<<8)|b[1]
def s16(b):
 v=u16(b); return v-65536 if v&0x8000 else v
def u24(b): return (b[0]<<16)|(b[1]<<8)|b[2]
def u32(b): return (b[0]<<24)|(b[1]<<16)|(b[2]<<8)|b[3]
def decode(i,d):
 if i==0x100:return {"temperature_C":s16(d[:2])/100,"humidity_pct":u16(d[2:4])/100,"pressure_Pa":u24(d[4:7]),"counter":d[7]}
 if i==0x101:return {"adc_raw":u16(d[:2]),"input_mV":u16(d[2:4]),"sensor_ok":d[4],"can_ok":d[5],"errors":d[6],"counter":d[7]}
 if i==0x110:return {"uptime_ms":u32(d[:4]),"fw":f"{d[4]}.{d[5]}","state":d[6],"counter":d[7]}
 if i==0x120:return {"tx_ok":u16(d[:2]),"tx_fail":u16(d[2:4]),"rx_ok":u16(d[4:6]),"bus_off":d[6],"counter":d[7]}
 return {"raw":d.hex()}
if __name__=='__main__':
 i=int(sys.argv[1],0); d=bytes.fromhex(sys.argv[2]); print(decode(i,d))
