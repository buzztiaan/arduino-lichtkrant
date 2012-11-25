byte countNeigbours(byte whichBuffer[][SHREGISTERS], byte x, byte y)
{
  byte xRight = (x + 1) % COLUMNS;           // 1 position to the right, if x == max, roll over to 0.
  byte xLeft= (x + COLUMNS - 1) % COLUMNS;   // 1 position to the left, if x == 0, roll over to max.
  byte yDown  = (y + 1) % ROWS;              // 1 position down, if y == max, roll over to 0.
  byte yUp= (y + ROWS - 1) % ROWS;           // 1 position up, if y == 0, roll over to max.
  byte result = readPixel(whichBuffer, xRight, y);     // right
      result += readPixel(whichBuffer, xRight, yDown); // right down
      result += readPixel(whichBuffer, x,      yDown); // down
      result += readPixel(whichBuffer, xLeft,  yDown); // left down
      result += readPixel(whichBuffer, xLeft,  y);     // left
      result += readPixel(whichBuffer, xLeft,  yUp);   // left up
      result += readPixel(whichBuffer, x,      yUp);   // up
      result += readPixel(whichBuffer, xRight, yUp);   // right up  
  return byte(result);
}

void seedWorldRandom(byte whichBuffer[][SHREGISTERS])
{
  for(byte column = 0; column < COLUMNS; column++)
  {
    for(byte row = 0; row < ROWS; row++)
    {
      setPixel(whichBuffer, random(0, 2), column, row); 
    }
  }
}



