#include "U8glib.h"
#include <TimeLib.h>
#include <SoftwareSerial.h>

SoftwareSerial miBT(10, 11);

#define RST 3
#define CE 4
#define DC 5
#define DIN 6
#define CLK 7
#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message
byte opcion = 0;
char incomingData;

U8GLIB_PCD8544 u8g(CLK, DIN, CE, DC, RST); //Pines a usar

void setup() {
  Serial.begin(9600);
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Esperando mensaje de sincronizacion");
  u8g.setContrast(110);
  miBT.begin(38400);
  pantallaCarga();
  bienvenida();
}

void loop() {

  if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus() != timeSet and opcion == 0) {

    u8g.firstPage();
    do {
      // BATERIA //

      u8g.drawRFrame(0, 0, 20, 10, 3); // Frame de bateria
      u8g.setFont(u8g_font_4x6);
      u8g.setPrintPos(2, 7);
      u8g.print("100%");

      u8g.setFont(u8g_font_courB08);
      u8g.setPrintPos(32, 24);
      u8g.print("Sin");
      u8g.setPrintPos(10, 34);
      u8g.print("Sincronizar");



    } while (u8g.nextPage());


  } else {

    u8g.firstPage();
    do {
      opcion = 1;
      u8g.drawRFrame(0, 0, 84, 48, 3);
      u8g.setFont(u8g_font_courB10);

      // BATERIA //

      u8g.drawRFrame(0, 0, 20, 10, 3); // Frame de bateria
      u8g.setFont(u8g_font_4x6);
      u8g.setPrintPos(2, 7);
      u8g.print("100%");;

      // HORA

      u8g.setFont(u8g_font_courB10);
      u8g.setPrintPos(45, 25); // Minutos
      u8g.print(minute());
      u8g.setPrintPos(37, 25);
      u8g.print(":");

      u8g.setPrintPos(20, 25); // Hora
      u8g.print(hour());


      // FECHA Y LINEA SEPARADORA
      u8g.setFont(u8g_font_5x7);
      u8g.setPrintPos(10, 36);
      u8g.print("-------------");
      u8g.setPrintPos(19, 43);
      u8g.print(day());
      u8g.setPrintPos(30, 43);
      u8g.print("/");
      u8g.setPrintPos(35, 43);
      u8g.print(month());
      u8g.setPrintPos(46, 43);
      u8g.print("/");
      u8g.setPrintPos(51, 43);
      u8g.print(year());
    } while (u8g.nextPage());
  }
}

void pantallaCarga() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_6x12);
    u8g.setPrintPos(5, 20);
    u8g.print("CleverClock");
    u8g.setPrintPos(5, 35);
    u8g.print("Iniciando...");
  } while (u8g.nextPage());
  delay(8000);
}

void bienvenida() {
  u8g.firstPage();
  do {
    // BATERIA //

    u8g.drawRFrame(0, 0, 20, 10, 3); // Frame de bateria
    u8g.setFont(u8g_font_4x6);
    u8g.setPrintPos(2, 7);
    u8g.print("100%");

    u8g.setFont(u8g_font_7x14);
    u8g.setPrintPos(30, 20);
    u8g.print("Sea");
    u8g.setPrintPos(5, 35);
    u8g.print("bienvenido!");
  } while (u8g.nextPage());
  delay(5000);
}

void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if (Serial.find(TIME_HEADER)) {
    pctime = Serial.parseInt();
    if ( pctime >= DEFAULT_TIME) { // Valida si el valor es valido (mayor a el 1 de enero de 2013)
      setTime(pctime); // Sincroniza el reloj de arduino al valor recibido por el puerto serial
    }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);
  return 0; // El mensaje va a ser enviado luego en respuesta como un mensaje serial
}
