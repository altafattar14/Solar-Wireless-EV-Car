# System architecture and power flow

## Ground station

1. Solar panel supplies the MPPT charge controller.
2. The MPPT controller manages charging of the ground-station battery (battery chemistry and settings must match the actual battery).
3. The ground-station DC source supplies the ZVS transmitter only through wiring, protection, and ratings that match the ZVS module.
4. The ZVS inverter drives the TX coil at its designed operating frequency and power.

## Wireless link

The TX and RX coils transfer energy by magnetic coupling. Coupling depends on coil geometry, separation, alignment, tuning, load, and operating frequency. Efficiency and safe operating limits must be measured; they must not be assumed.

## Vehicle receiver

1. RX coil output enters a suitable rectifier.
2. DC-link capacitance filters rectified output.
3. A properly selected regulator/converter creates the required motor and logic rails.
4. The motor rail supplies the L298N and motors; the logic rail supplies ESP32 and OLED.
5. Grounds must be referenced appropriately for the control interface, while power wiring is routed to minimise motor-noise coupling.

There is no onboard battery in the intended vehicle architecture. Do not add a battery-charging stage unless the project architecture is deliberately changed and a battery-specific charge-management design is provided.

## Required measurements before integration

- Ground-station battery voltage and current.
- ZVS input voltage/current and switching/coil temperature.
- TX/RX coil geometry, gap, alignment, and frequency.
- Rectified RX voltage/current under no-load and controlled load.
- Regulated rail voltage during motor startup and running.
- ESP32 3.3 V rail during Bluetooth transmission and motor switching.
- Motor current and L298N temperature.

Log measured values with instrument model, range, test condition, and date.
