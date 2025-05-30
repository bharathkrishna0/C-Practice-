#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YourWiFi";
const char* password = "YourPassword";
const char* mqtt_server = "broker.hivemq.com"; // Or your local broker

WiFiClient espClient;
PubSubClient client(espClient);

#define RELAY_LIGHT D1
#define RELAY_FAN   D2

void callback(char* topic, byte* payload, unsigned int length) {
  String command;
  for (int i = 0; i < length; i++) {
    command += (char)payload[i];
  }

  if (String(topic) == "home/light") {
    digitalWrite(RELAY_LIGHT, command == "on" ? LOW : HIGH);
  }
  if (String(topic) == "home/fan") {
    digitalWrite(RELAY_FAN, command == "on" ? LOW : HIGH);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      client.subscribe("home/light");
      client.subscribe("home/fan");
    } else {
      delay(2000);
    }
  }
}

void setup() {
  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  digitalWrite(RELAY_LIGHT, HIGH);
  digitalWrite(RELAY_FAN, HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
