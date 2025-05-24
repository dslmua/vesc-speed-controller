# VESC Speed Controller with ESP32 and 2.8” TFT Display (ST7789)

## Description

This project allows you to control speed modes of an electric scooter or any device with a VESC 75100 controller using an ESP32 microcontroller. The current speed mode is displayed on a 2.8” TFT display (ST7789), and three buttons enable switching between modes and toggling power.

---

## Features

- Four speed modes:  
  - Eco — 10 km/h  
  - Drive — 20 km/h  
  - Sport — 25 km/h  
  - Sport+ (secret mode) — 50 km/h  

- Three buttons:  
  - Back — decrease speed mode  
  - ON/OFF — toggle power (long press unlocks secret mode)  
  - Next — increase speed mode  

- VESC control via UART0 on ESP32

- Visual feedback on TFT display

---

## Wiring

| Component      | ESP32 GPIO | Notes                         |
|----------------|------------|-------------------------------|
| Button Back    | 13         | Decrease speed mode button    |
| Button ON/OFF  | 12         | Power toggle button           |
| Button Next    | 14         | Increase speed mode button    |
| TFT Display    | See TFT_eSPI config           | ST7789 display                |
| VESC RX        | GPIO1 (TX0) | ESP32 TX → VESC RX            |
| VESC TX        | GPIO3 (RX0) | ESP32 RX → VESC TX            |
| GND            | GND        | Common ground                 |

---

## Installation

1. Install [Arduino IDE](https://www.arduino.cc/en/software) if you haven't already.
2. Install the required libraries via Arduino Library Manager:  
   - **VescUart**  
   - **TFT_eSPI**
3. Configure the `User_Setup.h` file in the TFT_eSPI library for your ST7789 display pins.
4. Open the `.ino` file in Arduino IDE.
5. Connect your ESP32, TFT display, buttons, and VESC according to the wiring.
6. Upload the sketch to your ESP32.

---

## Required Libraries

This project depends on the following Arduino libraries, which you need to install before compiling:

- VescUart — for communication with the VESC controller via UART.  
  You can find it on GitHub or install manually if not available in the Library Manager.

- TFT_eSPI — for controlling the 2.8" TFT display (ST7789).  
  Install it via Arduino IDE Library Manager:  
  Sketch → Include Library → Manage Libraries...  
  then search for TFT_eSPI and click Install.

- HardwareSerial — built-in with Arduino ESP32 core, no installation needed.

---

### How to install libraries via Arduino IDE

1. Open Arduino IDE.
2. Go to Sketch → Include Library → Manage Libraries....
3. In the search bar, type the library name (e.g., `TFT_eSPI`).
4. Select the library in the list and click Install.
5. Repeat for each required library.

---

If you can't find VescUart in the Library Manager, download it manually from its GitHub repository and install it:  
Sketch → Include Library → Add .ZIP Library...  
then select the downloaded ZIP file.

---

Make sure these libraries are installed before compiling the project.

---

## Usage

- Press **Next** and **Back** buttons to cycle through speed modes.
- Press **ON/OFF** button to toggle power (turn on/off controller and display).
- Hold **ON/OFF** button for 3 seconds to unlock or lock the secret Sport+ mode.

---

## License

This project is licensed under the MIT License.

---

## Author

Created by [dslmua]
