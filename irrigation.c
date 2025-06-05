int soilPin = 34; 
int lightPin = 35; 
int pumpPin = 26;  

void setup() {
  Serial.begin(115200);
  pinMode(pumpPin, OUTPUT);
  initSD(); 
}

void loop() {
  int soilVal = analogRead(soilPin);
  int lightVal = analogRead(lightPin);
  
  bool isDry = soilVal > 2500;
  bool isSunny = lightVal > 1000;

  if (isDry && isSunny) {
    digitalWrite(pumpPin, HIGH); 
    delay(3000);                
    digitalWrite(pumpPin, LOW);

    logData(soilVal, lightVal); 
  }

  delay(600000); 
}

void logData(int moisture, int light) {
  File file = SD_MMC.open("/log.txt", FILE_APPEND);
  file.printf("Moisture: %d, Light: %d, Time: %lu\n", moisture, light, millis());
  file.close();
}
