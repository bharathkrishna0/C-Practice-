#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTPIN D3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define RELAY_LIGHT D1
#define RELAY_FAN   D2

const char* ssid = "YourWiFi";
const char* password = "YourPassword";

ESP8266WebServer server(80);

void handleRoot() {
  float temp = dht.readTemperature();
  String html = "<html><body><h1>Smart Home Control</h1>";
  html += "<p>Temperature: " + String(temp) + " C</p>";
  html += "<p><a href=\"/lighton\">Light ON</a> | <a href=\"/lightoff\">Light OFF</a></p>";
  html += "<p><a href=\"/fanon\">Fan ON</a> | <a href=\"/fanoff\">Fan OFF</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  digitalWrite(RELAY_LIGHT, HIGH); // Relay OFF (active low)
  digitalWrite(RELAY_FAN, HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi connected! IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/lighton", []() {
    digitalWrite(RELAY_LIGHT, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/lightoff", []() {
    digitalWrite(RELAY_LIGHT, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/fanon", []() {
    digitalWrite(RELAY_FAN, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/fanoff", []() {
    digitalWrite(RELAY_FAN, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
