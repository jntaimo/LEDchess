
#ifndef HEADER_BOARD
#define HEADER_BOARD

#include <cstdint>
class Bitboard
{
private:
    uint16_t _nummoves = 0; 
    
    bool _blackcastled = false;
    bool _white_castled = false;

    char _board[129];
    char _pieces[17] = ".-pknbrq-P-KNBRQ";
    char * _pieces_ascii = nullptr

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
    bool undo_move(uint16_t nummoves = 1);
    void print_board();

    //getters
    char * get_board();
    char * get_moves();
    uint16_t * get_nummoves();

};


#endif