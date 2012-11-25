byte readByte(int address)
{
  byte data = 0;
  digitalWrite(MOSIPIN, HIGH);        // 1 set startbit     
  digitalWrite(CHIPSELECTPIN, HIGH);
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);        // startbit clocked out

  digitalWrite(MOSIPIN, HIGH);        // 1
  digitalWrite(CLOCKPIN, HIGH);       // first bit of opcode 
  digitalWrite(CLOCKPIN, LOW);

  digitalWrite(MOSIPIN, LOW);         // 0 
  digitalWrite(CLOCKPIN, HIGH);       // second bit of opcode 
  digitalWrite(CLOCKPIN, LOW);        //

  digitalWrite(MOSIPIN, bitRead(address, 8));   // MSB of address
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);        
  
  digitalWrite(MOSIPIN, bitRead(address, 7));
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);
  
  digitalWrite(MOSIPIN, bitRead(address, 6));
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);
  
  digitalWrite(MOSIPIN, bitRead(address, 5));
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);
  
  digitalWrite(MOSIPIN, bitRead(address, 4));
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);
  
  digitalWrite(MOSIPIN, bitRead(address, 3));
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);
  
  digitalWrite(MOSIPIN, bitRead(address, 2));
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);
  
  digitalWrite(MOSIPIN, bitRead(address, 1));
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);
  
  digitalWrite(MOSIPIN, bitRead(address, 0));      // LSB of address
  digitalWrite(CLOCKPIN, HIGH);
  digitalWrite(CLOCKPIN, LOW);

  digitalWrite(CLOCKPIN, HIGH);
  bitWrite(data, 7, digitalRead(MISOPIN)); // MSB of data
  digitalWrite(CLOCKPIN, LOW);
  digitalWrite(CLOCKPIN, HIGH);
  bitWrite(data, 6, digitalRead(MISOPIN));
  digitalWrite(CLOCKPIN, LOW);
  digitalWrite(CLOCKPIN, HIGH);
  bitWrite(data, 5, digitalRead(MISOPIN));
  digitalWrite(CLOCKPIN, LOW);
  digitalWrite(CLOCKPIN, HIGH);
  bitWrite(data, 4, digitalRead(MISOPIN));
  digitalWrite(CLOCKPIN, LOW);
  digitalWrite(CLOCKPIN, HIGH);
  bitWrite(data, 3, digitalRead(MISOPIN));
  digitalWrite(CLOCKPIN, LOW);
  digitalWrite(CLOCKPIN, HIGH);
  bitWrite(data, 2, digitalRead(MISOPIN));
  digitalWrite(CLOCKPIN, LOW);
  digitalWrite(CLOCKPIN, HIGH);
  bitWrite(data, 1, digitalRead(MISOPIN));
  digitalWrite(CLOCKPIN, LOW);
  digitalWrite(CLOCKPIN, HIGH);
  bitWrite(data, 0, digitalRead(MISOPIN));  // LSB of data
  digitalWrite(CLOCKPIN, LOW);
  
  digitalWrite(CHIPSELECTPIN, LOW);  
  
  return data;
}

void initPins()
{
  pinMode(MOSIPIN, OUTPUT);    // input of the eeprom.
  digitalWrite(MOSIPIN, HIGH);
  pinMode(MISO, INPUT);      // output from eeprom
  pinMode(CLOCKPIN, OUTPUT);   
  digitalWrite(CLOCKPIN, LOW);       // default LOW
  pinMode(CHIPSELECTPIN, OUTPUT);
  digitalWrite(CHIPSELECTPIN, LOW);     // default LOW
}

