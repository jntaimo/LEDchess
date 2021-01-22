
#ifndef HEADER_BOARD
#define HEADER_BOARD

 #include <cstdint>   
namespace JN {

extern const char *notation[128];
extern const char pieces[17];
extern const char *pieces_ascii[16];
extern char step_vectors[32];                      
enum{WHITE = 8, BLACK = 16};
class Bitboard
{
private:
    uint16_t _nummoves = 0; 
    uint8_t _side = WHITE; 
    bool _blackcastled = false;
    bool _white_castled = false;

    char * _board = nullptr;
    char * _moves = nullptr;
    void _init_board();
    void _delete_board();
    void _init();

public:
    Bitboard(/* args */);
    ~Bitboard();

    //move making
    bool valid_move(uint8_t src_sq, uint8_t dst_sq);
    bool make_move(uint8_t src_sq, uint8_t dst_sq);
    bool make_moves(char * moves);
    char * parse_move();
    void undo_move(uint16_t nummoves);

    //getters
    char * get_board();
    char * get_moves();
    char * get_moves_alg();
    uint16_t get_nummoves();
    char * valid_moves();
    char * valid_moves(uint8_t src_sq);
};

}
#endif