# Simulink model — planned blocks

The intended top-level model is:

`PV Array → MPPT / DC Bus → ZVS Inverter → TX/RX Coupled-Coil Link → Rectifier / DC Link → DC-DC Rails → Motor + ESP32 Load`

Build and validate each subsystem separately. The selected Simulink/Simscape libraries and exact block choices depend on the installed MATLAB release and available toolboxes. Do not create empty `.slx` files and label them complete; commit models only after they open and simulate successfully.
