#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Airport Baggage Tracking System - ESP32 simulation
// Buttons simulate baggage checkpoint scanners.

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BTN_CHECKIN = 18;
const int BTN_SORTING = 19;
const int BTN_TRANSPORT = 23;
const int BTN_CLAIM = 5;
const int LED_GREEN = 25;
const int LED_RED = 26;
const int BUZZER = 27;

const char *statuses[] = {
  "NOT REGISTERED",
  "CHECK-IN DONE",
  "SORTING DONE",
  "IN TRANSPORT",
  "AT BAGGAGE CLAIM"
};

int stage = 0;
unsigned long lastPress[4] = {0, 0, 0, 0};
const unsigned long debounceMs = 250;

void showStatus() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BAG: TN-2048");
  lcd.setCursor(0, 1);
  lcd.print(statuses[stage]);
  Serial.print("Bag TN-2048 status: ");
  Serial.println(statuses[stage]);
}

void alertError(const char *message) {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  tone(BUZZER, 1200, 250);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INVALID SCAN!");
  lcd.setCursor(0, 1);
  lcd.print(message);
  Serial.print("ERROR: ");
  Serial.println(message);
  delay(800);
  digitalWrite(LED_RED, LOW);
  showStatus();
}

void advanceTo(int requiredStage, int newStage, const char *eventName, int buttonIndex, int buttonPin) {
  if (millis() - lastPress[buttonIndex] < debounceMs) return;
  lastPress[buttonIndex] = millis();

  if (stage == requiredStage) {
    stage = newStage;
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    tone(BUZZER, 1800, 80);
    Serial.print("Checkpoint passed: ");
    Serial.println(eventName);
    showStatus();
  } else {
    alertError("WRONG CHECKPOINT");
  }
  while (digitalRead(buttonPin) == LOW) delay(10); // wait for button release
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN_CHECKIN, INPUT_PULLUP);
  pinMode(BTN_SORTING, INPUT_PULLUP);
  pinMode(BTN_TRANSPORT, INPUT_PULLUP);
  pinMode(BTN_CLAIM, INPUT_PULLUP);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AIRPORT BAGGAGE");
  lcd.setCursor(0, 1);
  lcd.print("TRACKING SYSTEM");
  delay(1200);
  showStatus();
}

void loop() {
  if (digitalRead(BTN_CHECKIN) == LOW) {
    advanceTo(0, 1, "CHECK-IN", 0, BTN_CHECKIN);
  }
  if (digitalRead(BTN_SORTING) == LOW) {
    advanceTo(1, 2, "SORTING", 1, BTN_SORTING);
  }
  if (digitalRead(BTN_TRANSPORT) == LOW) {
    advanceTo(2, 3, "TRANSPORT", 2, BTN_TRANSPORT);
  }
  if (digitalRead(BTN_CLAIM) == LOW) {
    advanceTo(3, 4, "BAGGAGE CLAIM", 3, BTN_CLAIM);
  }
  delay(20);
}
