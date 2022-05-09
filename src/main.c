/*
          _____                    _____                    _____                    _____
         /\    \                  /\    \                  /\    \                  /\    \
        /::\    \                /::\____\                /::\    \                /::\    \
       /::::\    \              /:::/    /               /::::\    \              /::::\    \
      /::::::\    \            /:::/    /               /::::::\    \            /::::::\    \
     /:::/\:::\    \          /:::/    /               /:::/\:::\    \          /:::/\:::\    \
    /:::/__\:::\    \        /:::/    /               /:::/__\:::\    \        /:::/__\:::\    \
   /::::\   \:::\    \      /:::/    /               /::::\   \:::\    \      /::::\   \:::\    \
  /::::::\   \:::\    \    /:::/    /      _____    /::::::\   \:::\    \    /::::::\   \:::\    \
 /:::/\:::\   \:::\    \  /:::/____/      /\    \  /:::/\:::\   \:::\____\  /:::/\:::\   \:::\    \
/:::/  \:::\   \:::\____\|:::|    /      /::\____\/:::/  \:::\   \:::|    |/:::/__\:::\   \:::\____\
\::/    \:::\  /:::/    /|:::|____\     /:::/    /\::/   |::::\  /:::|____|\:::\   \:::\   \::/    /
 \/____/ \:::\/:::/    /  \:::\    \   /:::/    /  \/____|:::::\/:::/    /  \:::\   \:::\   \/____/
          \::::::/    /    \:::\    \ /:::/    /         |:::::::::/    /    \:::\   \:::\    \
           \::::/    /      \:::\    /:::/    /          |::|\::::/    /      \:::\   \:::\____\
           /:::/    /        \:::\__/:::/    /           |::| \::/____/        \:::\   \::/    /
          /:::/    /          \::::::::/    /            |::|  ~|               \:::\   \/____/
         /:::/    /            \::::::/    /             |::|   |                \:::\    \
        /:::/    /              \::::/    /              \::|   |                 \:::\____\
        \::/    /                \::/____/                \:|   |                  \::/    /
         \/____/                  ~~                       \|___|                   \/____/

   Programa de ejemplo para la AureBoard
   Requerido: Aureboard Versi�n>2.0

   - El programa configura el puerto Serie por USB.
   - Cada programa deber� ir en su carpeta al mismo nivel de la carpeta lib




   A.U.R.E. 2010
*/

#include <../lib/aurebot.h>
#include <../lib/motores.h>
#include <../lib/flex_lcd.c>

/*#include <../lib/ldr.h>
#include <../lib/cny70.h>
#include <../lib/bumper.h>
#include <../lib/sonido.h>
#include <../lib/2leds.h>*/

#define iniciox 0b1
#define inicioy 0b1

#define PIN_BUMPER PIN_A0
#define PIN_INF PIN_A1

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



//Rutina principal
void main()
{
   int i, d, j, k;
   aure_configurar();
   lcd_init();
   lcd_configurar();
   aure_configurar_usb_sinespera();
   
   for(i=0; i<50; i++)
   {
     delay_ms(100);
     if(input(PULSADOR))i=100;
   }
   
   if (aure_configurar_usb_comprobar()==1) 
   {
   
      // Si est� conectado
         while (!input(PULSADOR)) {aure_usb();} //Esperamos hasta que se pulse el pulsador 
         aure_usb();
         while (1) {aure_usb();}
   } else {
      // Si no est� conectado   
         while (!input(PULSADOR)) {} //Esperamos hasta que se pulse el pulsador 
         for (i=0; i<2; i++) {
         printf(lcd_putc,"Palante            ");
         lcd_gotoxy(iniciox,inicioy);
         motores_palante();
         while (input(PIN_BUMPER)) {
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
