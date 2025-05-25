#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "SmartPlant"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

#define DHTPIN D4
#define DHTTYPE DHT11
#define SOILPIN A0
#define LEDPIN D2

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int soil = analogRead(SOILPIN);
  int soilPercent = map(soil, 1023, 0, 0, 100); // Dry = 1023, Wet = 0

  Blynk.virtualWrite(V0, soilPercent);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);

  if (soilPercent < 30) {
    digitalWrite(LEDPIN, HIGH);
    Blynk.virtualWrite(V3, 255); // Turn ON LED in app
  } else {
    digitalWrite(LEDPIN, LOW);
    Blynk.virtualWrite(V3, 0);   // Turn OFF LED in app
  }
}

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
