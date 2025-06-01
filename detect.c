#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "YourWiFi";
const char* password = "YourPassword";

const char* botToken = "YOUR_TELEGRAM_BOT_TOKEN";
const char* chatID = "YOUR_CHAT_ID";

#define REED_PIN D1
bool lastState = HIGH;

void sendTelegramMessage(const String& msg) {
  WiFiClientSecure client;
  client.setInsecure(); // For HTTPS without cert verification

  if (!client.connect("api.telegram.org", 443)) {
    Serial.println("Connection failed");
    return;
  }

  String url = "/bot" + String(botToken) + "/sendMessage?chat_id=" + String(chatID) + "&text=" + msg;
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: api.telegram.org\r\n" +
               "Connection: close\r\n\r\n");
}

void setup() {
  Serial.begin(115200);
  pinMode(REED_PIN, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("Connected!");
}

void loop() {
  bool currentState = digitalRead(REED_PIN);
  if (currentState == LOW && lastState == HIGH) {
    sendTelegramMessage("📬 Mailbox Opened!");
    delay(2000);  // Debounce and avoid spamming
  }
  lastState = currentState;
  delay(100);
}

