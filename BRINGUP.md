# Bring-up Procedure
1. Inspect assembly and polarity.
2. With power off, check 3V3-GND for a hard short.
3. Apply current-limited 5 V.
4. Verify 3.3 V rail and regulator temperature.
5. Confirm ESP32 boot/UART log.
6. Confirm BME280 chip ID 0x60 and sensible measurements.
7. Apply known ADC input voltages and compare reported value against a DMM.
8. Connect CAN to a second node/analyzer on a properly terminated bus.
9. Verify 0x100/101/110/120 at 500 kbit/s.
10. Force a CAN fault/disconnection and observe diagnostics/recovery.
11. Record actual instrument screenshots and measurements in `results/PHYSICAL_TEST_RESULTS.md`.
