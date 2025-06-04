#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"
#include "fd_forward.h"

#define LED_PIN 4
RTC_DATA_ATTR int bootCount = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  
  camera_config_t config = {/* setup pins */};
  esp_camera_init(&config);

  // Init SD card
  if(!SD_MMC.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }

  
  bootCount++;
}

void loop() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) return;

  
  if (face_detected(fb)) {
    digitalWrite(LED_PIN, HIGH);
    savePhotoToSD(fb);
    digitalWrite(LED_PIN, LOW);
    delay(5000); 
  }

  esp_camera_fb_return(fb);
  delay(1000);
}

void savePhotoToSD(camera_fb_t *fb) {
  String path = "/face_" + String(millis()) + ".jpg";
  File file = SD_MMC.open(path.c_str(), FILE_WRITE);
  if (!file) return;
  file.write(fb->buf, fb->len);
  file.close();
}
