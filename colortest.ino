#include <NeoPixelBus.h>

const uint16_t PixelCount = 64;
const uint8_t PixelPin = 2;
const uint8_t whiteness = 128;
NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> strip(PixelCount,PixelPin);

RgbwColor bpawn(166, 255, 77, 0);
RgbwColor wpawn(166, 255, 77, whiteness);

RgbwColor bking(77, 255, 255, 0);
RgbwColor wking(77, 255, 255, whiteness);

RgbwColor bknight(204, 34, 0, 0);
RgbwColor wknight(204, 34, 0, whiteness);

RgbwColor bbishop(102, 25, 255, 0);
RgbwColor wbishop(102, 25, 255, whiteness);

RgbwColor brook(255, 255, 0, 0);
RgbwColor wrook(255, 255, 0, whiteness);

RgbwColor bqueen(255, 119, 51, 0);
RgbwColor wqueen(255, 119, 51, whiteness);

RgbwColor empty(0);
RgbwColor white(0,0,0,whiteness);

RgbwColor piece_colors[] =   {empty,white, wpawn, wking, wknight, wbishop, wrook, wqueen, 
                white, bpawn, white, bking, bknight, bbishop, brook, bqueen};
char pieces[] = ".-pknbrq-P-KNBRQ";
char board[129] = {
    22, 20, 21, 23, 19, 21, 20, 22, 0,  0,  0,  0,  0,  0,  0,  0,
    18, 18, 18, 18, 18, 18, 18, 18, 0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    9,  9,  9,  9,  9,  9,  9,  9,  0,  0,  0,  0,  0,  0,  0,  0,
    14, 12, 13, 15, 11, 13, 12, 14, 0,  0,  0,  0,  0,  0,  0,  0,
};

void print_board(){
    uint8_t i = 0;
    char piece = 0;
    while(i < 128){
        //on the board
        if((i & 0x88) == 0){
            piece = board[i];
            Serial.print(pieces[piece & 15]);
            Serial.print(' ');
            ++i;
        } else {
            Serial.println();
            i += 8;
        }
    }
}

void setup(){
    Serial.begin(115200);
    while (!Serial);

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    strip.Begin();
    strip.Show();

    print_board();
}

void loop(){}

