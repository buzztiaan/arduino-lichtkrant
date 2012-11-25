

void serviceFramebuffer()
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
