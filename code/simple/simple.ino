#define ROWS        7  // number of rows
#define SHREGISTERS 7  // number of shiftregisters, (56 ouputs, 'last' 6 are *not* visible/don't have leds connected.)

#define DATAPIN  22  // U1 pin 32 
#define LATCHPIN 23  // U1 pin 25 (storage register clock input, used as 'latch')
#define CLOCKPIN 24  // U1 pin 24

#define ROW0PIN  A0  // U1 pin 39  
#define ROW1PIN  A1  // U1 pin 38
#define ROW2PIN  A2  // U1 pin 37
#define ROW3PIN  A3  // U1 pin 36
#define ROW4PIN  A4  // U1 pin 35
#define ROW5PIN  A5  // U1 pin 34
#define ROW6PIN  A6  // U1 pin 33

const byte rowToPin[ROWS] = 
{ 
  ROW0PIN, ROW1PIN, ROW2PIN, ROW3PIN, ROW4PIN, ROW5PIN, ROW6PIN
};

void setup() 
{   
  for(byte row = 0; row < ROWS; row++)      // row mosfets
  {
    pinMode(rowToPin[row], OUTPUT);      
    digitalWrite(rowToPin[row], HIGH);      // turn all /off/
  }

  pinMode(DATAPIN, OUTPUT);                 // shiftregister pins
  digitalWrite(DATAPIN, HIGH);              // default state
  pinMode(LATCHPIN, OUTPUT);
  digitalWrite(LATCHPIN, HIGH);       
  pinMode(CLOCKPIN, OUTPUT);
  digitalWrite(CLOCKPIN, LOW);        

  digitalWrite(LATCHPIN, LOW);              // 
  for(byte sr = 0; sr < SHREGISTERS; sr++)  // for all shiftregisters,
  {
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, B11111111);  // send a byte of data, all *off* in this case.
  }
  digitalWrite(LATCHPIN, HIGH);  

}

void loop()
{
  static byte data = B11001100;                    // some pattern
  for(byte row = 0; row < ROWS; row++)             // for each row
  {
    digitalWrite(LATCHPIN, LOW);                   
    for(byte sr = 0; sr < SHREGISTERS; sr++)       // for the number of registers
    {
      shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, data); // shift out a byte
    }
    digitalWrite(LATCHPIN, HIGH);                  
    
    digitalWrite(rowToPin[row], LOW);              // /on/ Show the pixels on this row
    delay(1000);                                   // show
    digitalWrite(rowToPin[row], HIGH);             // /off/ 
    
    data=~data;  // change data. next row is the inverse of the last. 101 -> 010
  }
  
}



