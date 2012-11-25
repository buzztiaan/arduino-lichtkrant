#include <MemoryFree.h>

#ifndef LICHTKRANT_H
#define LICHTKRANT_H

#include "Arduino.h"

#define SHREGISTERS 7
#define ROWS        7
#define COLUMNS     50   // actually visible columns, 6 pins of the 'last' register (first byte in buffers) is not used.
#define NONVISABLES 6

#define DATAPIN  5
#define LATCHPIN 4
#define CLOCKPIN 3

#define ROW0PIN  6 //A0   
#define ROW1PIN  7 //A1
#define ROW2PIN  8 //A2
#define ROW3PIN  9 //A3
#define ROW4PIN  10 //A4
#define ROW5PIN  11 //A5
#define ROW6PIN  12 //A6

#define MICROSPERROW 2750   // ~50 full frames per second. ( 1000000micros in a second / 50 frames per second / 7 rows = 2857micros per row)

const byte rowToPin[ROWS] = 
{ 
  ROW0PIN, ROW1PIN, ROW2PIN, ROW3PIN, ROW4PIN, ROW5PIN, ROW6PIN
};

void initHardware(void);
void serviceFramebuffer(void);
void setBuffer(byte whichBuffer[][SHREGISTERS], byte data);
void bufferCopy(byte from[][SHREGISTERS], byte to[][SHREGISTERS]);
void setPixel(byte whichBuffer[][SHREGISTERS], byte value, byte x, byte y);
byte readPixel(byte whichBuffer[][SHREGISTERS],byte x, byte y);


#endif
