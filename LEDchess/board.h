
#ifndef HEADER_BOARD
#define HEADER_BOARD

 #include <cstdint>   
namespace JN {

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
    uint8_t _last_piece = 0;
    bool _blackcastled = false;
    bool _white_castled = false;

    uint8_t * _board = nullptr;
    uint8_t * _moves = nullptr;
    void _init_board();
    void _init_moves();
    void _delete_board();
    void _init();

public:
    Bitboard(/* args */);
    ~Bitboard();

    //move making
    bool valid_move(uint8_t src_sq, uint8_t dst_sq) const;
    void make_move(uint8_t src_sq, uint8_t dst_sq);
    void make_moves(char * moves, uint16_t nummoves);
    char * parse_move() const;
    void undo_move(uint16_t nummoves);

    //getters
    uint8_t * get_board() const;
    uint8_t * get_moves() const;
    uint16_t get_nummoves() const;
    char * valid_moves() const;
    char * valid_moves(uint8_t src_sq) const;
};

}
#endif