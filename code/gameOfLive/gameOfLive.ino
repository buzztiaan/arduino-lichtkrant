#include <frames.h>
#include <lichtkrant.h>

#define ALIVE 1
#define DEAD  0

extern byte frameBuffer[ROWS][SHREGISTERS];
byte temp[ROWS][SHREGISTERS];

#define MILLISPERGENERATION 500UL

void setup()
{
  Serial.begin(115200);
  Serial.println("Hi there.");

  initHardware();

  // randomSeed(analogRead(A15)); // floating pin. random enough
  // seedWorldRandom(frameBuffer);


  // LightWeightSpaceShip - blockInCorners - assortyStructs - 
  // nerds - ehVertical - gliders - Rpentomino - Diehard -
  // acorn - nerdsOpen - nerdz - 
  bufferCopy(assortyStructs, frameBuffer);

}

void loop()
{
  serviceFramebuffer();


  unsigned long currentMillis = millis();
  static long prevGenMillis = 0L;
  if(currentMillis - prevGenMillis > MILLISPERGENERATION) 
  {
    prevGenMillis=currentMillis;
    for(byte row = 0; row < ROWS; row++)
    {
      for(byte column = 0; column < COLUMNS; column++)
      {
        setPixel(temp, DEAD, column, row);     // make sure of DEAD/empty target cell.
        byte cellAlive = readPixel(frameBuffer, column, row);
        byte neighbours = countNeigbours(frameBuffer, column, row);
        if(cellAlive==ALIVE)            // Any live cell ...
        {
          if(neighbours < 2)                    // with fewer than two live neighbours ... 
          {
            setPixel(temp, DEAD, column, row);  // dies, as if caused by under-population.
          }
          else if(neighbours < 4)               // with two or three live neighbours ... 
          {
            setPixel(temp, ALIVE, column, row); // lives on to the next generation.
          }
          else if(neighbours > 3)               // with more than three live neighbours ... 
          {
            setPixel(temp, DEAD, column, row);  // dies, as if by overcrowding.
          }
        }
        else                            // Any dead cell 
        { 
          if(neighbours == 3)                   // with exactly three live neighbours 
          {
            setPixel(temp, ALIVE, column, row); //becomes a live cell, as if by reproduction.
          }
        }
        serviceFramebuffer();
      }
    }

    bufferCopy(temp, frameBuffer);
  }
}














