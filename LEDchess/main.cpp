#include "board.h"
#include <cstdio>

void printboard(uint8_t * b){
    for(uint8_t i=0;i<121;i++)printf(" %c",i&8&&(i+=7)?10:JN::pieces[b[i]&15]);
    printf("\n");
}
void printmoves(uint8_t * moves, uint16_t nummoves){
    for (uint16_t i =0; i < 2*nummoves; i += 2){
        printf("From %d to %d\n",moves[i],moves[i+1]);
    }
}
void makemove(JN::Bitboard &bitboard){
    int *p;
    int chars[9];
    int src_sq;
    int dst_sq;
    p = chars;
    while((*p++=getchar())>10);
    if(*chars-10){
    src_sq=*chars-16*chars[1]+799,dst_sq=chars[2]-16*chars[3]+799;
    bitboard.make_move(src_sq,dst_sq);
    } 
}

int main(){
    
    printf("Starting up...\n");
    JN::Bitboard bitboard = JN::Bitboard();
    while (1){
    printboard(bitboard.get_board());
    makemove(bitboard);
    printf("\n");
    }
    return 0;
}