#include "board.h"
#include <NeoPixelBrightnessBus.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#define LED_PIN     4
#define NUM_LEDS    64
#define BRIGHTNESS  100
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define DEPTH 3

CRGB leds[NUM_LEDS];

CRGB bpawn = CRGB::Yellow; 
CRGB wpawn = CRGB::Goldenrod;//yellow

CRGB bking = CRGB::Blue; 
CRGB wking = CRGB::RoyalBlue; //Blue

CRGB bknight = CRGB::DarkOrange;
CRGB wknight = CRGB::OrangeRed; // Orange

CRGB bbishop =  CRGB::Red;
CRGB wbishop = CRGB::FireBrick;//red

CRGB brook = CRGB::Green;
CRGB wrook = CRGB::LawnGreen;//Green

CRGB bqueen = CRGB::Purple;
CRGB wqueen = CRGB::Amethyst;//purple

CRGB empty = CRGB::Black;
CRGB none = CRGB::White;//Black

CRGB checker_square = CRGB::Black;
CRGB piece_colors[] =   {empty, none, bpawn, bking, bknight, bbishop, brook, bqueen, 
                                none, wpawn, none, wking, wknight, wbishop, wrook, wqueen};

JN::Bitboard bitboard = JN::Bitboard();
uint8_t selector = 0;
typedef struct Directions{
  bool up;
  bool down;
  bool left;
  bool right;
  bool button;
} Directions;
Directions Dirs {false, false, false, false, false}; 
void printDir(Directions &Dirs){
  Serial.print("up ");
  Serial.print(Dirs.up);
  Serial.print(" down ");
  Serial.print(Dirs.down);
  Serial.print(" left ");
  Serial.print(Dirs.left);
  Serial.print(" right ");
  Serial.print(Dirs.right);
  Serial.println(Dirs.button ? " !":" .");
}
// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&Dirs, incomingData, sizeof(Dirs));
  move_selector(selector, Dirs);
  display_board(bitboard.get_board());
  display_selector(selector);
  //Serial.print("Bytes received: ");
  //Serial.println(len);
  //printDir(Dirs);
  //Serial.println();
}
uint8_t move_selector(uint8_t &selector, Directions &Dirs){
    Serial.print("Selector square: ");
    Serial.println(JN::notation[selector]);
    //makes sure it's on the board
    if (Dirs.up && !((selector - 16) & 0x88)) selector -= 16;
    if (Dirs.down && !((selector + 16) & 0x88)) selector +=16;
    if (Dirs.left && !((selector - 1) & 0x88)) selector -= 1;
    if (Dirs.right && !((selector + 1) & 0x88)) selector += 1;
    return selector;
}

void display_selector(uint8_t selector){
    leds[strip_index(selector)] = none;
    FastLED.show();
}
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

//Converts the bitboard index to the proper index on the LED strip
//Does not check that the index is on the board.
uint8_t strip_index(uint8_t index){
    uint8_t row = index / 16;
    uint8_t col = index % 16;
    return 8*row + ((row%2)?col:(7-col)); //odd rows are reversed
}

//Displays the current state of the bitboard on the LEDs
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
    //display_selector(selector);
    FastLED.show();
}
//Inputs a usermove in long algebraic notation over the Serial port
//If no move is entered, then the computer thinks of a move on its own.
void user_move(JN::Bitboard &bitboard){
  Serial.println("make move:");
  int *p, c[9];
  int src_sq = 0;
  int dst_sq = 0;
  p = c;
  while(!Serial.available()) delay(100); // check every 10 msecs for input
  while((*p++=Serial.read()) > 10);
  if(*c-10){src_sq=c[0]-16*c[1]+799,dst_sq=c[2]-16*c[3]+799;
  Serial.println(src_sq);
  Serial.println(dst_sq);
  bitboard.make_move(src_sq, dst_sq);
  Serial.println("user_move: ");
  Serial.print(JN::notation[src_sq]);
  Serial.println(JN::notation[dst_sq]);
  } else {
    int score = bitboard.SearchPosition(bitboard._side, DEPTH, -10000, 10000 );
    bitboard.make_move_best();    
  }
}

void computer_move(JN::Bitboard &bitboard){
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

void joystick_move(JN::Bitboard &bitboard, Directions &Dirs, uint8_t &selector){
    int src_sq = 0;
    int dst_sq = 0;
    uint8 piece = 0;
    uint8_t *board = bitboard.get_board();
    while (1){
        while (!Dirs.button) delay(100);//wait for first button press
        Serial.println("First button press");
        Dirs.button = false;
        piece = board[selector];
        Serial.print("Source piece at: ");
        Serial.println(JN::notation[selector]);
        //piece exists and is on the same side
        if (piece && (piece & bitboard._side)) src_sq = selector;
        else continue; //restart if invalid square
        while (!Dirs.button) delay(100);//wait for second button press
        Serial.println("Second button press");
        Dirs.button = false;
        //piece exists and is on the same side
        piece = board[selector];
        Serial.print("Destination square at: ");
        Serial.println(JN::notation[selector]);        
        //No piece at destination
        //Or opposite side piece
        if (!piece || (piece & (24 - bitboard._side))) dst_sq = selector;
        else continue;
        if (bitboard.valid_move(src_sq, dst_sq)){
            Serial.println("VALID MOVE");
            Dirs.button = false;
            Serial.println("Making move");
            Serial.println(JN::notation[src_sq]);
            Serial.println(JN::notation[dst_sq]);
            bitboard.make_move(src_sq, dst_sq); 
            return;   
        }
        Serial.println("invalid move");
    }
    

}
void setup(){
    delay(1000);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    Serial.println("Initializing...");
    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
     }
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(OnDataRecv);     
    display_board(bitboard.get_board());

}

void loop(){
    //user_move(bitboard);
    joystick_move(bitboard, Dirs, selector);
    display_board(bitboard.get_board());
    print_board(bitboard.get_board());
    delay(100);
    //while(!Serial.available()) delay(50);
    computer_move(bitboard);
}
