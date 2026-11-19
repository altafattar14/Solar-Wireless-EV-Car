# Hardware safety checklist

## ZVS transmitter — currently a no-power zone

The prototype previously had wires burn during ZVS testing. Keep the ZVS supply disconnected. First identify the exact failure location and cause. Inspect wire gauge, polarity, solder joints, coil short circuits, supply capability, switching device condition, tuning components, and cooling. A qualified person should review the high-current/high-frequency stage before energising it.

## Receiver and DC link

- Confirm rectifier polarity and current/thermal rating.
- Confirm capacitor polarity, voltage rating, ripple-current rating, and discharge method.
- The mentioned 4700 µF / 25 V capacitor must never see more than its 25 V rating; provide appropriate margin and verify its suitability for ripple current.
- Verify converter input limits at both no-load and loaded conditions.
- Do not feed raw rectifier output directly to ESP32, OLED, or motors.

## Motors and driver

- Check motor rated voltage and stall current.
- The L298N previously became hot; measure current and temperature, and stop testing if it overheats.
- Ensure driver cooling and supply wiring are adequate.
- Test with wheels lifted and a current-limited bench supply before floor testing.

## Logic and EMI

- Power ESP32 from a stable regulated logic supply.
- Verify no I²C or other ESP32 input is pulled up to 5 V.
- Keep motor leads away from antenna, I²C, and receiver signal wiring where practical.
- Use suitable fusing, strain relief, insulated terminals, and emergency power isolation.
