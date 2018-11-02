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
boolean opcion = true;
char incomingChar;


boolean newData = false;

U8GLIB_PCD8544 u8g(CLK, DIN, CE, DC, RST); //Pines a usar

void setup() {
  Serial.begin(9600);
  Serial.println("Esperando mensaje de sincronizacion");
  u8g.setContrast(110);
  miBT.begin(38400);
  pantallaCarga();
  bienvenida();
}

void loop() {

  if (miBT.available() > 0) {
    analizarInfo();
  }
  if (timeStatus() != timeSet and opcion = true ) {

    u8g.firstPage();
    do {
      mostrarBateria();

      u8g.setFont(u8g_font_courB08);
      u8g.setPrintPos(30, 14);
      u8g.print("Hora");
      u8g.setPrintPos(32, 24);
      u8g.print("sin");
      u8g.setPrintPos(10, 34);
      u8g.print("Sincronizar");

    } while (u8g.nextPage());

  } else {

    u8g.firstPage();
    do {
      opcion = false;
      u8g.drawRFrame(0, 0, 84, 48, 3);
      u8g.setFont(u8g_font_courB10);

      mostrarBateria();

      // Hora

      u8g.setFont(u8g_font_courB10);
      u8g.setPrintPos(45, 25); // Minutos
      u8g.print(minute());
      u8g.setPrintPos(37, 25);
      u8g.print(":");

      u8g.setPrintPos(20, 25); // Hora
      u8g.print(hour());


      // Fecha y separador
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
  delay(6000);
}

void bienvenida() {
  u8g.firstPage();
  do {
    mostrarBateria();

    u8g.setFont(u8g_font_7x14);
    u8g.setPrintPos(30, 20);
    u8g.print("Sea");
    u8g.setPrintPos(5, 35);
    u8g.print("bienvenido!");
  } while (u8g.nextPage());
  delay(4000);
}

void analizarInfo() {
  incomingChar = miBT.read();
  Serial.print(incomingChar);
  if (incomingChar == 'w') {
    u8g.firstPage();
    do {
      mostrarBateria();
      u8g.drawRFrame(0, 0, 84, 48, 3);
      u8g.setFont(u8g_font_6x12);
      u8g.setPrintPos(3, 20);
      u8g.print("Nuevo msj de");
      u8g.setPrintPos(3, 35);
      u8g.print("Whatsapp");
    } while (u8g.nextPage());
    delay(3000);
  }

  if (incomingChar == 'i') {      // USAR SIEMPRE '' Y NUNCA "" PORQUE NO VA A FUNCIONAR
    u8g.firstPage();
    do {
      mostrarBateria();
      u8g.drawRFrame(0, 0, 84, 48, 3);
      mostrarBateria();
      u8g.setFont(u8g_font_6x12);
      u8g.setPrintPos(3, 20);
      u8g.print("Nuevo msj de");
      u8g.setPrintPos(3, 35);
      u8g.print("Instagram");
    } while (u8g.nextPage());
    delay(3000);
  }

void mostrarBateria() {
  // Bateria //

  u8g.drawRFrame(0, 0, 20, 9, 3); // Frame de la bateria
  u8g.setFont(u8g_font_4x6);
  u8g.setPrintPos(2, 7);
  u8g.print("100%");
}
