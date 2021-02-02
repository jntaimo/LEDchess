#include "board.h"
#include <cstdio>

void printboard(uint8_t * b){
    for(uint8_t i=0;i<121;i++)printf(" %c",i&8&&(i+=7)?10:JN::pieces[b[i]&15]);
    printf("\n");
}

int main(){
    printf("Starting up...\n");
    JN::Bitboard bitboard = JN::Bitboard();
    printboard(bitboard.get_board());
    bitboard.make_move(0,17);
    return 0;
}