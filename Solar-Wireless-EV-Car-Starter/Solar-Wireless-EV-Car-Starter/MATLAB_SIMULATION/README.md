# MATLAB simulation — planned model

This folder will contain executable MATLAB scripts for:

1. PV array model (irradiance and temperature inputs).
2. MPPT controller and ground-station battery/DC bus.
3. ZVS transmitter equivalent model (after actual topology and ratings are known).
4. Coupled TX/RX coil model using measured or datasheet inductance, resistance, mutual inductance/coupling coefficient, and frequency.
5. Receiver rectifier, DC-link capacitor, and DC-DC regulation.
6. Vehicle motor-load model, including startup transient.
7. End-to-end power and efficiency calculations.

No electrical ratings have been assumed in a working simulation yet. The model parameters must come from the actual components. Start with a parameter file and verify each subsystem independently before integrating them.
