# Circuit diagrams — Solar Wireless EV Car

This folder contains three starter diagrams:

1. `01_system_power_flow_overview.png/.svg` — ground station, wireless transfer, and batteryless vehicle power flow.
2. `02_receiver_power_stage_concept.png/.svg` — receiver coil, KBPC2510 bridge, DC link, and separate motor/logic DC-DC rails.
3. `03_esp32_l298n_oled_low_voltage_wiring.png/.svg` — confirmed ESP32 pin mapping to L298N and I2C OLED.

## Important limitations

These are conceptual/connection diagrams, not a construction-ready high-frequency power schematic. The ZVS module's exact circuit, TX/RX coil tuning network, wiring gauge, fuses, capacitor selection, and DC-DC ratings are not specified because the exact module, coil, supply, and motor specifications have not yet been provided. The prototype previously had wires burn during ZVS testing; keep the ZVS stage disconnected until the fault is diagnosed and the stage is checked by a qualified person.

The vehicle has no onboard battery. The RX output must be rectified, filtered, and regulated before it supplies the motor and logic rails. Raw rectifier DC must not be connected directly to the ESP32/OLED or motor driver.

## Confirmed low-voltage pin map

| ESP32-WROOM-32 | L298N |
|---|---|
| GPIO25 | ENA (left PWM) |
| GPIO26 | IN1 |
| GPIO27 | IN2 |
| GPIO32 | ENB (right PWM) |
| GPIO33 | IN3 |
| GPIO14 | IN4 |
| GND | GND (common logic reference) |

OLED: GPIO21 to SDA, GPIO22 to SCL/SCK, 3V3 to VDD only if supported, and GND to GND. Confirm I2C pull-up voltage; ESP32 pins must not be pulled up to 5 V.

For L298N power, motor outputs, module 5 V regulator jumper, and ESP32 board VIN/5V input, follow the labels/manual for the exact purchased boards. Do not connect two sources to the same 5 V rail. Remove ENA/ENB jumpers when PWM is driven from the ESP32.
