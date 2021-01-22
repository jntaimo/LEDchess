//Author: Joseph Ntaimo
//File
#include "board.h"
namespace JN {
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

}

//Deletes the board, allowing the memory to be used elsewhere
void Bitboard::_delete_board(){

}

//constructor helper that resets the board and tracking variables
//in preparation for a new game.
void Bitboard::_init(){

}

//Returns whether a move is valid based on the current board configuration
//moves are the indices into the bitboard
//src_sq = source square index
//dst_sq = destination square index
bool Bitboard::valid_move(uint8_t src_sq, uint8_t dst_sq) {

}

//Makes a move on the bitboard
//moves are the indices into the the bitboard
//src_sq = source square index
//dst_sq = destination square index
//returns false if the move is invalid
//returns true if the move was properly executed
bool Bitboard::make_move(uint8_t src_sq, uint8_t dst_sq){

}

//Reverts the last nummoves moves that were made
//defaults to undoing the last move if nummoves is not specified
void Bitboard::undo_move(uint16_t nummoves = 1){

}
//returns a cchar pointer to the location of the board array
char * Bitboard::get_board(){

}
//returns a pointer to an array of pairs of previously made moves
//based on the current board configuration
//even indices are the source squares indices
//odd indices are the destination square indices
char * Bitboard::get_moves(){

} 

//returns an array of move strings in algebraic notation
char * Bitboard::get_moves_alg(){

}

//Returns the number of moves that have been made in the current game
uint16_t Bitboard::get_nummoves(){

}


//returns a pointer to an array possible moves
//based on the current board configuration
//even indices are the source squares indices
//odd indices are the destination square indices
char * Bitboard::valid_moves(){
    
} 

//returns a pointer to an array of possible moves
//for the piece at the bitboard index src_sq
char * Bitboard::valid_moves(uint8_t src_sq){

}

}