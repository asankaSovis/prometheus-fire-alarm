# 🔥 Prometheus Fire Alarm System
![Device Poster](https://user-images.githubusercontent.com/46389631/170832781-fd202c3a-0dc3-4c76-857c-3c3a94a17366.png)

---

## Project Introduction

**Prometheus** is a next generation fire alarm system Designed to take fire safety to the next level. This fire alarm system is designed to detect, indicate and extinguish fire by using necessary precautions. The system consists of three main stages:
1. Fire sensing and extinguishing system
2. Control stage
3. Alarming and notification stage

There are four main sections and components for the proper functioning of the system. It will help to complete that all the stages that are mentioned above.
1. Fire sensors
2. Extinguishing valves
3. Control unit
4. Software system
5. structural design

*NOTE: You can use the [Emulator code](https://github.com/asankaSovis/prometheus-fire-alarm/tree/main/Emulator/sketch_feb24b) to emulate a real world device for [command panel](https://github.com/asankaSovis/prometheus-command-panel) testing purposes. In it, all input sensors are replaced by potentiometers.*

## Prometheus Fire Alarm System
**Prometheus Fire Alarm System** is a fire alarm system and an extinguishing system that allows real time monitoring via software. It can perform smart extinguishing on site while providing connectivity to multiple devices at the same time via the control panel.

> ![Final Assembly](https://user-images.githubusercontent.com/46389631/185868729-a241fe1a-46b8-485a-bd56-5d62223f4bfc.jpeg)
> The final assembled unit

## Components

### 1. Control Unit
This is the brain of the system. It consists of a microcontroller which will be controlling the whole system. This also interfaces between all other components. The microcontroller used is the Atmega 328p This has a good count of pins and is suitable for the task. It will be powerful enough to control the system.

**Specifications**
- CPU type - 8-bit AVR (Arduino Uno)
- Maximum CPU speed - 20 MHz
- Performance - 20 MIPS at 20 MHz
- Flash memory - 32 KB
- SRAM - 2 KB
- EEPROM - 1 KB
- Package pin count - 28 or 32
- Capacitive touch sensing channels - 16
- Maximum I/O pins - 23
- External interrupts – 2

### 2. Fire Sensors
This is the module that directly interact with the fire. This consists of two components as listed below.

**Specifications**
1. Smoke Sensor – Detect the existence of a fire.
    - Operating Voltage: 2.5V to 5.0V
    - Power consumption: 150mA
    - Detect/Measure: NH3, Nox, CO2, Alcohol, Benzene, Smoke
    - Typical operating Voltage: 5V
    - Digital Output: 0V to 5V (TTL Logic) @ 5V Vcc
    - Analog Output: 0-5V @ 5V Vcc

2. Temperature and Humidity Sensor – Detect the thermal changes in the surrounding
    - Operating Voltage: 3.5V to 5.5V
    - Operating current: 0.3mA (measuring) 60uA (standby)
    - Output: Serial data
    - Temperature Range: 0°C to 50°C
    - Humidity Range: 20% to 90%
    - Resolution: Temperature and Humidity both are 16-bit
    - Accuracy: ±1°C and ±1%

They will sense the following three from the environment.
1. Temperature – DHT11 sensor
2. Humidity – DHT11 sensor
3. Carbondioxide – MQ 135 sensor

DHT 11 is communicating with the microcontroller digitally while the MQ 135 senses analog.

### 3. Extinguisher
The extinguisher consists of three parts. It handles the extinguishing of the fire.

**Specifications**
1. 5V relay – Convers the 5V control signal to 12V so that the solenoid valve can operate
    - Supply voltage: 3.75V to 6V
    - Quiescent current: 2mA
    - Current when the relay is active: ~70mA
    - Relay maximum contact voltage: 250VAC or 30VDC
    - Relay maximum current: 10A

2. Solenoid Valve – Controls the water flow
    - Material: Metal + plastic
    - Voltage: DC 12V
    - Power: 15W
    - Current: 1.25A
    - Inlet and outlet thread diameter: G1/2
    - Pressure: 0.02 - 0.8Mpa
    - Max fluid temperature: 80°C
    - Operation mode: Normally Closed

3. Nozzle – Sprays the water onto the fire so that the extinguishing is effective

While the relay and valve were bought, the nozzle was custom fabricated to suit the needs.

### 4. Indicators
The indicators give out an indication to the people about the fire. We included two indicators, both visual and auditory for the best outcome.

**Specifications**
1. Visual – A red LED
    - The red LED will blink twice every second to indicate that the system is operating normally. If it stays continuously on, then there is a warning or extinguishing has started. Any other combination or no light at all means that the device is turned off or is not working properly.

2. Auditory – A 5V Buzzer
    - The buzzer stays off when the system is operating normal. It will beep once every second in case of a warning is issued. It will then continuously buzz in case of an extinguishing.

### 5. Communication Unit
This unit is responsible for communicating with the command panel. The communication unit comprises of the USB to TTL device. This device provides an interface between the PC and the microcontroller via a USB cable. Thus, data and command signals can be exchanged.

**Specifications**
- Voltage: 3.3V, 5V
- Chipset: FT232RL
- USB power has over current protection using 500MA self-restore fuse
- RXD/TXD transceiver communication indicator
- Pin definition: DTR, RXD, TXD, VCC, CTS, GND
- Pitch: 2.54mm
- Module size: 36mm x 17.5mm

> ![Components](https://user-images.githubusercontent.com/46389631/185901185-ccc0f130-7fa7-491f-b832-135f4ef87584.jpg)
> List of components

## Hardware Specifications
- 12V input
- Minimum 500mA
- Micro USB (If connecting to the Control Panel Software)

## Operational Specifications
- Device issues a warning
    * when carbondioxide goes above 1000PPM.
    * with humidity drops below 30%.
- warning and turn on the valve at 85°C.

*NOTE: These values are set on par with the international guidelines.*

> ![Design](https://user-images.githubusercontent.com/46389631/185869594-2c75dce2-67c4-4d6d-a136-386a9cc70195.png)
> 
> Design Architecture

## Limitations
- Transistor of power supply overheat with extended use making the readings unstable (Added a heat sink that extends the time)
- Accuracy of the Carbon dioxide sensor increase with time, thus it is not accurate at first
- The relays can have back EMFs that can damage the circuit

## Demonstration

> [![Prometheus Fire Alarm System - Demonstration](https://user-images.githubusercontent.com/46389631/192273259-fb92e6f6-b95d-4e68-a962-5505359a668c.png)](https://www.youtube.com/watch?v=StTqXEQ2l-Y "Prometheus Fire Alarm System - Demonstration")
> Demonstration video of the final product

*NOTE: You can find additional documents such as reports, schematics and gerber files in the [Additional Material](https://github.com/asankaSovis/prometheus-fire-alarm/tree/main/Additional%20Material) folder.*

`© 2022 Asanka Sovis`
