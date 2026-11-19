# Solar-Powered Wireless EV Car

A combined MATLAB/Simulink simulation and physical prototype for a **batteryless onboard electric vehicle** powered wirelessly from a solar ground station.

## 1. System architecture

### Ground station (solar-powered)

`Solar panel → MPPT charge controller → ground-station battery/DC bus → correctly rated DC supply → ZVS inverter → transmitter (TX) coil`

### Wireless power link

`TX coil → magnetic coupling across air gap → receiver (RX) coil`

### Vehicle (no onboard battery)

`RX coil → bridge rectifier → DC-link/filter → regulated and protected DC distribution`

The vehicle-side supply is intended to power the motor driver and motors, plus a separate regulated logic supply for the ESP32 and OLED. The receiver must handle motor starting and stall-current transients; a receiver that can run the ESP32 may still be unable to propel the car.

### Control and display

- ESP32-WROOM-32 controls two DC motors through an L298N.
- Android phone communicates with ESP32 over Bluetooth Classic.
- OLED is connected by I²C.
- Firmware commands: `F` forward, `B` reverse, `L` left, `R` right, `S` stop; `+` and `-` adjust speed.

**Important:** The firmware does not currently measure receiver voltage or current. Add a properly designed and calibrated sensing circuit before displaying real power data. Do not treat a software-generated value as a measurement.

## 2. Repository layout

```text
.
├── README.md
├── .gitignore
├── ESP32_CODE/WirelessEVCar/WirelessEVCar.ino
├── HARDWARE/
│   ├── system-architecture.md
│   ├── connections.md
│   ├── components-and-ratings.md
│   └── safety.md
├── MATLAB_SIMULATION/README.md
├── SIMULINK/README.md
├── CIRCUIT_DIAGRAMS/README.md
├── DOCUMENTATION/
│   ├── working-principle.md
│   └── test-plan.md
└── RESULTS/README.md
```

## 3. ESP32 pin map

| ESP32-WROOM-32 | Connection |
|---|---|
| GPIO 25 | L298N ENA (left motor PWM) |
| GPIO 26 | L298N IN1 |
| GPIO 27 | L298N IN2 |
| GPIO 32 | L298N ENB (right motor PWM) |
| GPIO 33 | L298N IN3 |
| GPIO 14 | L298N IN4 |
| GPIO 21 | OLED SDA |
| GPIO 22 | OLED SCL |
| 3V3 | OLED VDD, only if the module supports 3.3 V |
| GND | Common vehicle-side logic ground |

Remove ENA/ENB jumpers when using ESP32 PWM. Confirm the exact L298N board and motor ratings before connecting power.

## 4. Development sequence

1. Record the exact ratings and model numbers of the solar panel, MPPT, ground-station battery, ZVS board, coils, rectifier, capacitor, regulators, motors, and driver.
2. Test ESP32, Bluetooth, OLED, and motor direction at a safe, current-limited low voltage.
3. Verify the receiver power stage with a suitable electronic load before connecting the motors.
4. Add protected voltage/current sensing and calibration.
5. Build MATLAB models for PV generation, MPPT, transmitter, coupled coils, receiver, DC link, and motor load.
6. Create and validate the corresponding Simulink model.
7. Compare predicted results against recorded hardware data.

## 5. Safety — read before powering the system

**Keep the ZVS transmitter disconnected.** The prototype previously had wires burn during ZVS testing. Do not energise it until the cause is found and the supply rating, wiring, current limit, fuse, coil, cooling, insulation, and assembly have been checked.

- Do not connect the RX output directly to a battery or to the MPPT controller.
- Do not connect an unregulated RX output directly to the ESP32 or OLED.
- The vehicle is batteryless in this architecture; use a correctly designed regulated DC power path, not an assumed battery charger circuit.
- Check rectifier current/thermal rating, capacitor polarity and ripple-current rating, and regulator dissipation.
- The previously mentioned 4700 µF capacitor is rated 25 V; never exceed its voltage rating.
- The L298N previously became hot. Check actual motor current, including startup/stall current, and driver heating.
- Use a separate regulated logic supply for the ESP32, with a common reference ground between control and driver logic. Do not power the motors from the ESP32 3.3 V pin.

## 6. Project status

This starter commit contains architecture and safety documentation plus basic ESP32 control firmware. **It does not contain completed MATLAB or Simulink models, and it does not certify the wireless power hardware.** Those will be developed and tested as separate milestones.
