#include "board.h"
#include <NeoPixelBrightnessBus.h>
#include <FastLED.h>
#define LED_PIN     4
#define NUM_LEDS    64
#define BRIGHTNESS  100
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define DEPTH 4
CRGB leds[NUM_LEDS];

CRGB bpawn = CRGB::Yellow; 
CRGB wpawn = CRGB::Coral;//yellow

CRGB bking = CRGB::Blue; 
CRGB wking = CRGB::SkyBlue; //Blue

CRGB bknight = CRGB::DarkOrange;
CRGB wknight = CRGB::OrangeRed; // Orange

CRGB bbishop =  CRGB::Red;
CRGB wbishop = CRGB::FireBrick;//red

CRGB brook = CRGB::Green;
CRGB wrook = CRGB::LawnGreen;//Green

CRGB bqueen = CRGB::Purple;
CRGB wqueen = CRGB::Indigo;//purple

CRGB empty = CRGB::Black;
CRGB none = CRGB::Black;//Black

CRGB checker_square = CRGB::Black;
CRGB piece_colors[] =   {empty, none, bpawn, bking, bknight, bbishop, brook, bqueen, 
                                none, wpawn, none, wking, wknight, wbishop, wrook, wqueen};

JN::Bitboard bitboard = JN::Bitboard();

void print_board(uint8_t * board){
    uint8_t i = 0;
    char piece = 0;
    while(i < 128){
        //on the board
        if((i & 0x88) == 0){
            piece = board[i];
            Serial.print(JN::pieces[piece & 15]);
            Serial.print(' ');
            ++i;
        } else {
            Serial.println();
            i += 8;
        }
    }
    Serial.println();
}

uint8_t strip_index(uint8_t index){
    uint8_t row = index / 16;
    uint8_t col = index % 16;
    return 8*row + ((row%2)?col:(7-col)); //odd rows are reversed
}

void display_board(uint8_t * board){
    uint8_t i = 0;
    uint8_t piece = 0;
    CRGB color;
    while(i < 128){
        //on the board
        if((i & 0x88) == 0){
            piece = board[i];
            color = piece_colors[piece & 15];
            uint8_t strip_i = strip_index(i);
            //adds checkers on empty squares
            if(color == empty){
                leds[strip_i] = (strip_i%2)? checker_square:color;
            } else {
                leds[strip_i] = color;
            }
            
            ++i;
        } else i+=8;
    }
    FastLED.show();
}

void user_move(JN::Bitboard &bitboard){
  Serial.println("make move:");
  int *p, c[9];
  int src_sq = 0;
  int dst_sq = 0;
  p = c;
  while(!Serial.available()) delay(100); // check every 10 msecs for input
  while((*p++=Serial.read()) > 10);
  if(*c-10)src_sq=c[0]-16*c[1]+799,dst_sq=c[2]-16*c[3]+799;
  Serial.println(src_sq);
  Serial.println(dst_sq);
  bitboard.make_move(src_sq, dst_sq);
  Serial.println("user_move: ");
  Serial.print(JN::notation[src_sq]);
  Serial.println(JN::notation[dst_sq]);
}

void setup(){
    delay(3000);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Initializing...");
    

}

void loop(){
    
    display_board(bitboard.get_board());
    print_board(bitboard.get_board());
    delay(100);
    user_move(bitboard);
    int score = bitboard.SearchPosition(bitboard._side, DEPTH, -10000, 10000 );
    bitboard.make_move_best();
    display_board(bitboard.get_board());
    print_board(bitboard.get_board());
    Serial.println();
    Serial.print("move #");
    Serial.println(bitboard.get_nummoves());
    Serial.print("score: '");
    Serial.print(score);
    Serial.print("'\n");
    Serial.print("best move: '");
    Serial.print(JN::notation[bitboard.best_src]);
    Serial.println(JN::notation[bitboard.best_dst]);
}
