#include <lichtkrant.h>
#include <frames.h>

extern byte frameBuffer[ROWS][SHREGISTERS];

#define MILLISPERFRAME 500UL

void setup()
{
  Serial.begin(115200);
  Serial.println("Hi there.");

  initHardware();

  // LightWeightSpaceShip - blockInCorners - assortyStructs - 
  // nerds - ehVertical - gliders - Rpentomino - Diehard -
  // acorn - nerdsOpen - nerdz - 
  bufferCopy(assortyStructs, frameBuffer);

}

void loop()
{
  serviceFramebuffer();

  unsigned long currentMillis = millis();
  static long prevFrameMillis = 0L;
  if(currentMillis - prevFrameMillis > MILLISPERFRAME) 
  {
    prevFrameMillis=currentMillis;

    // inverse picture by reading each pixel from buffer
    for(byte row = 0; row < ROWS; row++)
    {
      for(byte column = 0; column < COLUMNS; column++)
      {
        boolean state = readPixel(frameBuffer, column, row);
        setPixel(frameBuffer, !state, column, row);
      }
    }
  }
}
