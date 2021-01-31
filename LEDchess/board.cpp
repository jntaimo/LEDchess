//Author: Joseph Ntaimo
//File
#include "board.h"
#include <cstdio>
namespace JN {
const char *notation[] = {           // convert square id to board notation

    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",     "i8","j8","k8","l8","m8","n8","o8", "p8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",     "i7","j7","k7","l7","m7","n7","o7", "p7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",     "i6","j6","k6","l6","m6","n6","o6", "p6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",     "i5","j5","k5","l5","m5","n5","o5", "p5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",     "i4","j4","k4","l4","m4","n4","o4", "p4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",     "i3","j3","k3","l3","m3","n3","o3", "p3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",     "i2","j2","k2","l2","m2","n2","o2", "p2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",     "i1","j1","k1","l1","m1","n1","o1", "p1",

};

const int newboard[128] = {                 // 0x88 board + positional scores

    22, 20, 21, 23, 19, 21, 20, 22,    0,  0,  5,  5,  0,  0,  5,  0, 
    18, 18, 18, 18, 18, 18, 18, 18,    5,  5,  0,  0,  0,  0,  5,  5,
     0,  0,  0,  0,  0,  0,  0,  0,    5, 10, 15, 20, 20, 15, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0,    5, 10, 20, 30, 30, 20, 10,  5,    
     0,  0,  0,  0,  0,  0,  0,  0,    5, 10, 20, 30, 30, 20, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0,    5, 10, 15, 20, 20, 15, 10,  5,
     9,  9,  9,  9,  9,  9,  9,  9,    5,  5,  0,  0,  0,  0,  5,  5,
    14, 12, 13, 15, 11, 13, 12, 14,    0,  0,  5,  5,  0,  0,  5,  0

};
const char pieces[] = ".-pknbrq-P-KNBRQ";     // print ASCII characters to represent pieces on board

const char *pieces_ascii[] = {                      // print unicode characters to represent pieces on board

 " ", "-", "\u265F", "\u265A", "\u265E", "\u265D", "\u265C", "\u265B", 
 "-", "\u2659", "-", "\u2654", "\u2658", "\u2657", "\u2656", "\u2655",  

};
int step_vectors[]={-16,-15,-17,0,1,16,0,1,16,15,17,0,14,18,31,33,0, /* step-vector lists */
     7,-1,11,6,8,3,6,                          /* 1st dir. in o[] per piece*/
     6,3,5,7,4,5,3,6};                         /* initial piece setup      */

//constructor
Bitboard::Bitboard(/* args */) {
    _init(); 
}
//destructor
Bitboard::~Bitboard(){
    _delete_board();
}

//Initializes a bitboard with pieces in standard positions
void Bitboard::_init_board(){
//Concise method from micro-Max
//More details here https://home.hccnet.nl/h.g.muller/encode.html
 _board = new char[129]; 
 if (!_board) printf("No board space");
for(int i = 0; i < 129; ++i ) _board[i]= 0;//clear board completely
 int K=8;
 while(K--){_board[K]=(_board[K+112]=step_vectors[K+24]+8)+8;_board[K+16]=18;_board[K+96]=9;  /* initial board setup*/
 }
 K=8;
 while (K--){  
 for(uint8_t i=0;i<121;i++)printf(" %c",i&8&&(i+=7)?10:JN::pieces[_board[i]&15]);
 printf("\n");
}
}

//Deletes the board, allowing the memory to be used elsewhere
void Bitboard::_delete_board(){
    if(_board) delete[] _board;
    if(_moves) delete[] _moves;
    _board = nullptr;
    _moves = nullptr;
}

//constructor helper that resets the board and tracking variables
//in preparation for a new game.
void Bitboard::_init(){
    _delete_board();
    _init_board();
    _side = WHITE; 
    _nummoves = 0;

}

//Returns whether a move is valid based on the current board configuration
//moves are the indices into the bitboard
//src_sq = source square index
//dst_sq = destination square index
bool Bitboard::valid_move(uint8_t src_sq, uint8_t dst_sq) const {

}

//Makes a move on the bitboard
//moves are the indices into the the bitboard
//src_sq = source square index
//dst_sq = destination square index
//returns false if the move is invalid
//returns true if the move was properly executed
bool Bitboard::make_move(uint8_t src_sq, uint8_t dst_sq){
    if(src_sq > 127 || dst_sq > 127) return false;
    char piece = _board[src_sq];    
    _board[src_sq] = 0; 
    _board[dst_sq] = piece;
    //add move to moves array
    //
    return true;
}
//makes a series of moves stored in array pairs of indices
//even indices are the source square indices
//odd indices are the destination square indices.
bool Bitboard::make_moves(char * moves){

}
//Reverts the last nummoves moves that were made
//defaults to undoing the last move if nummoves is not specified
void Bitboard::undo_move(uint16_t nummoves = 1){

}
//returns a cchar pointer to the location of the board array
char * Bitboard::get_board() const{
    return _board;
}
//returns a pointer to an array of pairs of previously made moves
//based on the current board configuration
//even indices are the source squares indices
//odd indices are the destination square indices
char * Bitboard::get_moves() const{
    return _moves;
} 

//returns an array of move strings in algebraic notation
char * Bitboard::get_moves_alg() const{
    // char alg_moves[_nummoves];
    // for (uint8_t i = 0; i < _nummoves; ++i){
    //     alg_moves[i] = *notation[i]; //gets the algebraic form of each move
    // }
    // return alg_moves;
}

//Returns the number of moves that have been made in the current game
uint16_t Bitboard::get_nummoves() const{
    return _nummoves;
}


//returns a pointer to an array possible moves
//based on the current board configuration
//even indices are the source squares indices
//odd indices are the destination square indices
char * Bitboard::valid_moves() const{
    
} 

//returns a pointer to an array of possible moves
//for the piece at the bitboard index src_sq
char * Bitboard::valid_moves(uint8_t src_sq) const{

}

}