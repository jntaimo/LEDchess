#include "board.h"
void printboard();
void setup(){
    delay(500);
    Serial.begin(115200);
    Serial.println("Initializing...");
    //JN::Bitboard yeet = JN::Bitboard();
    Serial.println("I made a bitboard");
}
void loop(){
    JN::Bitboard yeet = JN::Bitboard();
    while(1){
    Serial.println("I am running");
    Serial.println(millis());
    printboard(yeet);
    delay(1000);
    }
}

void printboard(JN::Bitboard bitboard){
    const char * board = bitboard.get_board();
    // uint8_t N=-1;
    // while(++N<121) Serial.write(N&8&&(N+=7)?10:".?+nkbrq?*?NKBRQ"[board[N]&15]); 
    //for (uint8_t i = 0; i <128; ++i) Serial.print(board[i]);
}