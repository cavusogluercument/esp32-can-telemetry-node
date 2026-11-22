EESchema Schematic File Version 4
LIBS:power
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
Sheet 1 1
Title "ESP32 CAN Telemetry & Sensor Node Rev A"
Comment1 "Portfolio reference design - verify ERC/footprints before fabrication"
$EndDescr
Text Notes 900 900 0 100 ~ 20
POWER: 5V input -> 3V3 LDO -> ESP32 / BME280 / SN65HVD230
Text Notes 900 1300 0 80 ~ 12
U1 ESP32-WROOM-32E: GPIO5=CAN_TX, GPIO4=CAN_RX, GPIO21=SDA, GPIO22=SCL, GPIO34=ADC
Text Notes 900 1650 0 80 ~ 12
U2 SN65HVD230D: pin1 D<-GPIO5; pin4 R->GPIO4; pin3=3V3; pin2=GND; pin7=CANH; pin6=CANL; pin8 RS=GND
Text Notes 900 2000 0 80 ~ 12
U3 BME280: VDD/VDDIO=3V3; SDA/SCL with 4.7k pullups; local 100nF decoupling
Text Notes 900 2350 0 80 ~ 12
ADC: VIN -> 100k -> node -> 1k -> GPIO34; node -> 27k -> GND; GPIO34 -> 10nF -> GND
Text Notes 900 2700 0 80 ~ 12
CAN: CANH/CANL to J1; optional 120R termination via JP1; add ESD protection for field revision
Text Notes 900 3050 0 80 ~ 12
J3: programming/debug header; expose 3V3, GND, TX0, RX0, EN, IO0
Text Notes 900 3600 0 70 ~ 12
This legacy KiCad schematic is an editable design note source. Use the accompanying NETLIST.csv and PCB source as the connectivity authority for Rev A capture.
$EndSCHEMATC
