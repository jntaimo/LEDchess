#include "board.h"
#include <cstdio>

void printboard(JN::Bitboard bitboard){
    char * b = bitboard.get_board();
    for(uint8_t i=0;i<121;i++)printf(" %c",i&8&&(i+=7)?10:JN::pieces[b[i]&15]);
    printf("\n");
}

int main(){
    printf("Starting up...\n");
    JN::Bitboard bitboard = JN::Bitboard();
    for (uint8_t i = 3; i > 0; --i) printboard(bitboard);
    // printf("Normal empty board\n\n\n");
    // char * _board = new char[129]; 
    // for(int i = 0; i < 129; ++i ) _board[i] = 0;
    
    // uint8_t K=8;
    // while(K--){_board[K]=(_board[K+112]=JN::step_vectors[K+24]+8)+8;_board[K+16]=18;_board[K+96]=9;  /* initial board setup*/
    // //uint8_t L=8;while(L--)_board[16*L+K+8]=(K-4)*(K-4)+(L-3.5)*(L-3.5); /* center-pts table   */
    // }  
    // for(uint8_t i = 0; i < 2; ++i){
    //     for(uint8_t i=0;i<121;i++)printf(" %c",i&8&&(i+=7)?10:JN::pieces[_board[i]&15]);
    //     printf("\n");       
    // }
    return 0;
}