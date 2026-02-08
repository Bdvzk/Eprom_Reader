/*
Vpp = 5V
A0 - A14 =	Pin 22-36
Q0-Q7 = Pin 37-44
CE = Pin 10
OE = Pin 11
VCC = 5V
VSS = GND
Tested on 27C256-15
note: some EPROMs may have a different voltage!!!
*/
const int CE = 10;
const int OE = 11;
const int addrPins[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
const int dataPins[] = {37, 38, 39, 40, 41, 42, 43, 44};

void setup() {
 
  SerialUSB.begin(115200);
  while (!SerialUSB) {
    ; 
  }
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  digitalWrite(CE, HIGH);
  digitalWrite(OE, HIGH);

  for (int i = 0; i < 15; i++) pinMode(addrPins[i], OUTPUT);
  for (int i = 0; i < 8; i++) pinMode(dataPins[i], INPUT);
}

void setAddress(unsigned int addr) {
  for (int i = 0; i < 15; i++) {
    digitalWrite(addrPins[i], (addr >> i) & 1);
  }
}

void dumpEPROM() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(CE, LOW);
  for (unsigned int addr = 0; addr <= 0x7FFF; addr++) {
    setAddress(addr);
    digitalWrite(OE, LOW);
    delayMicroseconds(5); 
    
    byte data = 0;
    for (int i = 0; i < 8; i++) {
      if (digitalRead(dataPins[i])) data |= (1 << i);
    }
    
    SerialUSB.write(data); 
    digitalWrite(OE, HIGH);
  }
  digitalWrite(CE, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if (SerialUSB.available() > 0) {
    char c = SerialUSB.read();
    if (c == 'R' || c == 'r') {
      dumpEPROM();
    }
  }
}
