#include <SoftwareSerial.h>

SoftwareSerial miBT(10, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("Listo");
  miBT.begin(38400);
}

void loop() {
  if (miBT.available())       //lee BT y envia a arduino
  Serial.write(miBT.read());

  if (Serial.available())
  miBT.write(Serial.read());  // Lee arduino y envia a BT
  
}
