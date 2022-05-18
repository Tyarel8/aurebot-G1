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

// Inicio del display, usando la funcion lcd_gotoxy(iniciox,inicioy) se mueve el cursor al inicio
#define iniciox 0b1
#define inicioy 0b1

// Pines para la lectura de los diferentes dispositivos
#define PIN_BUMPER PIN_A0
#define PIN_INF PIN_A1
#define PIN_LED PIN_A3


// Rutina de gesti�n de pulsaciones serie
void aure_serie()
{
   output_toggle(LED);
   switch(keypress)
   {
//Control de movimiento
            case 'w':
               motores_palante();
               break;
            case 'W':
               motores_palante();
               break;
            case 's':
               motores_patras();
               break;
            case 'S':
               motores_patras();
               break;
            case 'd':
               motores_paderecha();
               break;
            case 'D':
               motores_paderecha();
               break;
            case 'a':
               motores_paizda();
               break;
            case 'A':
               motores_paizda();
               break;
            case 'q':
               motores_parar();
               break;
            case 'Q':
               motores_parar();
               break;               
            default:
               printf (usb_cdc_putc, "NR:%c\r\n", keypress);
               break;
   }
   //Vaciamos el buffer
   keypress=0;
}

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

//Rutina principal
void main()
{
   // Inicializacion de los dispositivos
   aure_configurar();
   lcd_init();
   lcd_configurar();
   aure_configurar_usb_sinespera();
   
   for(int i=0; i<50; i++)
   {
     delay_ms(100);
     if(input(PULSADOR))i=100;
   }
   
   if (aure_configurar_usb_comprobar()==1) 
   {
   
      // Si esta conectado
         while (!input(PULSADOR)) {aure_usb();} //Esperamos hasta que se pulse el pulsador 
         aure_usb();
         while (1) {aure_usb();}
   } else {
      // Si no esta conectado   
         while (!input(PULSADOR)) {} //Esperamos hasta que se pulse el pulsador

         //configuracion del timer
         // set_tris_b(0x00);  //0b00000000 
         // setup_timer_0(RTCC_INTERNAL | RTCC_DIV_8);
         // set_timer0(tmr0); //50ms : TMR0=65536 - overflow_time/(4*Tosc*prescaler)=53036 [in this case overflow_time=50ms, Tosc=1/8MHz=125ns, prescaler=8]
         //since TMR0=53036 -> overflow_time=(65536-TMR0)*(4*Tosc*prescaler)=(65536-53036)*(4*125ns*8)=50ms
         // enable_interrupts(INT_TIMER0);
         // enable_interrupts(GLOBAL);
         //********************************************
         
         // int start = current_time();
         for (int t=0; t<1; t++) { // Bucle para detectar obstaculo 2 veces
         printf(lcd_putc,"Palante            ");
         lcd_gotoxy(iniciox,inicioy);
         motores_palante();
         int16 ms_counter = 0;
         while (input(PIN_BUMPER)) { // Lee el pin del bumper y del sensor infrarojo, y si detecta algo sigue el programa
            // if (input(PIN_INF)) {
            //    break;
            // }
            // Aproximacion cutre de cuanto tiempo ha pasado asumeindo que lo que tarde en leer los pines es mucho menor de 10ms
            delay_ms(10);
            ms_counter++;
         }
         // int elapsed_time = current_time() - start;
         printf(lcd_putc,"                   ");
         lcd_gotoxy(iniciox,inicioy);
         printf(lcd_putc, "%f", (float)ms_counter/100);
         lcd_gotoxy(iniciox,inicioy);
         motores_parar();
         motores_patras();
         delay_ms(1000);
         motores_paderecha();
         delay_ms(5000);
         motores_parar();

         char length_string[100];
         sprintf(length_string, "AUREBOT ha recorrido %.2f metros", (float)ms_counter/100); // Crear variable con el mensaje para traducir a morse
         char morse[150];
         str_to_morse(length_string, morse); // Funcion convierte un string en morse (hola mundo -> ..../---/.-../.-/ --/..-/-./-../---)
         printf(lcd_putc, "%s", length_string);
         lcd_gotoxy(iniciox,inicioy);
         int unit = 100; // Unidad morse
         for (int p=0;p<strlen(morse);p++) {
            if (morse[p] == '.') { // Punto = 1 unidad
               output_toggle(PIN_LED);
               delay_ms(unit);
               output_toggle(PIN_LED);
            } else if (morse[p] == '-') { // Raya = 3 unidades
               output_toggle(PIN_LED);
               delay_ms(3*unit);
               output_toggle(PIN_LED);
            } else if (morse[p] == '/') { // Pausa entre letras = 3 unidades
               delay_ms(unit*2);
            } else if (morse[p] == ' ') { // Pausa entre palabras = 7 unidades
               delay_ms(unit*4);
            }
            delay_ms(unit); // Pausa entre puntos y rayas = 1 unidad
         }
         }
         motores_parar();
   }
   
   while(1) {usb_task();}
}
