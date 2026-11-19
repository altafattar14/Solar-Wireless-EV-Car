# Staged test plan

## A. Inspection and documentation

- Record exact module model numbers and ratings.
- Check polarity, wire gauge, solder joints, connector condition, and insulation.
- Keep the ZVS stage disconnected during all early tests.

## B. Controller-only test

- Power ESP32 from a stable regulated logic supply over USB or a suitable bench supply.
- Verify OLED address and display.
- Pair phone with `WirelessEVCar` and test each command with motors disconnected.
- Confirm unknown input is ignored and disconnect/timeout stops the outputs.

## C. Motor-driver test

- Lift the wheels clear of the bench.
- Use a current-limited supply matched to motor and L298N ratings.
- Verify each motor direction at low duty, then increase gradually while monitoring current and temperature.
- Test ESP32 stability while motors start and stop.

## D. Receiver power-stage test

- Test rectifier and DC-DC converters with suitable loads before connecting ESP32 or motors.
- Record voltage/current ripple and temperatures.
- Confirm rail stability through load steps comparable to motor startup.

## E. Wireless power test

Only after the prior sections pass and the previous ZVS wiring failure is understood, perform a controlled low-power test with appropriate isolation, current limiting, fusing, temperature monitoring, and qualified review.

## F. Integrated vehicle test

Begin with wheels raised, then a restrained low-speed floor test. Record TX input power, RX output power, regulated rails, motor current, speed, coil alignment/gap, and temperatures.
