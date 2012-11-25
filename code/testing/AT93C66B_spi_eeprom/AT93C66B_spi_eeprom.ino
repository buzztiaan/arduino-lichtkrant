// all pins, except pin 6, are externally pulled high by 1K resistors.
#define MISOPIN A9  // input of the eeprom.
#define MOSIPIN  A10  // output from eeprom, INPUT
#define CLOCKPIN      A11  // default LOW
#define CHIPSELECTPIN A12  // default LOW
// pin 6, ORG, of the device is tied to ground.
// the 512 words x 8 bits organisation is selected.

// 2MHz clock rate (5V)

// Op Codes
#define STARTBIT B1 
#define READ  B10 // + 1 byte address. Reads 8bits data stored in memory at specified address
#define ERASE B11 // + 1 byte address. Sets all 8 bits at specified address to 1, logical one.
#define WRITE B01 // + 1 byte address + 1 byte data. Writes memory location.

#define EXTEND B00
#define EWEN   B11XXXXXX        // x, value don't care but clocked.
#define ERAL   B10XXXXXX 
#define WRAL   B01XXXXXX // + 8 bits of data
#define EWDS   B00XXXXXX

//#define STARTBITSIZE   1             // single bit
#define COMMANDSIZE    2             // 2 bits
#define EXTCOMMANDSIZE 8             // 8 bits


void setup()
{
  initPins();
  
  delay(1000);
  Serial.begin(115200);
  Serial.println("Hi There.");
  

  for(int addr=0; addr < 512; addr+=16)
  {
    Serial.write(readByte(addr));      //Serial.print(", ");
    Serial.write(readByte(addr+1));   // Serial.print(", ");
    Serial.write(readByte(addr+2));      //Serial.print(", ");
    Serial.write(readByte(addr+3));   // Serial.print(", ");
    Serial.write(readByte(addr+4));      //Serial.print(", ");
    Serial.write(readByte(addr+5));   // Serial.print(", ");
    Serial.write(readByte(addr+6));      //Serial.print(", ");
    Serial.write(readByte(addr+7));   // Serial.print(", ");
    Serial.write(readByte(addr+8));      //Serial.print(", ");
    Serial.write(readByte(addr+9));   // Serial.print(", ");
    Serial.write(readByte(addr+10));      //Serial.print(", ");
    Serial.write(readByte(addr+11));   // Serial.print(", ");
    Serial.write(readByte(addr+12));      //Serial.print(", ");
    Serial.write(readByte(addr+13));   // Serial.print(", ");
    Serial.write(readByte(addr+14));      //Serial.print(", ");
    Serial.write(readByte(addr+15));   // Serial.print(", ");
    Serial.println();
  }
  
  
  
}

void loop()
{
}
