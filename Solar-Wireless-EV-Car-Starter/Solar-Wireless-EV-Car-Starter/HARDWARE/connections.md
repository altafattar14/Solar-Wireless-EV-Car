# Initial low-voltage connections

## ESP32-WROOM-32 to L298N

| ESP32 pin | L298N pin | Function |
|---|---|---|
| GPIO25 | ENA | Left motor speed PWM |
| GPIO26 | IN1 | Left motor direction input 1 |
| GPIO27 | IN2 | Left motor direction input 2 |
| GPIO32 | ENB | Right motor speed PWM |
| GPIO33 | IN3 | Right motor direction input 1 |
| GPIO14 | IN4 | Right motor direction input 2 |
| GND | GND | Shared logic reference |

Remove the ENA and ENB jumpers if PWM is driven from GPIO25 and GPIO32. Motor 1 connects to OUT1/OUT2 and motor 2 to OUT3/OUT4. If a motor runs in the opposite direction from the command, power down and swap that motor's output leads or invert its direction logic in firmware.

## ESP32 to I²C OLED

| ESP32 | OLED |
|---|---|
| 3V3 | VDD (only if module supports 3.3 V) |
| GND | GND |
| GPIO21 | SDA |
| GPIO22 | SCK/SCL |

Confirm the OLED module's supply and I²C pull-up voltage. Do not allow 5 V pull-ups onto ESP32 GPIO pins. Use a suitable bidirectional I²C level shifter if the module pulls SDA/SCL to 5 V.

## Power notes

- Do not power the motors from the ESP32 3.3 V pin or from the USB supply.
- The receiver-side motor supply must be regulated and sized for the motor driver's input range and motor startup/stall current.
- Use a separate stable regulator for the ESP32 logic rail. Keep the power return layout controlled and connect the driver logic ground to ESP32 ground.
- L298N modules differ in their onboard 5 V regulator/jumper arrangement. Follow the exact board documentation; do not connect an external 5 V logic supply while the onboard regulator is also driving that rail.
- Do not connect the ZVS transmitter during these low-voltage control tests.
