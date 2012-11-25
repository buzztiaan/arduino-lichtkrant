//
// !! OLD'N BUGGY !!
//

#include "frames.h"

#ifndef SHREGISTERS 
#define SHREGISTERS 7
#endif
#ifndef ROWS        
#define ROWS        7
#endif
#define COLUMNS     56

#define DATAPIN  22
#define LATCHPIN 23
#define CLOCKPIN 24

#define ROW0PIN  A0   
#define ROW1PIN  A1
#define ROW2PIN  A2
#define ROW3PIN  A3
#define ROW4PIN  A4
#define ROW5PIN  A5
#define ROW6PIN  A6

#define MICROSPERROW 2750 // ~50 full frames per second. ( 1000000micros / 50 frames per second / 7 rows = 2857)

#define MILLISPERIMAGE 500



byte imageInBuffer = 0;

const byte rowToPin[ROWS] = 
{ 
  ROW0PIN, ROW1PIN, ROW2PIN, ROW3PIN, ROW4PIN, ROW5PIN, ROW6PIN
};
  
byte frameBuffer[ROWS][SHREGISTERS];

void setup() 
{  
  for(byte row = 0; row < ROWS; row++)   // row mosfets
  {
    pinMode(rowToPin[row], OUTPUT);
    digitalWrite(rowToPin[row], HIGH);            // turn all /off/
  }

  pinMode(DATAPIN, OUTPUT);      // shiftregister
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

  

  /*  
   for(int i = A8; i < A12; i++)  // for external eeprom
   {
   pinMode(i, OUTPUT);
   }
   */
   
   copyToFrameBuffer(nerdz);  
   //setFrameBuffer(0x00);
}

void loop()
{
  serviceFramebuffer();
  
  unsigned long currentMillis = millis();
  static long prevImageMillis = 0L;
  if(currentMillis - prevImageMillis > MILLISPERIMAGE) 
  {
    prevImageMillis = currentMillis; 
    switch (imageInBuffer)
    {
      case 0:
//        for(byte column = 0; column < COLUMNS; column++)
//        {
//          for(byte row = 0; row < ROWS; row++)
//          {
//            setPixel(!readPixel(column, row), column, row);
//          }
//        }
shiftFrameBufferRight1();
        imageInBuffer++;
        break;
      case 1:
//        for(byte column = 0; column < COLUMNS; column++)
//        {
//          for(byte row = 0; row < ROWS; row++)
//          {
//            setPixel(!readPixel(column, row), column, row);
//          }
//        }
shiftFrameBufferRight1();
        imageInBuffer=0;
        break;
    }
  }
  
} // end of loop()








