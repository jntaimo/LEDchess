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

#include <Bounce2.h>
#define APIN A0  // Analog input pin that the potentiometer is attached to
#define LED_PIN LED_BUILTIN // Analog output pin that the LED is attached to
#define BUTTON_PIN D3
#define AXIS_PIN D5

int X = 0;        // value read from the pot
int Y = 0;        // value output to the PWM (analog out)
unsigned long previousMillis = 0;
const long interval = 100;


uint8_t chessboardMACAddress[] = {0xC8, 0x2B, 0x96, 0x30, 0x2C, 0x78};


// Structure example to send data
// Must match the receiver structure
//typedef struct test_struct {
//    int x;
//    int y;
//} test_struct;
typedef struct Directions{
  bool up;
  bool down;
  bool left;
  bool right;
  bool button;
} Directions;
// Create a struct_message called test to store variables to be sent
//test_struct test;
Directions Dirs {false, false, false, false, false}; 
Bounce2::Button button = Bounce2::Button();
int ledState = LOW;
//unsigned long lastTime = 0;  
//unsigned long timerDelay = 2000;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  char macStr[18];
  Serial.print("Packet to:");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  //Init button
  button.attach(BUTTON_PIN, INPUT);
  button.interval(5);
  button.setPressedState(LOW);
  //Init LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  //Init axis selector
  pinMode(AXIS_PIN, OUTPUT);  
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(chessboardMACAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

}
void getX(){
  digitalWrite(AXIS_PIN, HIGH);
  X = analogRead(APIN);
}

void getY(){
  digitalWrite(AXIS_PIN, LOW);
  Y = analogRead(APIN);
}

void printXY(){
  Serial.print("X = ");
  Serial.print(X);
  Serial.print(" ");
  Serial.print("Y = ");
  Serial.println(Y);
}

void getDir(Directions &Dirs){
  Dirs.up = Dirs.down = Dirs.left = Dirs.right = false;
  if(Y > 900) Dirs.up = true;
  if(Y < 100) Dirs.down = true;
  if(X > 900) Dirs.right = true;
  if(X < 100) Dirs.left = true;
}

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

void loop() {
    button.update();
  if(button.pressed()){
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Dirs.button = true;
    Dirs.left = Dirs.right = Dirs.up = Dirs.down = false;
    //printDir(Dirs);
    esp_now_send(0, (uint8_t *) &Dirs, sizeof(Dirs));
  } else {
    Dirs.button = false;   
    if(millis() - previousMillis >= interval){
      previousMillis = millis();
      getX();
      getY();
      getDir(Dirs);
      //printXY();
      //printDir(Dirs);
      esp_now_send(0, (uint8_t *) &Dirs, sizeof(Dirs));
    }
  }
//  if ((millis() - lastTime) > timerDelay) {
//    // Set values to send
//    test.x = random(1, 50);
//    test.y = random(1, 50);
//
//    // Send message via ESP-NOW
//    esp_now_send(0, (uint8_t *) &test, sizeof(test));
//
//    lastTime = millis();
//  }
}
