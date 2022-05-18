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

// Pines para la lectura de los diferentes dispositivos
#define PIN_BUMPER PIN_A0
#define PIN_INF PIN_A1
#define PIN_LED PIN_A3
// --------------------------------------------------

// * ---------------- timer ---------------- (no funciona)
#define tmr0 53036  //50ms with a 8MHz clock
#INT_TIMER0
static int counter = 0;

int current_time() {
   return counter*50;
}

void TIMER0()
{       
    set_timer0(tmr0);   //reload timer register
    if(counter++ == 0)
    {
        //1 sec.
    }
}
// * ---------------------------------------

void clear_lcd() { // Pone todos los caracteres del display como espacios
   lcd_gotoxy(iniciox, inicioy);
   printf(lcd_putc,"               ");
   lcd_gotoxy(iniciox, 2);
   printf(lcd_putc,"               ");
   lcd_gotoxy(iniciox, inicioy);
}

//Rutina principal
void main() {
   // Inicializacion de los dispositivos
   aure_configurar();
   lcd_init();
   lcd_configurar();
   aure_configurar_usb_sinespera();
   
   for(int i=0; i<50; i++) {
     delay_ms(100);
     if(input(PULSADOR))i=100;
   }
   
   while (!input(PULSADOR)) {} //Esperamos hasta que se pulse el pulsador

   // ---------------- timer ----------------
   // set_tris_b(0x00);  //0b00000000 
   // setup_timer_0(RTCC_INTERNAL | RTCC_DIV_8);
   // set_timer0(tmr0); //50ms : TMR0=65536 - overflow_time/(4*Tosc*prescaler)=53036 [in this case overflow_time=50ms, Tosc=1/8MHz=125ns, prescaler=8]
   //since TMR0=53036 -> overflow_time=(65536-TMR0)*(4*Tosc*prescaler)=(65536-53036)*(4*125ns*8)=50ms
   // enable_interrupts(INT_TIMER0);
   // enable_interrupts(GLOBAL);
   // ---------------------------------------
   
   // int start = current_time();
   // ! Cambiar bucle a 2 iteraciones cuando funcione el infrarrojo
   for (int t=0; t<1; t++) { // Bucle para detectar obstaculo 2 veces
      clear_lcd();
      printf(lcd_putc,"Palante");
      motores_palante();
      int16 ms_counter = 0; // Inicializando el contador de tiempo con un entero de 16 bits
      while (input(PIN_BUMPER)) { // Lee el pin del bumper y del sensor infrarojo, y si detecta algo sigue el programa
         // if (input(PIN_INF)) {
         //    break;
         // }
         // Aproximacion cutre de cuanto tiempo ha pasado asumiendo que lo que tarda en leer los pines es mucho menor de 10ms
         delay_ms(10);
         ms_counter++; // Añadimos 1 al contador, que se representa 10ms
      }
      // int elapsed_time = current_time() - start;
      clear_lcd();
      printf(lcd_putc,"Obstáculo", ms_counter);
      lcd_gotoxy(iniciox, 2);
      printf(lcd_putc, "%fs", (float)ms_counter/100);
      motores_parar();
      motores_patras(); // Retroceder para no chocar al girar
      delay_ms(1000);
      motores_paderecha();
      // ! Falta ajustar tiempo de giro
      delay_ms(5000); // Tiempo para hacer un giro de 180º
      motores_parar();
   }
   motores_parar();

   // ---------------- Morse ----------------
   char final_message[100];
   char morse[150];
   // ! Falta calcular la velocidad y convertir el tiempo en distancia
   sprintf(final_message, "AUREBOT ha recorrido %.2f metros", (float)ms_counter/100); // Crear variable con el mensaje para traducir a morse
   str_to_morse(final_message, morse); // Funcion convierte un string en morse (hola mundo -> ..../---/.-../.-/ --/..-/-./-../---)
   clear_lcd();
   printf(lcd_putc, "%.2f metros", (float)ms_counter/100));
   int unit = 100; // Unidad morse en milisegundos
   for (int p=0;p<strlen(morse);p++) {
      // Bucle para traducir las rayas y puntos a encender y apagar un LED
      if (morse[p] == '.') { // Punto = 1 unidad
         output_toggle(PIN_LED);
         delay_ms(unit);
         output_toggle(PIN_LED);
      } 
      else if (morse[p] == '-') { // Raya = 3 unidades
         output_toggle(PIN_LED);
         delay_ms(3*unit);
         output_toggle(PIN_LED);
      } 
      else if (morse[p] == '/') { // Pausa entre letras = 3 unidades
         delay_ms(unit*2);
      } 
      else if (morse[p] == ' ') { // Pausa entre palabras = 7 unidades
         delay_ms(unit*4);
      }
      delay_ms(unit); // Pausa entre puntos y rayas = 1 unidad
   }
   // ---------------------------------------
   
   while(1) {usb_task();}
}
