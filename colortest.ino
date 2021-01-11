#include <NeoPixelBus.h>

const uint16_t PixelCount = 64;
const uint8_t PixelPin = 2;
const uint8_t whiteness = 170;
const char white = 8;
const char black = 16;

NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> strip(PixelCount,PixelPin);
NeoGamma<NeoGammaTableMethod> colorGamma;

RgbwColor bpawn(0, 150, 150 , 0);
RgbwColor wpawn(0, 150, 150, bpawn.CalculateBrightness()*1.5);

RgbwColor bking(0, 0, 150, 0);
RgbwColor wking(0, 0, 150, bking.CalculateBrightness()*1.5);

RgbwColor bknight(150, 0, 150, 0);
RgbwColor wknight(150, 0, 150, bknight.CalculateBrightness()*1.5);

RgbwColor bbishop(150, 0, 0, 0);
RgbwColor wbishop(150, 0, 0, bbishop.CalculateBrightness()*1.5);

RgbwColor brook(0, 150, 0, 0);
RgbwColor wrook(0, 150, 0, brook.CalculateBrightness()*1.5);

RgbwColor bqueen(150, 150, 0, 0);
RgbwColor wqueen(150, 150, 0, bqueen.CalculateBrightness()*1.5);

RgbwColor empty(0);
RgbwColor none(0,0,0, 150);

RgbwColor piece_colors[] =   {empty, none, wpawn, wking, wknight, wbishop, wrook, wqueen, 
                none, bpawn, none, bking, bknight, bbishop, brook, bqueen};

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

void display_board(){
    uint8_t i = 0;
    char piece = 0;
    RgbwColor color;
    uint8_t strip_i = 0;
    while(i < 128){
        //on the board
        if((i & 0x88) == 0){
            piece = board[i];
            color = piece_colors[piece & 15];
            strip.SetPixelColor(strip_i, color);
            ++strip_i;
            ++i;
        } else i+=8;
    }
    strip.Show();
}

void setup(){
    Serial.begin(115200);
    while (!Serial);

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();
    for(uint8_t i=0; i<14; ++i){
        //piece_colors[i].Darken(100);
        //piece_colors[i]  = colorGamma.Correct(piece_colors[i]);
    }
    strip.Begin();
    display_board();
    //print_board();
}

void loop(){}

