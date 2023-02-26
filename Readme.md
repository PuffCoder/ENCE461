# ENCE461

# Schematic Common

**To-Do List:**

- [ ]  Title block:  —— 1
    - [ ]  students names
    - [ ]  group number
- [ ]  Battery fusing.    —— 2
- [ ]  Use serial wire debug interface for programming.   —— 3
    - Why do we need it for debugging/programming?
    - Is the USB not enough?
    - How different with USB debug port?
- [ ]  *3.3V MCU regulator can be back driven?*   —— 4
    - What is a regulator?
    - Why is it not able to drive back?
- [ ]  Short circuit protection for MCU pio pins going to external headers.   —— 5
    1. Add a series resistor: Adding a series resistor between the MCU PIO pin and the external header limits the amount of current that can flow through the pin, thus preventing damage in case of a short circuit. The value of the resistor can be chosen based on the current requirements of the connected external components.
    2. Use a current-limiting IC: A current-limiting IC can be added between the MCU PIO pin and the external header to limit the current flowing through the pin in case of a short circuit. This protects the MCU and the connected components from damage.
    3. Add a polyfuse: A polyfuse is a type of self-resetting fuse that can be added between the MCU PIO pin and the external header to protect the MCU from short circuits. If the current flowing through the polyfuse exceeds a certain limit, it trips and disconnects the shorted circuit. Once the short is removed, the polyfuse resets itself.
    4. Use a crowbar circuit: A crowbar circuit is a protection circuit that shorts the power supply to ground in case of overvoltage or overcurrent. It can be used to protect the MCU and the connected components from damage due to short circuits.
    5. Add a voltage clamp: A voltage clamp can be added between the MCU PIO pin and the external header to limit the voltage level in case of a short circuit. This protects the MCU from voltage spikes that can damage it.
- [ ]  Battery voltage monitoring.   —— 6
- [ ]  Analog inputs ≤ 3.3 V    —— 7
- [ ]  LEDs for debug.   —— 8
    - [ ]  state
    - [ ]  
- [ ]  Jumpers for mode configuration   —— 9
    - [ ]  4 x channel
- [ ]  Pull—up Resistor on TWI(I2C)   —— 10
- [ ]  Test point — 11
    - [ ]  
- [ ]  Gound Test Point    —— 12
- [ ]  USB signals are not swapped   —— 13
- [ ]  USB has series termination resistors (27 Ohm)   —— 14
- [ ]  VBUS detection through voltage divider to PIO pin.    —— 15
    - [ ]  This is needed so that the MCU can tell when USB plugged / removed
    - [ ]  Diode/ Jumpers — USB 5V can connected to 5V from the switching regulator
- [ ]  Power supply filtering for radio   —— 16
    - [ ]  recommend ferrite bead
    - [ ]  resistor in series with power rail with parallel capacitor
- [ ]  The radio needs to be connected to SPI pin   —— 17
    - [ ]  MISO/PA12
    - [ ]  MOSI/PA13
    - [ ]  SCK/PA14
- [ ]  Radio IRQ connected to MCU PIO pin   —— 18
- [ ]  Radio uses SPI clock (SCK) not The TWI clock (TWCK)   —— 19
- [ ]  TWI uses TWCK0/PA4 a   —— 20
    - [ ]  TWD0/PA3
    - [ ]  TWCK1/PB5
    - [ ]  TWD1/PB4
- [ ]  SAM4S erase pin on testpoint   —— 21
- [ ]  SAM4S has 12MHz crystal   —— 22
- [ ]  Reset button connected to NRSP pin   —— 23
- [ ]  Power on/off button connected to WKUPn pin   —— 24
- [ ]  Avoid PB4-PB5 for GPIO   —— 25
    - [ ]  They default to JTAG pins on reset but can be reconfigured in software   —— 26
- [ ]  Have a few spare PIO pins connected to pads for last minute mods?   —— 27

---

Hat board 

- [ ]  Fall-back option if IMU does not work
- [ ]  Nav-switch / joystick for remote control
- [ ]  Drive circuit for piezo tweeter
- [ ]  IMU nCS pin connected high to enable I2C operation
- [ ]  IMU AUX pins not connected

---

Racer board

- [ ]  MOSFET for actuator
    - [ ]  p-channel MOSFET need transistor to provide sufficient gate voltage to turn MOSFET off
- [ ]  H bridge driven by 4 PWM signals
    - [ ]  It is best to use PWMHx, note PWMLx and PWMHx are complementary
- [ ]  H-bridge AISEN and BISEN pin connected to ground (unless using current control)
