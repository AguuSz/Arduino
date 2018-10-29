#include <Time.h>

time_t  T0, T1 ;         // Contenedores de fechas

void setup()
   {    Serial.begin(115200);  }

void loop()
   {    T0 = SetFecha(2014, 11, 6, 20, 17, 0);  // 6 nov 2014  20:17
        printFecha(T0) ;
        T1 = SetFecha(2014, 11, 13, 16, 45, 0);  // 13 nov 2014 16:45
        printFecha(T1) ;
        printFecha(T1 - T0);

        Serial.println("--------------------------------------------------");
        time_t H =  T1 - T0 ;

        Serial.print(String(year(H )- 1970)+" años,"  + String(month(H)-1 )+" meses,");
        Serial.println(String(day(H))+ " dias," + String(hour(H))+ " horas");
        Serial.println("---------------------------------------------------");
   }

void printFecha(time_t  t)
   {
       Serial.print(day(t)) ;    Serial.print(+ "/") ;   Serial.print(month(t));   Serial.print(+ "/") ;
       Serial.print(year(t));    Serial.print( " ") ;
       Serial.print(hour(t));   Serial.print(+ ":") ;   Serial.print(minute(t));   Serial.print(":") ;
       Serial.println(second(t));
       delay(1000);
   }

time_t SetFecha(int y, int m, int d, int h, int mi, int s  )
   {  tmElements_t Fecha ;
      Fecha.Second = s;
      Fecha.Minute = mi;
      Fecha.Hour = h;
      Fecha.Day = d ;
      Fecha.Month = m ;
      Fecha.Year = y -1970 ;
 
      return makeTime(Fecha);
   }
