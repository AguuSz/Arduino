#define RST 3
#define CE 4
#define DC 5
#define DIN 6
#define CLK 7

void LcdWriteCmd(byte cmd)
{
  digitalWrite(DC, LOW); //DC pin is low for commands
  digitalWrite(CE,LOW);
  shiftOut(DIN,CLK,MSBFIRST,cmd); //Transmit serial data
  digitalWrite(CE,HIGH);
}

void setup() {

  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(RST,LOW);
  digitalWrite(RST,HIGH);

  LcdWriteCmd(0x21); //LCD extended commands
  LcdWriteCmd(0xB8); // set LCD Vop (contrast)
  LcdWriteCmd(0x04); // set temp coefficent
  LcdWriteCmd(0x14); // LCD Bias mode 1:40
  LcdWriteCmd(0x20); // LCD basic commands 
  LcdWriteCmd(0x09); // LCD all segments/pixels on

}

void loop() {
  // put your main code here, to run repeatedly:

}
