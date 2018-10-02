#include "U8glib.h"

U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8

void setup(void) {
}

void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    u8g.setContrast(100);
    u8g.drawRFrame(0, 0, 83, 47, 3); //Usar un pixel menos al maximo
    u8g.setFont(u8g_font_10x20);
    u8g.drawStr( 10, 18, "Hello"); // x, y, "String"
    u8g.drawStr( 10, 38, "World!");
    
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  //delay(50);
}
