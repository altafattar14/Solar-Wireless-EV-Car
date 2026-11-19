# ESP32 controller firmware

## Arduino IDE setup

1. Install the Espressif ESP32 board package using Arduino IDE Boards Manager.
2. Select an ESP32-WROOM-32 compatible board, commonly **ESP32 Dev Module**.
3. In Library Manager, install **Adafruit GFX Library** and **Adafruit SSD1306**.
4. Open `WirelessEVCar.ino`, select the correct COM port, and upload.
5. Open Serial Monitor at 115200 baud to view startup messages.

The sketch uses the Arduino ESP32 core 2.x/3.x LEDC API based on the installed core version. Bluetooth Classic support is required; it is not available on ESP32-S2/S3/C3 in the same way as the original ESP32-WROOM-32.

## Bluetooth commands

Pair the phone with **WirelessEVCar**. Use a Bluetooth Classic serial terminal app and send one character:

| Character | Action |
|---|---|
| `F` | Forward |
| `B` | Reverse |
| `L` | Turn left (tank steering) |
| `R` | Turn right (tank steering) |
| `S` | Stop |
| `+` | Increase PWM by 15 |
| `-` | Decrease PWM by 15 |

The firmware stops the motors when Bluetooth disconnects or after 3 seconds without a valid command. The PWM start value is 150/255; tune it only after measuring the DC supply and motor current.

## Before connecting motors

- Test Bluetooth and OLED first with the motor driver disconnected.
- Remove ENA/ENB jumpers on the L298N if using ESP32 PWM.
- Check the OLED I²C pull-ups; ESP32 GPIO must not be pulled up to 5 V.
- Use a stable regulated ESP32 supply and a separately rated motor supply from the vehicle receiver power stage. Join logic grounds as required by the driver interface.
- Do not connect raw rectifier output directly to ESP32, OLED, or L298N.
- Keep the ZVS transmitter disconnected until the previous wire-burn fault has been diagnosed.

This sketch does not read a voltage sensor. OLED text explicitly reports RX voltage as **not measured**.
