#include "board.h"
#include <cstdio>

void printboard(JN::Bitboard bitboard){
    const char * b = bitboard.get_board();
    for(uint8_t i=0;i<121;i++)printf(" %c",i&8&&(i+=7)?10:".?+nkbrq?*?NKBRQ"[b[i]&15]);
}

int main(){
    printf("Starting up...\n");
    JN::Bitboard bitboard = JN::Bitboard();
    printboard(bitboard);
    return 0;
}