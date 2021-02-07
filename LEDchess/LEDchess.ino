#include "board.h"
#include <NeoPixelBrightnessBus.h>

const uint16_t PixelCount = 64;
const uint8_t PixelPin = 24; // ignored for ESP8266
const uint8_t whiteness = 170;
int depth = 3;

NeoPixelBrightnessBus<NeoGrbwFeature, Neo800KbpsMethod> strip(PixelCount,PixelPin);
NeoGamma<NeoGammaTableMethod> colorGamma;

RgbwColor bpawn(255, 255, 0 , 200);
RgbwColor wpawn(255, 255, 0, 0); //yellow

RgbwColor bking(0, 0, 255, 200);
RgbwColor wking(0, 0, 255, 0);//dark blue

RgbwColor bknight(255, 128, 0, 200);
RgbwColor wknight(255, 128, 0, 0);//orange

RgbwColor bbishop(255, 0, 0, 100);
RgbwColor wbishop(255, 0, 0, 0);//red

RgbwColor brook(0, 255, 0, 200);
RgbwColor wrook(0, 255, 0, 0); // green

RgbwColor bqueen(187, 51, 255, 100);
RgbwColor wqueen(187, 51, 255, 0);//purple

RgbwColor empty(0);
RgbwColor none(0,0,0, 255);


RgbwColor checker_square(0, 0, 0, 255);
RgbwColor piece_colors[] =   {empty, none, bpawn, bking, bknight, bbishop, brook, bqueen, 
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
    return 8*row + ((row%2)?(7-col):col); //even rows are reversed
}

void display_board(uint8_t * board){
    uint8_t i = 0;
    uint8_t piece = 0;
    RgbwColor color;
    while(i < 128){
        //on the board
        if((i & 0x88) == 0){
            piece = board[i];
            color = piece_colors[piece & 15];
            uint8_t strip_i = strip_index(i);
            //adds checkers on empty squares
            if(color == empty){
                strip.SetPixelColor(strip_i, (strip_i%2)? RgbwColor::LinearBlend(color,checker_square,0.10):color);
            } else {
                strip.SetPixelColor(strip_i,color);
            }
            
            ++i;
        } else i+=8;
    }
    strip.Show();
}

void setup(){
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Initializing...");
    for(uint8_t i=0; i<14; ++i){
        piece_colors[i]  = colorGamma.Correct(piece_colors[i]);
    }
    strip.SetBrightness(120);
    strip.Begin();
    //display_board(bitboard.get_board());

}

void loop(){

    int score = bitboard.SearchPosition(bitboard._side, depth, -10000, 10000 );
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
    delay(1000);
}
