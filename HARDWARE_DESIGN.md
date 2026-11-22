# Hardware Design Notes
## CAN
SN65HVD230D is powered from 3.3 V. D/TXD is driven by ESP32 GPIO5; R/RXD returns to GPIO4. RS is tied low for high-speed mode in Rev A. CANH/CANL go directly to the bus connector; selectable 120-ohm termination is provided for an end node.

## BME280
I2C address is configured as 0x76 in firmware. External 4.7k pull-ups are used. Firmware reads factory calibration coefficients and applies compensation before publishing values.

## ADC
100k/27k divider scales a nominal 0-12 V input. A 1k series resistor and 10 nF capacitor provide a simple input RC. This is a prototype measurement input, not an automotive transient-rated front end.

## Power
5 V input is regulated to 3.3 V. The selected regulator must be checked for ESP32 peak current and thermal performance before fabrication.

## Field-hardening backlog
TVS/ESD at CAN and external inputs, reverse-polarity/input surge protection, common-mode choke footprint, improved ADC protection, and EMC pre-compliance testing.
