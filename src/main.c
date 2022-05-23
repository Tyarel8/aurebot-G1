/*
    ___                   __          __     ______                          ___
   /   | __  __________  / /_  ____  / /_   / ____/______  ______  ____     <  /
  / /| |/ / / / ___/ _ \/ __ \/ __ \/ __/  / / __/ ___/ / / / __ \/ __ \    / /
 / ___ / /_/ / /  /  __/ /_/ / /_/ / /_   / /_/ / /  / /_/ / /_/ / /_/ /   / /
/_/  |_\__,_/_/   \___/_.___/\____/\__/   \____/_/   \__,_/ .___/\____/   /_/
                                                         /_/
*/

#include <../lib/aurebot.h>
#include <../lib/motores.h>
#include <../lib/flex_lcd.c>

/*#include <../lib/ldr.h>
#include <../lib/cny70.h>
#include <../lib/bumper.h>
#include <../lib/sonido.h>
#include <../lib/2leds.h>*/

#include "morse.h"

// Inicio del display, usando la funcion lcd_gotoxy(iniciox,inicioy) se mueve el cursor al inicio de la primera línea
#define iniciox 0b1
#define inicioy 0b1

// Velocidad del aurebot de metros por segundo
#define velocidad_aurebot 0.06289

// Pines para la lectura de los diferentes dispositivos
#define PIN_BUMPER PIN_A0
#define PIN_INF PIN_A5
#define PIN_LED PIN_A3
#define PIN_BUZZER PIN_A1
#define PIN_MANDO PIN_E1
// --------------------------------------------------

void clear_lcd()
{ // Pone todos los caracteres del display como espacios
   lcd_gotoxy(iniciox, inicioy);
   printf(lcd_putc, "               ");
   lcd_gotoxy(iniciox, 2);
   printf(lcd_putc, "               ");
   lcd_gotoxy(iniciox, inicioy);
}

void buzz(int t, int f) // Hace funcionar el buzzer con el tiempo y la frecuencia como paramtros
{
   float periodo2 = 1000 / (f * 2); // La mitad del periodo para hacer el delay
   int32 counter = 0;
   while (counter < t)
   {
      output_high(PIN_BUZZER);
      delay_ms((int)periodo2);
      output_low(PIN_BUZZER);
      delay_ms((int)periodo2);
      counter += (int)periodo2 * 2;
   }
}

// Rutina principal
void main()
{
   // Inicializacion de los dispositivos
   aure_configurar();
   lcd_init();
   lcd_configurar();
   aure_configurar_usb_sinespera();

   while (!input(PULSADOR))
   { // Esperamos hasta que se pulse el pulsador o se active el mando
      if (!input(PIN_MANDO))
      {
         for (int z = 0; z < 5; z++)
         { // Si se enciende por el mando parpadea el LED
            output_high(PIN_LED);
            delay_ms(100);
            output_low(PIN_LED);
            delay_ms(100);
         }
         break;
      }
      delay_ms(10); // Sin el delay a veces se enciende solo como si se hubiera activado el mando
   }

   // int start = current_time();
   int16 ms_counter = 0; // Inicializando el contador de tiempo con un entero de 16 bits
   // ! Cambiar bucle a 2 iteraciones cuando funcione el infrarrojo
   for (int t = 0; t < 1; t++)
   { // Bucle para detectar obstaculo 2 veces
      clear_lcd();
      printf(lcd_putc, "Palante");
      motores_palante();
      while (input(PIN_BUMPER))
      { // Lee el pin del bumper y del sensor infrarojo, y si detecta algo sigue el programa
         if (input(PIN_INF))
         {
            break;
         }
         // Aproximacion cutre de cuanto tiempo ha pasado asumiendo que lo que tarda en leer los pines es mucho menor de 10ms
         delay_ms(10);
         ms_counter++; // Añadimos 1 al contador, que se representa 10ms
      }
      // int elapsed_time = current_time() - start;
      clear_lcd();
      printf(lcd_putc, "Obstaculo");
      lcd_gotoxy(iniciox, 2);
      printf(lcd_putc, "%fs", (float)ms_counter / 100);
      motores_parar();
      motores_patras(); // Retroceder para no chocar al girar
      delay_ms(1000);
      motores_paderecha();
      delay_ms(6900); // Tiempo para hacer un giro de 180º
      motores_parar();
   }
   motores_parar();

   // ---------------- Morse ----------------
   char final_message[100];
   char morse[150];
   sprintf(final_message, "AUREBOT ha recorrido %.2f metros", (float)ms_counter / 100 * velocidad_aurebot); // Crear variable con el mensaje para traducir a morse
   str_to_morse(final_message, morse);                                                                      // Funcion convierte un string en morse (hola mundo -> ..../---/.-../.-/ --/..-/-./-../---)
   clear_lcd();
   printf(lcd_putc, "%.2f metros", (float)ms_counter / 100 * velocidad_aurebot);
   int unit = 150; // Unidad morse en milisegundos
   for (int p = 0; p < strlen(morse); p++)
   {
      // Bucle para traducir las rayas y puntos a encender y apagar un LED
      if (morse[p] == '.')
      { // Punto = 1 unidad
         output_high(PIN_LED);
         // delay_ms(unit);
         buzz(unit, 1000);
         output_low(PIN_LED);
      }
      else if (morse[p] == '-')
      { // Raya = 3 unidades
         output_high(PIN_LED);
         // delay_ms(3 * unit);
         buzz(unit * 3, 1000);
         output_low(PIN_LED);
      }
      else if (morse[p] == '/')
      { // Pausa entre letras = 3 unidades
         delay_ms(unit * 2);
      }
      else if (morse[p] == ' ')
      { // Pausa entre palabras = 7 unidades
         delay_ms(unit * 4);
      }
      delay_ms(unit); // Pausa entre puntos y rayas = 1 unidad
   }
   // ---------------------------------------

   while (1)
   {
      usb_task();
   }
}