
#ifndef HEADER_BOARD
#define HEADER_BOARD

#include <cstdint>   
namespace JN {
extern const int max_moves;
extern const char *notation[128];
extern const int newboard[128];
extern const char pieces[17];
extern const char *pieces_ascii[16];
extern int step_vectors[32];                      
enum{WHITE = 8, BLACK = 16};
class Bitboard
{
private:
    uint16_t _nummoves = 0; 
    uint8_t _side = WHITE; 
    bool _blackcastled = false;
    bool _white_castled = false;

    static uint8_t _board[128];
    static uint8_t _moves[2 * max_moves];
    void _init_board();
    void _clear_board();
    void _delete_moves();
    void _init();

public:
    Bitboard(/* args */);
    ~Bitboard();

    //move making
    bool valid_move(uint8_t src_sq, uint8_t dst_sq) const;
    bool make_move(uint8_t src_sq, uint8_t dst_sq);
    bool make_moves(uint8_t * moves, uint8_t nummoves);
    char * parse_move() const;
    void undo_move(uint16_t nummoves);

    //getters
    uint8_t * get_board() const;
    uint8_t * get_moves() const;
    char * get_moves_alg() const;
    uint16_t get_nummoves() const;
    char * valid_moves() const;
    char * valid_moves(uint8_t src_sq) const;
};

}
#endif