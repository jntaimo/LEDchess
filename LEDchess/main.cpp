#include "board.h"
#include <cstdio>

void printboard(JN::Bitboard bitboard){
    const char * b = bitboard.get_board();
    for(uint8_t i=0;i<121;i++)printf(" %c",i&8&&(i+=7)?10:JN::pieces[b[i]&15]);
    printf("\n");
}

int main(){
    printf("Starting up...\n");
    JN::Bitboard bitboard = JN::Bitboard();
    for (uint8_t i = 5; i > 0; --i) printboard(bitboard);
    printf("Normal empty board\n\n\n");
    for (uint8_t i = 5; i > 0; --i){
        for(uint8_t i=0;i<121;i++)printf(" %c",i&8&&(i+=7)?10:JN::pieces[JN::newboard[i]&15]);
    }
    return 0;
}