# Working principle

The solar panel harvests energy at the stationary ground unit. The MPPT controller manages the ground-station battery/DC bus. A suitably rated supply drives the ZVS inverter, which excites the transmitter coil. Magnetic coupling transfers a portion of that energy to the receiver coil mounted on the vehicle.

The vehicle-side receiver rectifies the induced AC and filters it to a DC link. DC-DC conversion then provides the motor-driver and logic rails. The ESP32 receives movement commands over Bluetooth Classic and drives the two motors through the L298N. An I²C OLED displays controller and Bluetooth status.

Because the vehicle has no onboard battery in this design, motor power must be continuously available from the wireless receiver. Misalignment, excess air gap, low coupling, or motor startup current can cause the receiver voltage to collapse. The receiver power capability must be measured under realistic load before attempting vehicle movement.
