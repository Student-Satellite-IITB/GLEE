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

The X-rays and gamma rays coming from Sun, hit the lunar surface and are reflected by the lunar regolith. The photons from the reflected rays hit our sensor and produce a surge in the reverse current. The magnitude of this surge is used to estimate the composition of the lunar soil (regolith). We have decided to use photodiode sensors for the the task due to lower power consumption and small size as compared to other detectors

After going through the response rates of various diodes, the following 2 photodiode detectors were finalized:
- UM 9441: https://www.microsemi.com/existing-parts/parts/82558#resources
- X1007: https://www.mouser.in/datasheet/2/313/FirstSensor_09202018_X100-7_SMD_501401-1483097.pdf

While UM9441 is a radiation hardened diode, X1007 has prior spectroscopy usage. Both diodes need to have a reverse biased voltage of around 30 V in order to act as photodiode. 
The output voltage from the GLEE solar panel is expected to be 5 V, hence a boost convertor would be required to step up the voltage from 5 V to 30 V.

Selected Boost Convertor: TPS6104x-Q1  (https://www.ti.com/document-viewer/TPS61041-Q1/datasheet).
This boost convertor can step up voltage from 5 V to 28 V with an efficiency of 85 %
