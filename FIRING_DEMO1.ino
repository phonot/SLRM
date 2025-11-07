#include <Servo.h>

// === Pin Definitions ===
#define leverPin        7   // Master lever switch
#define touch1Pin       2   // Reload gesture start
#define touch2Pin       3   // Reload gesture complete
#define fireSensorPin   4   // Trigger button
#define recoilServoPin  5   // Servo for recoil
#define ledPin          13  // Optional: LED indicator for system armed

// === Config ===
const int MAX_ROUNDS = 20;
const int RECOIL_FORWARD = 50;
const int RECOIL_NEUTRAL = 90;
const int RECOIL_DURATION_MS = 80;
const int DEBOUNCE_DELAY_MS = 300;
const int RELOAD_TIMEOUT_MS = 1500;

// === Variables ===
int roundCount = 0;
bool waitingForSecondTouch = false;
unsigned long lastReloadTime = 0;
bool recoilReady = true;

Servo recoilServo;

void setup() {
  Serial.begin(115200);

  pinMode(leverPin, INPUT);
  pinMode(touch1Pin, INPUT);
  pinMode(touch2Pin, INPUT);
  pinMode(fireSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  recoilServo.attach(recoilServoPin);
  recoilServo.write(RECOIL_NEUTRAL);
}

void loop() {
  bool leverOn = digitalRead(leverPin) == HIGH;

  // Show system armed status with LED
  digitalWrite(ledPin, leverOn ? HIGH : LOW);

  // If lever is OFF, system locked
  if (!leverOn) {
    return;
  }

  // === Reload Mechanism ===
  if (digitalRead(touch1Pin) == HIGH && !waitingForSecondTouch) {
    lastReloadTime = millis();
    waitingForSecondTouch = true;
  }

  if (waitingForSecondTouch) {
    if (millis() - lastReloadTime < RELOAD_TIMEOUT_MS) {
      if (digitalRead(touch2Pin) == HIGH) {
        roundCount = MAX_ROUNDS;
        Serial.println("RELOAD");
        waitingForSecondTouch = false;
      }
    } else {
      waitingForSecondTouch = false;
    }
  }

  // === Fire Logic ===
  if (digitalRead(fireSensorPin) == HIGH && roundCount > 0) {
    // Simulate a target hit (random location for testing)
    int row = random(0, 5);
    int col = random(0, 5);
    Serial.print("Hit at: ");
    Serial.print(row);
    Serial.print(", ");
    Serial.println(col);

    roundCount--;

    // Trigger Recoil
    triggerRecoil();

    delay(DEBOUNCE_DELAY_MS); // Debounce for next shot
  }
}

// === Recoil Function ===
void triggerRecoil() {
  if (recoilReady) {
    recoilReady = false;
    recoilServo.write(RECOIL_FORWARD);
    delay(RECOIL_DURATION_MS);
    recoilServo.write(RECOIL_NEUTRAL);
    delay(20);
    recoilReady = true;
  }
}
