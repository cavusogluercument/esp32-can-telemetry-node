# CAN Protocol v1.0
Classical CAN, 500 kbit/s, 11-bit identifiers, big-endian multi-byte fields.

- 0x100 ENV: int16 temperature x100; uint16 RH x100; uint24 pressure Pa; uint8 counter.
- 0x101 ADC: uint16 raw; uint16 calculated input mV; sensor status; CAN status; error flags; counter.
- 0x110 HEARTBEAT: uint32 uptime ms; FW major; FW minor; state; counter.
- 0x120 DIAG: uint16 TX OK; uint16 TX fail; uint16 RX OK; uint8 bus-off count; counter.
