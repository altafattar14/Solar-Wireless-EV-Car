# Component register — fill in before power integration

Do not infer ratings from appearance. Record the actual label, datasheet, or measured value for each part.

| Component | Current project detail | Required information to record |
|---|---|---|
| Solar panel | Ground station | Vmp, Voc, Imp, Isc, rated power |
| MPPT controller | Ground station | Supported battery chemistry, PV input limits, charge current, output voltage |
| Ground-station battery | Ground station only | Chemistry, nominal/max voltage, capacity, max continuous/discharge current, BMS details if applicable |
| ZVS inverter | TX stage | Input range, maximum input current/power, frequency, cooling requirements |
| TX coil | Transmitter | Inductance, resistance, dimensions, conductor, thermal limit |
| RX coil | Vehicle | Inductance, resistance, dimensions, conductor, thermal limit |
| Bridge rectifier | Receiver | Repetitive reverse voltage, average/peak current, forward drop, thermal conditions |
| Filter capacitor | Receiver | Capacitance, voltage rating, ripple current, temperature rating, polarity |
| DC-DC converter(s) | Vehicle | Input range, output voltage/current, efficiency, thermal rating, protection |
| ESP32-WROOM-32 | Vehicle controller | Board variant and supply arrangement |
| L298N module | Motor driver | Board variant, motor supply range, current/thermal limits, regulator jumper details |
| DC motors (2) | Vehicle drive | Rated voltage, no-load current, stall current, rated speed |
| OLED | Vehicle display | Controller type, I²C address, supply voltage, pull-up voltage |

The receiver and regulator design cannot be finalised until the coil, rectifier, motor, and supply ratings are known.
