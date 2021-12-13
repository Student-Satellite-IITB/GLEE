# GLEE
## Spectroscopy Payload
**Aim -** To validate the presence of minerals in the lunar regolith through gamma ray or x-ray spectroscopy.

**Tasks:**
- Designing a capable spectroscopy system
- Testing the precision of spectral lines
- Modelling known sources of radiation and their spectrum
- Data analysis and inference
### Circuit Design
![image](./Overall_Circuit.png)

The Circuit Consists of the following parts-
- Diode Sensor & Voltage Bias
- Charge Sensitive Preamplifier
- Pulse Shaper Circuit
- Baseline Restorer & Pole-Zero Cancellation
- Amplifier
- Multi-Channel Analyzer

### Diode Sensor
After going through the size andpower constraints, 2 photodiode detectors were finalized:
- UM 9441: https://www.microsemi.com/existing-parts/parts/82558#resources
- X1007: https://www.mouser.in/datasheet/2/313/FirstSensor_09202018_X100-7_SMD_501401-1483097.pdf


