#include "board.h"
#include <cstdio>

void printboard(uint8_t * b){
    for(uint8_t i=0;i<121;i++)printf(" %c",i&8&&(i+=7)?10:JN::pieces[b[i]&15]);
    printf("\n");
}

void printboardfancy(uint8_t * board)
{
    for(int sq = 0; sq < 128; sq++)
    {
        if(!(sq % 16)) printf(" %d  ", 8 - (sq / 16));    // print ranks to the left of the board
        printf(" %c", ((sq & 8) && (sq += 7)) ? '\n' : JN::pieces[board[sq] & 15]);    // ASCII pieces
        //printf(" %s", ((sq & 8) && (sq += 7)) ? "\n" : JN::pieces_ascii[board[sq] & 15]);    // unicode pieces
    }
    
    printf("\n     a b c d e f g h\n\nYour move: \n");
}

void printmoves(uint8_t * moves, uint16_t nummoves){
    for (uint16_t i =0; i < 2*nummoves; i += 2){
        printf("From %d to %d\n",moves[i],moves[i+1]);
    }
}

void makemove(JN::Bitboard &bitboard){
    //more info here https://home.hccnet.nl/h.g.muller/legal.html
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

void computerplay(JN::Bitboard &bitboard, int depth = 2){
    while(1)    // computer plays against itself
    {
        int score = bitboard.SearchPosition(bitboard._side, depth, -10000, 10000);    // search best move
        
        // make AI move
        bitboard.make_move_best();

        printboardfancy(bitboard.get_board());
        printf("\nscore: '%d'\n", score);
        printf("best move: '%s%s'\n", JN::notation[bitboard.best_src], JN::notation[bitboard.best_dst]);
        
        getchar();
    }
}
int main(){
    
    printf("Starting up...\n");
    JN::Bitboard bitboard = JN::Bitboard();
    
    computerplay(bitboard, 4);
    return 0;
}