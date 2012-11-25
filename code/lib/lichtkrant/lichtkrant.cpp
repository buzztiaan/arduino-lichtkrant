#include "Arduino.h"
#include "lichtkrant.h"

byte frameBuffer[ROWS][SHREGISTERS];

byte readPixel(byte whichBuffer[][SHREGISTERS], byte x, byte y) // left upper pixel is x0, y0. it does account for the not connected pins on the sh-registers.
{
  return bitRead(whichBuffer[y][(x+NONVISABLES)/(SHREGISTERS+1)], 7-((x+NONVISABLES)%8));  
}

void setPixel(byte whichBuffer[][SHREGISTERS], byte value, byte x, byte y) // left upper pixel is x0, y0. it does account for the not connected pins on the sh-registers.
{
   bitWrite(whichBuffer[y][(x+NONVISABLES)/(SHREGISTERS+1)], 7-((x+NONVISABLES)%8) , value);
}

void bufferCopy(byte from[][SHREGISTERS], byte to[][SHREGISTERS])
{
  for(byte row = 0; row < ROWS; row++)
  {
    for(byte sr = 0; sr < SHREGISTERS; sr++)
    {
      to[row][sr] = from[row][sr];
    }
  }
}  

void setBuffer(byte whichBuffer[][SHREGISTERS], byte data)
{
  for(byte row = 0; row < ROWS; row++)
  {
    for(byte sr = 0; sr < SHREGISTERS; sr++)
    {
      whichBuffer[row][sr] = data;
    }
  }  
}

void serviceFramebuffer(void)
{
  unsigned long currentMicros = micros();
  static long prevRowMicros = 0L;
  if(currentMicros - prevRowMicros > MICROSPERROW) 
  {
    
    static int rowInUse = 0;    

    prevRowMicros = currentMicros;

    digitalWrite(rowToPin[rowInUse], HIGH); // switch row /off/

    rowInUse++;
    if (rowInUse == ROWS) 
    {
      rowInUse = 0;
    }
    digitalWrite(LATCHPIN, LOW);
    for(byte sr = 0; sr < SHREGISTERS; sr++)
    {
      shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, ~frameBuffer[rowInUse][sr]);  // 0 is /on/, 1 is /off/
    }
    digitalWrite(LATCHPIN, HIGH);
    digitalWrite(rowToPin[rowInUse], LOW);  // switch row /on/
  }
}

void initHardware(void)
{
  for(byte row = 0; row < 7; row++)   // row mosfets
  {
    pinMode(rowToPin[row], OUTPUT);
    digitalWrite(rowToPin[row], HIGH);            // turn all /off/. These pins are also pulled up externally.
  }

  pinMode(DATAPIN, OUTPUT);             // shiftregister
  digitalWrite(DATAPIN, HIGH); 
  pinMode(LATCHPIN, OUTPUT);
  digitalWrite(LATCHPIN, HIGH);       
  pinMode(CLOCKPIN, OUTPUT);
  digitalWrite(CLOCKPIN, LOW);        

  digitalWrite(LATCHPIN, LOW);
  for(byte sr = 0; sr < SHREGISTERS; sr++)
  {
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, byte(B11111111));  // all /off/
  }
  digitalWrite(LATCHPIN, HIGH);  
}

