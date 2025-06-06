#include <RTClib.h>
#include <SD.h>

RTC_DS3231 rtc;
const int buzzer = 5;
const int ledA = 6, sensorA = 2;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(ledA, OUTPUT);
  pinMode(sensorA, INPUT_PULLUP);

  rtc.begin();
  SD.begin();

  logEvent("System started");
}

void loop() {
  DateTime now = rtc.now();

  if (now.hour() == 8 && now.minute() == 0) {
    digitalWrite(ledA, HIGH);
    digitalWrite(buzzer, HIGH);

    unsigned long start = millis();
    bool taken = false;
    while (millis() - start < 180000) { // 3 min window
      if (digitalRead(sensorA) == LOW) {
        taken = true;
        break;
      }
    }

    digitalWrite(buzzer, LOW);
    digitalWrite(ledA, LOW);
    logEvent(taken ? "Compartment A → Taken" : "Compartment A → Missed");
    delay(60000); // Avoid retriggering
  }
}
