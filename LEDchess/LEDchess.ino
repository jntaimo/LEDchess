#include "board.h"
void setup(){
    Serial.begin(115200);
    Serial.print("Initializing");
   JN::Bitboard yeet = JN::Bitboard();
   Serial.print(sizeof(yeet));
   delay(5000);
    Serial.println("I made a bitboard");
}
void loop(){
    Serial.println("I am running");
    Serial.println(millis());
    delay(1000);
}
