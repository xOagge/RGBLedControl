# Arduino RGB LED Controller with Bluetooth

This Arduino project allows you to control the color and brightness of an RGB LED using a Bluetooth module. The color and brightness are adjusted through serial commands sent from a Bluetooth-connected device.

## Components Required

- Arduino board (e.g., Arduino Uno)
- RGB LED
- Bluetooth module (e.g., HC-05, HC-06)
- Potentiometer (for brightness adjustment)
- Resistors (if needed, for current limiting)
- Connecting wires and breadboard

## Pin Connections

- **Red LED Pin:** 10
- **Green LED Pin:** 9
- **Blue LED Pin:** 11
- **Brightness Pin (Potentiometer):** A4

## Code Overview

### Definitions and Variables

- `BLUETOOTH_BAUD`: Baud rate for Bluetooth communication (9600).
- `redPin`, `greenPin`, `bluePin`: Digital pins connected to the RGB LED.
- `brightnessPin`: Analog pin connected to the potentiometer.
- `command`: String to store incoming Bluetooth commands.
- `trueRed`, `trueGreen`, `trueBlue`: Variables to hold RGB values.
- `PValue`: Variable to store raw potentiometer readings.
- `brightness`: Float to store the brightness level.
- `changedBrightness`, `changedColor`: Flags to indicate if brightness or color has changed.

### Functions

- `setup()`: Initializes serial communication with the computer and Bluetooth module. Sets up pin modes.
- `loop()`: Main loop that reads data from the Bluetooth module, processes commands, and updates the LED.
- `isNumeric(String S)`: Checks if a string consists only of numeric characters.
- `setColor()`: Sets the RGB LED color according to the specified RGB values and brightness.
- `readBrightness()`: Reads the potentiometer value and updates the brightness if it has changed.
- `VerifyNewcolor()`: Checks if the command string is valid for updating the color.
- `UpdateLED()`: Updates the LED color and brightness based on the command and potentiometer readings.

## Commands

### RGB Command

- **Format:** `RRRGGGBBB`
- **Description:** Sets the RGB color of the LED.
- **Example:** `123456789` will set the LED to a specific color where `123` is the red value, `456` is the green value, and `789` is the blue value.

### Brightness Adjustment

- Adjusts brightness based on the potentiometer value connected to `brightnessPin`.

## Usage

1. **Upload Code to Arduino:** Use the Arduino IDE to upload the provided code to your Arduino board.
2. **Connect Components:** Wire the RGB LED, potentiometer, and Bluetooth module according to the pin definitions.
3. **Pair Bluetooth Module:** Ensure your Bluetooth module is paired with your smartphone or PC.
4. **Send Commands:**
   - **RGB Command:** Send a 9-digit string to set the LED color.
   - **Brightness Adjustment:** Use the potentiometer to adjust brightness.

## Troubleshooting

- **LED Color Shifts Toward Red:**
  - Ensure the RGB values sent via Bluetooth are within the valid range (0-255).
  - Check if the brightness value is correctly read and applied.

- **Brightness Not Working:**
  - Verify that the potentiometer is properly connected to the `brightnessPin`.
  - Ensure the `brightness` value is being updated and used correctly.

## Notes

- The baud rate for the Bluetooth module and serial communication must match. Adjust the `BLUETOOTH_BAUD` definition if needed.
- The `command` string is processed only when it has 9 digits. Ensure that commands are sent in the correct format.

## License

This project is open-source and can be modified and redistributed under the terms of the [MIT License](https://opensource.org/licenses/MIT).
