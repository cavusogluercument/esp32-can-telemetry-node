# ESP32 CAN Bus Telemetry & Sensor Node — Portfolio Final

An embedded hardware/firmware portfolio project built around ESP32-WROOM-32E, SN65HVD230 CAN transceiver and BME280 environmental sensor.

## What this repository demonstrates
- ESP32 / C / ESP-IDF / FreeRTOS
- Classical CAN (TWAI), TX/RX diagnostics and bus recovery
- I2C sensor integration with BME280 calibration/compensation
- ESP32 ADC one-shot acquisition and calibrated voltage telemetry
- UART logging and diagnostic counters
- Editable KiCad schematic source and PCB source (Rev A reference layout)
- BOM, bring-up procedure, verification plan and host-side CAN decoder
- Honest test reporting: software-generated self-test evidence is separated from physical bench measurements

## Interfaces
| Function | ESP32 pin |
|---|---:|
| CAN TX | GPIO5 |
| CAN RX | GPIO4 |
| I2C SDA | GPIO21 |
| I2C SCL | GPIO22 |
| ADC | GPIO34 / ADC1_CH6 |
| Status LED | GPIO2 |
| UART0 | default programming/debug port |

## CAN protocol
| ID | Payload |
|---|---|
| `0x100` | temperature, humidity, pressure, counter |
| `0x101` | ADC raw, input mV, status/error flags, counter |
| `0x110` | uptime, firmware version, system state, counter |
| `0x120` | RX/TX diagnostic counters |

Default bitrate: **500 kbit/s**, Classical CAN, standard 11-bit identifiers.

## Firmware build
Requires ESP-IDF 5.x with the legacy `driver/twai.h` interface enabled.

```bash
cd firmware
idf.py set-target esp32
idf.py build
idf.py flash monitor
```

## Hardware files
`hardware/kicad/` contains an editable KiCad schematic and a Rev-A PCB source/reference layout. Before fabrication, open in KiCad, run ERC/DRC, confirm footprints against the exact parts you will purchase, and complete routing/placement review.

## Validation status
The firmware and host-side protocol tests are supplied as reproducible project artifacts. **No fabricated PCB or oscilloscope measurements are claimed.** Physical measurements belong in `results/PHYSICAL_TEST_RESULTS.md` after a board is assembled.

## License
MIT.
