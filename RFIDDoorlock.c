#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <EEPROM.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 rfid(SS_PIN, RST_PIN);
Servo lockServo;

byte masterUID[] = {0xDE, 0xAD, 0xBE, 0xEF};  // Replace with your master card UID

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  lockServo.attach(6);
  lockServo.write(0); // Locked
  Serial.println("RFID Access Control Ready");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  Serial.print("Scanned UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (isAuthorized(rfid.uid.uidByte)) {
    unlockDoor();
  } else {
    Serial.println("Access Denied");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

bool isAuthorized(byte *uid) {
  for (int i = 0; i < 4; i++) {
    if (uid[i] != masterUID[i]) return false;
  }
  return true;
}

void unlockDoor() {
  Serial.println("Access Granted");
  lockServo.write(90); // Unlock
  delay(3000);
  lockServo.write(0);  // Lock back
}
