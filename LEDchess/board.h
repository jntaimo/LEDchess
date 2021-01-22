
#ifndef HEADER_BOARD
#define HEADER_BOARD

#include <cstdint>
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
const char pieces[] = ".-pknbrq-P-KNBRQ";     // print ASCII characters to represent pieces on board

const char *pieces_ascii[] = {                      // print unicode characters to represent pieces on board

 " ", "-", "\u265F", "\u265A", "\u265E", "\u265D", "\u265C", "\u265B", 
 "-", "\u2659", "-", "\u2654", "\u2658", "\u2657", "\u2656", "\u2655",  

};

class Bitboard
{
private:
    uint16_t _nummoves = 0; 
    uint8_t _side = 8; //8 for white, 16 for black
    bool _blackcastled = false;
    bool _white_castled = false;

    char _board[129];
    const char *_pieces = pieces;
    const char *_pieces_ascii = *pieces_ascii;

    void _init_board();
    void _clear_board();
    void _reset_board();
    void _init();

public:
    Bitboard(/* args */);
    ~Bitboard();

    //move making
    bool valid_move();
    bool make_move();
    void undo_move(uint16_t nummoves);

    //
    void print_board();
    void display_board();
    //getters
    char * get_board();
    char * get_moves();
    uint16_t get_nummoves();
    char * valid_moves();
};

}
#endif