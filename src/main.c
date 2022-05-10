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
         for (i=0; i<2; i++) { // Bucle para detectar obstaculo 2 veces
         printf(lcd_putc,"Palante            ");
         lcd_gotoxy(iniciox,inicioy);
         motores_palante();
         while (input(PIN_BUMPER)) { // Lee el pin del bumper y del sensor infrarojo, y si detecta algo sigue el programa
            // if (input(PIN_INF)) {
            //    break;
            // }
         }
         printf(lcd_putc, "Obstaculo detectado");
         lcd_gotoxy(iniciox,inicioy);
         motores_parar();
         motores_patras();
         delay_ms(1000);
         motores_paderecha();
         delay_ms(5000);
         }
   }
   
   while(1) {usb_task();}
}
