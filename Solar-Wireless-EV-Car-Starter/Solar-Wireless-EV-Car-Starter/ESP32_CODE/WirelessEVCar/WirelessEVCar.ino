/*
  Solar-Wireless-EV-Car - ESP32-WROOM-32 controller

  Hardware:
    L298N ENA -> GPIO25 (left motor PWM)
    L298N IN1 -> GPIO26
    L298N IN2 -> GPIO27
    L298N ENB -> GPIO32 (right motor PWM)
    L298N IN3 -> GPIO33
    L298N IN4 -> GPIO14
    OLED SDA  -> GPIO21
    OLED SCL  -> GPIO22

  Bluetooth Classic device name: WirelessEVCar
  Commands: F, B, L, R, S, +, -

  IMPORTANT:
  - This firmware is only the low-voltage control layer.
  - It does not measure RX voltage/current or prove that the wireless
    receiver can supply motor startup current.
  - Keep the ZVS transmitter disconnected until its previous wiring-burn
    fault is diagnosed and the power stage is independently validated.
*/

#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if __has_include(<esp_arduino_version.h>)
  #include <esp_arduino_version.h>
#endif

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error "Bluetooth is not enabled in this ESP32 Arduino build. Select an ESP32-WROOM-32 target with Bluetooth support."
#endif

// L298N pins
constexpr int ENA = 25;
constexpr int IN1 = 26;
constexpr int IN2 = 27;
constexpr int ENB = 32;
constexpr int IN3 = 33;
constexpr int IN4 = 14;

// OLED I2C pins and display
constexpr int OLED_SDA = 21;
constexpr int OLED_SCL = 22;
constexpr uint8_t OLED_ADDRESS = 0x3C;
constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;

// PWM configuration
constexpr uint32_t PWM_FREQUENCY = 1000;
constexpr uint8_t PWM_RESOLUTION = 8;
constexpr uint8_t LEFT_PWM_CHANNEL = 0;
constexpr uint8_t RIGHT_PWM_CHANNEL = 1;
constexpr int START_SPEED = 150;  // 0..255; tune only after measuring supply and motor current
constexpr int MIN_SPEED = 0;
constexpr int MAX_SPEED = 255;

// Stop motors if no valid command arrives within this interval.
constexpr unsigned long COMMAND_TIMEOUT_MS = 3000;

BluetoothSerial SerialBT;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int motorSpeed = START_SPEED;
char currentCommand = 'S';
unsigned long lastCommandAt = 0;
bool oledReady = false;

void writePwm(int pin, int channel, int duty) {
  duty = constrain(duty, 0, 255);
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  (void)channel;
  ledcWrite(pin, duty);
#else
  (void)pin;
  ledcWrite(channel, duty);
#endif
}

void setupPwm() {
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(ENA, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttach(ENB, PWM_FREQUENCY, PWM_RESOLUTION);
#else
  ledcSetup(LEFT_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(RIGHT_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(ENA, LEFT_PWM_CHANNEL);
  ledcAttachPin(ENB, RIGHT_PWM_CHANNEL);
#endif
  writePwm(ENA, LEFT_PWM_CHANNEL, 0);
  writePwm(ENB, RIGHT_PWM_CHANNEL, 0);
}

void setMotorOutputs(int leftA, int leftB, int rightA, int rightB) {
  digitalWrite(IN1, leftA);
  digitalWrite(IN2, leftB);
  digitalWrite(IN3, rightA);
  digitalWrite(IN4, rightB);
  writePwm(ENA, LEFT_PWM_CHANNEL, motorSpeed);
  writePwm(ENB, RIGHT_PWM_CHANNEL, motorSpeed);
}

void stopMotors() {
  writePwm(ENA, LEFT_PWM_CHANNEL, 0);
  writePwm(ENB, RIGHT_PWM_CHANNEL, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  currentCommand = 'S';
}

void applyCommand(char command) {
  command = toupper(static_cast<unsigned char>(command));
  switch (command) {
    case 'F': // both motors forward
      setMotorOutputs(HIGH, LOW, HIGH, LOW);
      currentCommand = 'F';
      break;
    case 'B': // both motors reverse
      setMotorOutputs(LOW, HIGH, LOW, HIGH);
      currentCommand = 'B';
      break;
    case 'L': // tank-style left turn
      setMotorOutputs(LOW, HIGH, HIGH, LOW);
      currentCommand = 'L';
      break;
    case 'R': // tank-style right turn
      setMotorOutputs(HIGH, LOW, LOW, HIGH);
      currentCommand = 'R';
      break;
    case 'S':
      stopMotors();
      break;
    case '+':
      motorSpeed = min(motorSpeed + 15, MAX_SPEED);
      if (currentCommand != 'S') {
        writePwm(ENA, LEFT_PWM_CHANNEL, motorSpeed);
        writePwm(ENB, RIGHT_PWM_CHANNEL, motorSpeed);
      }
      break;
    case '-':
      motorSpeed = max(motorSpeed - 15, MIN_SPEED);
      if (currentCommand != 'S') {
        writePwm(ENA, LEFT_PWM_CHANNEL, motorSpeed);
        writePwm(ENB, RIGHT_PWM_CHANNEL, motorSpeed);
      }
      break;
    default:
      return; // ignore unknown input; do not refresh timeout
  }
  lastCommandAt = millis();
}

void updateDisplay() {
  if (!oledReady) return;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Wireless EV Car"));
  display.println(F("ESP32 Controller"));
  display.println();
  display.print(F("Bluetooth: "));
  display.println(SerialBT.hasClient() ? F("Connected") : F("Waiting"));
  display.print(F("Command: "));
  display.println(currentCommand);
  display.print(F("Motor PWM: "));
  display.println(motorSpeed);
  display.println(F("RX voltage: not measured"));
  display.display();
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  setupPwm();
  stopMotors();

  Wire.begin(OLED_SDA, OLED_SCL);
  oledReady = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  if (oledReady) {
    display.clearDisplay();
    display.display();
  }

  if (!SerialBT.begin("WirelessEVCar")) {
    Serial.println(F("Bluetooth start failed"));
  } else {
    Serial.println(F("Bluetooth ready: WirelessEVCar"));
  }

  lastCommandAt = millis();
  updateDisplay();
}

void loop() {
  while (SerialBT.available()) {
    const char incoming = static_cast<char>(SerialBT.read());
    if (incoming == '\n' || incoming == '\r' || incoming == ' ' || incoming == '\t') {
      continue;
    }
    applyCommand(incoming);
  }

  // Fail safe: stop on Bluetooth disconnect or command timeout.
  if (!SerialBT.hasClient() || (millis() - lastCommandAt > COMMAND_TIMEOUT_MS)) {
    stopMotors();
  }

  static unsigned long lastDisplayAt = 0;
  if (millis() - lastDisplayAt >= 300) {
    updateDisplay();
    lastDisplayAt = millis();
  }
}
