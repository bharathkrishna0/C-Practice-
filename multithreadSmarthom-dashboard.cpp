#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MOTION_PIN 5
#define GAS_PIN 34

// WiFi
const char* ssid = "YourSSID";
const char* password = "YourPassword";

AsyncWebServer server(80);

// Shared variables
volatile float temperature = 0.0;
volatile bool motionDetected = false;
volatile int gasLevel = 0;
portMUX_TYPE mutex = portMUX_INITIALIZER_UNLOCKED;

void motionTask(void *pvParameters) {
  pinMode(MOTION_PIN, INPUT);
  while (1) {
    portENTER_CRITICAL(&mutex);
    motionDetected = digitalRead(MOTION_PIN);
    portEXIT_CRITICAL(&mutex);
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void tempTask(void *pvParameters) {
  dht.begin();
  while (1) {
    float t = dht.readTemperature();
    if (!isnan(t)) {
      portENTER_CRITICAL(&mutex);
      temperature = t;
      portEXIT_CRITICAL(&mutex);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void gasTask(void *pvParameters) {
  while (1) {
    int g = analogRead(GAS_PIN);
    portENTER_CRITICAL(&mutex);
    gasLevel = g;
    portEXIT_CRITICAL(&mutex);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setupServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<h2>Smart Home Dashboard</h2>";
    html += "<p>🌡️ Temperature: " + String(temperature) + " °C</p>";
    html += "<p>🏃 Motion Detected: " + String(motionDetected ? "Yes" : "No") + "</p>";
    html += "<p>🔥 Gas Level: " + String(gasLevel) + "</p>";
    request->send(200, "text/html", html);
  });

  server.begin();
}

void webTask(void *pvParameters) {
  setupServer();
  while (1) {
    vTaskDelay(10000 / portTICK_PERIOD_MS); // idle loop
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  xTaskCreatePinnedToCore(motionTask, "Motion", 1000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(tempTask, "Temp", 1000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(gasTask, "Gas", 1000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(webTask, "Web", 3000, NULL, 1, NULL, 0);
}

void loop() {}
