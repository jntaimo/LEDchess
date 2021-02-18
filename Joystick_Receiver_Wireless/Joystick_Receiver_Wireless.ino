/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-one-to-many-esp8266-nodemcu/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

// Structure example to receive data
// Must match the sender structure
typedef struct Directions{
  bool up;
  bool down;
  bool left;
  bool right;
  bool button;
} Directions;

Directions Dirs {false, false, false, false, false}; 
void printDir(Directions &Dirs){

  Serial.print("up ");
  Serial.print(Dirs.up);
  Serial.print(" down ");
  Serial.print(Dirs.down);
  Serial.print(" left ");
  Serial.print(Dirs.left);
  Serial.print(" right ");
  Serial.print(Dirs.right);
  Serial.println(Dirs.button ? " !":" .");
}
// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&Dirs, incomingData, sizeof(Dirs));
  Serial.print("Bytes received: ");
  Serial.println(len);
  printDir(Dirs);
  Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  
}
