#include "U8glib.h"

#define RST 8
#define DC 9
#define CE 10
#define DIN 11
#define CLK 13

U8GLIB_PCD8544 u8g(CLK, DIN, CE, DC, RST); //Pines a usar 

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  static unsigned numero = 0;
  
  u8g.firstPage();
  do {
    u8g.setContrast(100);
    u8g.drawRFrame(0, 0, 84, 48, 3);
    u8g.setFont(u8g_font_profont29);
    u8g.setPrintPos(15, 27); // 35 queda centrado aprox
    u8g.print(numero);

    
  } while (u8g.nextPage());

  numero = numero + 1;

  if (numero == 10) {
    
  }
  delay(1000);

}
