# Verification Plan
| ID | Verification | Acceptance criterion |
|---|---|---|
| SW-01 | host CAN decoder | supplied assertions pass |
| FW-01 | build | ESP-IDF build completes without errors |
| HW-01 | 3V3 rail | within regulator/design tolerance under load |
| HW-02 | BME280 | ID 0x60, plausible T/RH/P |
| HW-03 | ADC | error documented over at least 0, 3, 6, 9, 12 V input |
| CAN-01 | heartbeat | 0x110 every ~1 s |
| CAN-02 | telemetry | IDs 0x100 and 0x101 decode correctly |
| CAN-03 | diagnostics | 0x120 counters respond to traffic/faults |
| CAN-04 | termination | ~60 ohm CANH-CANL with two 120-ohm ends, power off |
| EMC-01 | layout review | short CAN stubs, ground reference, local decoupling, antenna keepout |
