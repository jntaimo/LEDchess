# Chess: Lit Edition
This is a twist on the ancient game of chess, where the pieces are replaced with LED colors that are moved using wireless joysticks, and the board is a scalable LED matrix that you can place on the wall (or anywhere) to play with your friends.
___
![Board](/img/board.jpg)
___
## Table of Contents
- [Chess: Lit Edition](#chess-lit-edition)
  - [Table of Contents](#table-of-contents)
  - [General info](#general-info)
  - [Technologies](#technologies)
    - [Addressable LEDs](#addressable-leds)
    - [Microcontroller](#microcontroller)
  - [Features](#features)
    - [To do:](#to-do)
      - [Basic:](#basic)
      - [Advanced](#advanced)
  - [Sources](#sources)
  - [Inspiration](#inspiration)
  - [About me](#about-me)
  - [Contact](#contact)

## General info
  This is a personal project funded through MIT's [ProjX] program that was presented on March 8, 2021 at MIT's [Xfair]. This repository represents the code of the project; for more information about the design of the board and 3D models check out my website at jntaimo.com/projects/ledchess.

  The chessboard is run using an LED strip with 64 RGBW addressable LEDs, which come in different densities, thereby allowing compatibility with boards of various sizes. A [NodeMcu ESP8266][ESP8266] microcontroller sends the signals to each square based on an internal chessboard representation.
  
  Regarding the interface, the chess board will use two custom wireless controllers, each with an analog joystick and rechargable 18650 Li-ion battery, communicating with the main ESP8266 via another ESP8266 using the [ESP_NOW protocol][ESP-NOW].
  
## Technologies
  ### Addressable LEDs
  * The board uses [SK6812] LEDs, which are similar to [WS2812B] LEDs, but have an extra white LED. This allows for greater LED depth and makes it easier to distinguish between piece colors.
  * The LEDs themselves use the open-source [NeoPixelBus] library by Makuna, which is designed to be computationally lightweight, and run on arduino-compatible boards with built in support for RGBW LEDS (as opposed to RGB). 
  
  ### Microcontroller
  * An [ESP8266] microcontroller holds the internal representation of the chessboard and sends the colors to the LEDs, hence serving as the brains of the operation. This microcontroller is significantly more powerful than a standard arduino board, and supports a host of wifi and wireless capabilities.
  * At the moment, it is unclear whether the ESP8266 microcontroller can handle running a chess engine in real time, so a Teensy4.1 running [microMax] or a Raspberry Pi running [Stockfish] may need to be integrated. Since the ESP8266 has wifi support, it could even do so wirelessly!
  
## Features
* Shows the piece colors in default format.
* Demo animation runs through all of the possible moves from the start configuration, displaying them on the board, as well as over the serial monitor.
* Input moves over the serial connection
* Run chess engine locally
* Converts moves from long algebraic notation (e.g. e2e4 d7d6) to internal square notation
* Allow two-player mode
* Add animations for move selection
### To do:
#### Basic:
* Allow one-player mode (with remote chess engine)
* Add animations for wins, loss, and startup
* Change color profile
* Input moves using wireless controller
#### Advanced
* Input
  * Input moves using keyboard over wifi
* Output
  * Output to multiple displays at once
  * Output to chess audio engine (see AudioChess)
  * Add animations for move selection
    * Joystick only skips to pieces with possible moves
* Read and write portable game notation ([PGN])
  * Demo games stored in [PGN] Locally
  * Demo games stored in [PGN] Remotely
  * Communicate via Universal Chess Interface ([UCI])
  * Convert moves from [Algebraic-Notation] to square notation and vice-versa 
* Chess engine
  * Use chess engine on Raspberry Pi
  * Use chess engine on Teensy4.1
  
## Sources
* [microMax] : very small chess engine
* [NeoPixelBus]: much easier interface with LEDs
* [Code Monkey King]: excellent tutorial on how to set up the basics of microMax
* [Chess Programming Wiki]: an excellent resource for anyone wanting to program something chess-related

## Inspiration
* [The Queen's Gambit]: A super hype chess drama on Netflix - 10/10 would recommend
* [Schachnovelle (The Royal Game)][Schachnovelle]: an excellent short novel by Author [Stefan Zweig] that I read in German IV.

## About me

Welcome to the bottom of the page! You made it! My name is Joseph Ntaimo, and I'm a sophomore at MIT studying mechanical engineering and computer science. My primary interests include music technology (e.g.sound reactive LEDs) and hacking stuff together with microcontrollers. Additionaly, I DJ for my hall at MIT (Woah PUTZ!), and definitely plan on using this chessboard as a sound-reactive display.

## Contact
Check out more about me and my projects at [jntaimo.com](http://www.jntaimo.com).

Do you want to get in touch? Shoot me an email at jntaimo@mit.edu

Interested in playing chess against me? Click [this boyo](https://chess.com/play/shazamthechosen)

[Projx]:https://projx.mit.edu/
[Xfair]:http://xfair.io/
[NeoPixelBus]: https://github.com/Makuna/NeoPixelBus
[microMax]:https://home.hccnet.nl/h.g.muller/max-src2.html
[Stockfish]:https://stockfishchess.org/
[ESP-NOW]:https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
[ESP8266]:https://www.make-it.ca/nodemcu-arduino/nodemcu-details-specifications/
[PGN]:https://en.wikipedia.org/wiki/Portable_Game_Notation
[Algebraic-Notation]:https://en.wikipedia.org/wiki/Algebraic_notation_(chess)
[UCI]:https://en.wikipedia.org/wiki/Universal_Chess_Interface
[SK6812]:https://cdn-shop.adafruit.com/product-files/1138/SK6812+LED+datasheet+.pdf
[WS2812B]:https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
[AudioChess]:https://github.com/jntaimo/audiochess
[Code Monkey King]:https://www.youtube.com/watch?v=M7Hw-f-uUlc&feature=youtu.be
[The Queen's Gambit]:https://en.wikipedia.org/wiki/The_Queen%27s_Gambit_(miniseries)
[Schachnovelle]: https://en.wikipedia.org/wiki/The_Royal_Game
[Stefan Zweig]:https://en.wikipedia.org/wiki/Stefan_Zweig
[Chess Programming Wiki]:https://www.chessprogramming.org/
