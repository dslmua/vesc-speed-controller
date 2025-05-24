#include <VescUart.h>
#include <TFT_eSPI.h>
#include <HardwareSerial.h>

// Buttons pins
#define BTN_BACK_PIN   13
#define BTN_TOGGLE_PIN 12
#define BTN_NEXT_PIN   14

// UART0 for VESC communication
HardwareSerial VESC_UART(0);
VescUart vesc;

// TFT display instance
TFT_eSPI tft = TFT_eSPI();

// Speed modes throttle values (0.0 to 1.0)
float speeds[] = {0.2, 0.4, 0.5, 1.0}; // Eco, Drive, Sport, Sport+

int mode = 0;                 // Current mode index
bool powerOn = false;         // Power state
bool sportPlusUnlocked = false; // Secret mode unlocked flag

unsigned long btnTogglePressTime = 0;
bool btnTogglePressed = false;

void setup() {
  Serial.begin(115200);

  // Start UART0 for VESC (RX=GPIO3, TX=GPIO1)
  VESC_UART.begin(115200, SERIAL_8N1, 3, 1);
  vesc.setSerialPort(&VESC_UART);

  // Initialize display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // Initialize buttons as input with pull-up
  pinMode(BTN_BACK_PIN, INPUT_PULLUP);
  pinMode(BTN_TOGGLE_PIN, INPUT_PULLUP);
  pinMode(BTN_NEXT_PIN, INPUT_PULLUP);

  updateDisplay();
}

void updateDisplay() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(10, 10);

  if (!powerOn) {
    tft.println("Power OFF");
  } else {
    tft.print("Mode: ");
    switch (mode) {
      case 0: tft.println("Eco (10 km/h)"); break;
      case 1: tft.println("Drive (20 km/h)"); break;
      case 2: tft.println("Sport (25 km/h)"); break;
      case 3: tft.println("Sport+ (50 km/h)"); break;
    }
  }
}

void setSpeedMode(int newMode) {
  if (newMode < 0) newMode = 0;
  if (newMode > 3) newMode = sportPlusUnlocked ? 3 : 2;
  mode = newMode;

  if (powerOn) {
    vesc.setSpeed(speeds[mode]);
  }
  updateDisplay();
}

void powerOff() {
  powerOn = false;
  vesc.setSpeed(0);
  updateDisplay();
}

void powerOnFunc() {
  powerOn = true;
  vesc.setSpeed(speeds[mode]);
  updateDisplay();
}

void loop() {
  bool backPressed = digitalRead(BTN_BACK_PIN) == LOW;
  bool togglePressed = digitalRead(BTN_TOGGLE_PIN) == LOW;
  bool nextPressed = digitalRead(BTN_NEXT_PIN) == LOW;

  if (backPressed) {
    delay(200); // simple debounce
    setSpeedMode(mode - 1);
    while (digitalRead(BTN_BACK_PIN) == LOW) delay(10); // wait release
  }

  if (nextPressed) {
    delay(200);
    setSpeedMode(mode + 1);
    while (digitalRead(BTN_NEXT_PIN) == LOW) delay(10);
  }

  if (togglePressed && !btnTogglePressed) {
    btnTogglePressed = true;
    btnTogglePressTime = millis();
  }

  if (!togglePressed && btnTogglePressed) {
    unsigned long pressDuration = millis() - btnTogglePressTime;
    btnTogglePressed = false;

    if (pressDuration >= 3000) { // long press: toggle secret mode unlock
      sportPlusUnlocked = !sportPlusUnlocked;
      if (!sportPlusUnlocked && mode == 3) {
        setSpeedMode(2);
      }
    } else { // short press: toggle power
      if (powerOn) {
        powerOff();
      } else {
        powerOnFunc();
      }
    }
  }

  delay(50);
}