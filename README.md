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

The X-rays and gamma rays coming from Sun, hit the lunar surface and are reflected by the lunar regolith. The photons from the reflected rays hit our sensor and produce a surge in the reverse current. The magnitude of this surge is used to estimate the composition of the lunar soil. We have decided to use photodiode sensors for the the task due to lower power consumption and small size as compared to other detectors. 

After going through the response rates of various diodes, the following 2 photodiode detectors were finalized:
- UM 9441: https://www.microsemi.com/existing-parts/parts/82558#resources
- X1007: https://www.mouser.in/datasheet/2/313/FirstSensor_09202018_X100-7_SMD_501401-1483097.pdf

While UM9441 is a radiation hardened diode, X1007 has prior spectroscopy usage. Both diodes need to have a reverse biased voltage of around 30 V in order to act as photodiode. 
The output voltage from the GLEE solar panel is expected to be 5 V, hence a boost convertor would be required to step up the voltage from 5 V to 30 V.

Selected Boost Convertor: **TPS6104x-Q1**  (https://www.ti.com/document-viewer/TPS61041-Q1/datasheet).
This boost convertor can step up voltage from 5 V to 28 V with an efficiency of 85 %, which was highest among the converters seen.

### Charge Sensitive Preamplifier

The next component in our system is the charge sensitive preamplifier, its task is to convert the current signal coming from the photodiode to a voltage signal which is easier to process and amplify. The output current from the photodiode is a **pulse train of dirac-delta signals** with each pulse representig an individual photon hitting the photodiode sensor. This current signal acts as the input signal for the CSP. The output of the CSP depends on the charge accumulated on it due to the photocurrent. The CSP can be thought as an integrator having current input and charge based voltage output.

The preamplifier basically consists of an Opamp, a pair of capacitors and a discharging mechanism. The CSP needs to regularly discharged in order to prevent it from getting saturated and/or saturating the final diode. We are using a resistance feedback CSP which uses the feedback resistance of the opamp to continously discharge the capacitor. The output voltage of this CSP is a **pulse train of exponential signals**. The height of each signal is directly propotional to the energy of the incident photons and time constant for this exponential signal is as per the values of feedback resistance and capacitance. The values of our feedback components are based on the count rate of the radiation. 

Count rate of a radiation for any sensor refers to the number of photons belonging to the energy range of that radiation that are hitting the sensor in a second.
- Count rate of X-rays =
- Count rate of Gamma rays =
The time constant for the CSP has to be lesser than the one-fifth of the maximum count rate possible. for the CSP designed by us-
- Feedback Resistance (R) =
- Feedback Capacitance (C) =
- Time Constant (RC) =

Another possible alternative to this RF CSP would have been the transistor reset pre-amplifier, but it was rejected due to excessively complicated circuitry, higher power & size as compared to RF CSP and no significant benefits other than slight reduced noise.

