# Airport Baggage Tracking System – ESP32 Simulation

A beginner-friendly airport/aviation IoT project using an ESP32. It simulates the checkpoints of a passenger baggage journey with four push buttons acting as virtual baggage scanners.

## Features

- Simulated bag ID: `TN-2048`
- Check-in → Sorting → Transport → Baggage claim status sequence
- 16x2 I2C LCD shows the current baggage status
- Green LED and short beep for a valid checkpoint
- Red LED and buzzer alert for an invalid checkpoint
- Serial Monitor event log

## Simulation

This project is designed for [Wokwi](https://wokwi.com/).

1. Create a new ESP32 project.
2. Replace the sketch with `main.ino`.
3. Add the LCD1602 I2C, four push buttons, two LEDs, two 220 Ω resistors, and a buzzer.
4. Use `diagram.json` as the wiring reference (or import it into the Wokwi project).
5. Add the `LiquidCrystal I2C` library if the simulator asks for it.
6. Start the simulation and press the checkpoint buttons in order.

## Button order

1. CHECK-IN (GPIO 18)
2. SORTING (GPIO 19)
3. TRANSPORT (GPIO 23)
4. BAGGAGE CLAIM (GPIO 5)

Pressing a checkpoint out of order produces an invalid-scan warning.

## Pin mapping

| Component | ESP32 pin |
|---|---|
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |
| Check-in button | GPIO 18 |
| Sorting button | GPIO 19 |
| Transport button | GPIO 23 |
| Baggage claim button | GPIO 5 |
| Green LED | GPIO 25 through 220 Ω resistor |
| Red LED | GPIO 26 through 220 Ω resistor |
| Buzzer + | GPIO 27 |

Buttons are connected between their GPIO and GND and use `INPUT_PULLUP`.

## Important note

The buttons are virtual checkpoint scanners for simulation. In a future physical version, they can be replaced by RFID readers or barcode scanners, and the bag ID can be read from a real tag.

## Resume / portfolio description

**Airport Baggage Tracking System (ESP32, Wokwi, C++):** Designed a simulated baggage tracking system that models airport handling checkpoints, validates the baggage workflow, displays status on an LCD, and signals incorrect checkpoint events with LEDs and a buzzer.

## Suggested GitHub repository name

`esp32-airport-baggage-tracking`
