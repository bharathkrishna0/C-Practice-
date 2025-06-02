#include "esp_camera.h"
#include "face_recognition_tool.h"  

#define SERVO_PIN 13

void setup() {
  
  camera_config_t config = { /* your camera setup */ };
  esp_camera_init(&config);

  
  face_recognition_init();

  
  pinMode(SERVO_PIN, OUTPUT);
}

void loop() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) return;

 
  if (face_detected(fb)) {
    if (recognize_face(fb)) {
      unlockDoor();
    }
  }

  esp_camera_fb_return(fb);
}

void unlockDoor() {
  
  analogWrite(SERVO_PIN, 90); 
  delay(5000);
  analogWrite(SERVO_PIN, 0); 
}
