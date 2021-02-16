#include <Bounce2.h>
#define APIN A0  // Analog input pin that the potentiometer is attached to
#define LED_PIN LED_BUILTIN // Analog output pin that the LED is attached to
#define BUTTON_PIN D3
#define AXIS_PIN D5
int X = 0;        // value read from the pot
int Y = 0;        // value output to the PWM (analog out)
unsigned long previousMillis = 0;
const long interval = 100;

typedef struct Directions{
  bool up;
  bool down;
  bool left;
  bool right;
  bool button;
};
Directions Dirs {false, false, false, false, false}; 
Bounce2::Button button = Bounce2::Button();
int ledState = LOW;
void setup() {
  button.attach(BUTTON_PIN, INPUT);
  button.interval(5);
  button.setPressedState(LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  Serial.begin(115200);
  pinMode(AXIS_PIN, OUTPUT);
  
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
    printDir(Dirs);
  } else {
    Dirs.button = false;   
    if(millis() - previousMillis >= interval){
      previousMillis = millis();
      getX();
      getY();
      getDir(Dirs);
      //printXY();
      printDir(Dirs);
    
    }
  }
  

}
