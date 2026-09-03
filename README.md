# AirDraw

**EE 2361 Final Project**


## Overview

AirDraw is a PIC24 library that combines physical motion with pixel-based digital art. The library abstracts the underlying PIC24 hardware, allowing developers to focus on application logic rather than peripheral management.

AirDraw provides:

* **WS2812B (NeoPixel) LED control** using cycle-accurate assembly bit-banging for stable rendering.
* **MPU-6050 IMU integration** through I2C communication.
* **Motion filtering** using an Alpha Filter to convert noisy physical movement into smooth cursor movement.
* **8×8 digital canvas** support for drawing with the LED matrix.
* **Timestamp-based button detection** capable of identifying single, double, and triple clicks.

Together, these features provide a modular foundation for real-time, motion-driven interaction.

## Hardware

| Component  | Part         | Description                                      |
| ---------- | ------------ | ------------------------------------------------ |
| Joystick   | Adafruit 512 | 2-axis potentiometer joystick with select button |
| LED Matrix | WS2812B      | 8×8, 64-pixel RGB LED array                      |
| IMU Sensor | MPU-6050     | 3D motion tracking sensor                        |

## API Documentation

### `void init_hardware(void)`

Initializes the hardware required by AirDraw.

**Functionality:**

* Configures the PIC24
* Initializes ADC channels for the joystick
* Configures Timer2 for 1-second interval tracking
* Wakes the MPU-6050 from sleep mode

**Inputs:** None

**Outputs:** None

---

### `void get_air_coords(int *x, int *y)`

Converts physical device movement into coordinates on the LED matrix.

The function reads the device's tilt, applies filtering to reduce hand-shaking and cursor jitter, and converts the resulting position into coordinates within the `0–7` range.

**Inputs:**

* `int *x` — Pointer to the X coordinate
* `int *y` — Pointer to the Y coordinate

**Outputs:** None

---

### `uint16_t read_adc(uint8_t channel)`

Reads the current position of a joystick axis through the PIC24 ADC.

The physical joystick position is converted into a value between `0` and `1023`.

**Inputs:**

* `uint8_t channel` — ADC channel to read

**Returns:**

* `uint16_t` — ADC value from `0–1023`

---

### `Action check_button_actions(void)`

Determines what type of button press occurred using the system's global `timeCounter`.

Supported actions include:

* `NO_CLICK`
* `SINGLE_CLICK`
* `DOUBLE_CLICK`
* `TRIPLE_CLICK`

**Inputs:** None

**Returns:** `Action`

---

### `void update_matrix(int curX, int curY)`

Updates the LED matrix display.

The function renders the saved artwork to the LED matrix and displays a cursor at the current position.

**Inputs:**

* `curX` — Current X position
* `curY` — Current Y position

**Outputs:** None

## Basic Usage

The basic implementation establishes a direct connection between device movement and the LED matrix.

After initializing the hardware, the program continuously polls the MPU-6050 for motion data. The library applies an Alpha Filter to smooth the sensor readings, converts the filtered motion into `0–7` coordinates, and updates the LED display.

This produces a steady LED cursor that follows the physical tilt of the device in real time.

## Advanced Usage

The advanced implementation turns AirDraw into a multi-functional digital sketchbook.

It demonstrates:

* Triple-click mode switching
* Manual joystick control
* Motion-based air drawing
* Button-hold drawing
* Coordinate filtering
* Persistent pixel-buffer storage

The system uses a state-driven loop to switch between joystick and motion-based control. The display is cleared when changing modes, while the cursor position is continuously updated using either raw ADC readings or filtered IMU data.

When the button is held, color data is written to the persistent `pixelBuffer`, allowing the user to draw directly onto the LED matrix.

## Project Structure

A typical AirDraw project can be organized around the following components:

```text
AirDraw/
├── README.md
├── src/
    └── ...

```

## Technologies

* **PIC24**
* **C**
* **Assembly**
* **I2C**
* **ADC**
* **Timer2**
* **WS2812B / NeoPixel**
* **MPU-6050**
* **Embedded Systems**
* **Sensor Filtering**

