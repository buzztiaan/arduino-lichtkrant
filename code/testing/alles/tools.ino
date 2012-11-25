byte readPixel(byte x, byte y) // left upper pixel is x0, y0. it does not account for the not connected pins on the sh-registers.
{
  return byte(bitRead(frameBuffer[y][x/8], x%8));
}

void setPixel(byte value, byte x, byte y) // left upper pixel is x0, y0. it does not account for the not connected pins on the sh-registers.
{
  bitWrite(frameBuffer[y][x/8], x%8 , value); 
}

void shiftFrameBufferDown1()
{
  for(byte sr = 0; sr < SHREGISTERS; sr++)
  {
    byte buffer = frameBuffer[ROWS - 1][sr];
    for(char row = ROWS - 1; row >= 0 ; row--)
    {
      frameBuffer[row][sr] = frameBuffer[row - 1][sr];      
    }
    frameBuffer[0][sr] = buffer;
  }
}

void shiftFrameBufferUp1()
{
  for(byte sr = 0; sr < SHREGISTERS; sr++)
  {
    byte buffer = frameBuffer[0][sr];
    for(byte row = 0; row < ROWS - 1; row++)
    {
      frameBuffer[row][sr] = frameBuffer[row + 1][sr];      
    }
    frameBuffer[ROWS - 1][sr] = buffer;
  }
}

void shiftFrameBufferRight1()
{
  for(byte shift = 0; shift < (COLUMNS - 6 - 1); shift++)
    shiftFrameBufferLeft1();                  // yeah, lame. i know... :D Let's call it code reuse, ok?
}

void shiftFrameBufferLeft1()
{
  byte bufa=0;
  bufa = bitRead(frameBuffer[0][0], 2);
  for (byte row = 1; row < ROWS; row++)
  {
    bufa = bufa << 1;
    bufa += bitRead(frameBuffer[row][0], 2);
  }

  for (byte sr = 0; sr < SHREGISTERS - 1; sr++)
  {
    for (byte row = 0; row < ROWS; row++)
    {
      //byte bufb = bitRead(frameBuffer[row][sr], 7);
      frameBuffer[row][sr] = (frameBuffer[row][sr] << 1) + bitRead(frameBuffer[row][sr+1], 7);
    }
  }

  for (char row = ROWS -1; row >= 0; row--)
  {
    frameBuffer[row][SHREGISTERS - 1] = (frameBuffer[row][SHREGISTERS - 1] << 1 ) + bitRead(bufa, 0);
    bufa = bufa >> 1;
  }
}

void setFrameBuffer(byte data)
{
  for(byte row = 0; row < ROWS; row++)
  {
    for(byte sr = 0; sr < SHREGISTERS; sr++)
    {
      frameBuffer[row][sr] = data;
    }
  }  
}

void copyToFrameBuffer(byte data[ROWS][SHREGISTERS])
{
  for(byte row = 0; row < ROWS; row++)
  {
    for(byte sr = 0; sr < SHREGISTERS; sr++)
    {
      frameBuffer[row][sr] = data[row][sr];
    }
  }  
}


