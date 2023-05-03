#include <18F4550.h>
#FUSES NOWDT                 //No Watch Dog Timer
#FUSES INTRC_IO              //OSCILADOR INTERNO SIN SALIDA DE CLOCK OUT
#FUSES NOPUT                 //No Power Up Timer
#FUSES NOMCLR                //Master Clear pin Un-enabled
#FUSES PROTECT               //Code not protected from reading
#FUSES CPD                   //No EE protection
#FUSES NOBROWNOUT            //Reset when brownout detected
#FUSES NOLVP                 //No Low Voltage Programming
#FUSES NODEBUG               //No Debug mode for ICD

#use delay (clock=8000000)

//#define OSC_8MHZ    0x70    // no es necesario definirlo, esta incluido en la cabecera del pic.

#use standard_io(D) 
#use standard_io(A) 
#define LCD_DATA_PORT getenv("SFR:PORTB")
#include <lcd.c>
#define use_portb_kbd TRUE
#include <kbd.c>
#include <stdlib.h>
#rom int 0xf00000 = {'1','2','3','4','5','6','7','8','4'}

#define CAMARA_1 PIN_D0
#define CAMARA_2 PIN_D1
#define CAMARA_3 PIN_D2
#define CAMARA_4 PIN_D3
#define CAMARA_5 PIN_D4
#define CAMARA_6 PIN_D5
#define CAMARA_7 PIN_D6
#define CAMARA_8 PIN_D7
#define TEST PIN_A4
void main() {
   setup_oscillator (OSC_8MHZ|OSC_INTRC);
   char k;
   int i;
   int data, numero[1];  //Matrices para guardar clave y datos

   lcd_init();
   kbd_init();
   port_b_pullups(TRUE);
   output_high(TEST);
   delay_ms(200);
   output_low(TEST);
   delay_ms(200);
   output_high(TEST);
   delay_ms(200);
   output_low(TEST);
    delay_ms(200);
   output_high(TEST);
   while (TRUE) {
   i=0; //posición de la matriz
   lcd_gotoxy(1,1);
   printf(lcd_putc,"Seleccionar Cam"); 

   while(i<1){                //Para tres datos
      k=kbd_getc();            //Lee el teclado
      
      if ((k!=0)&&( k!= '*' )&&( k!= '#' )&&( k!= '9' )&&( k!= '0' ))                //Si se ha pulsado alguna tecla 
         {data = k;           //se guarda en la posición correspondiente
          i++; 
          lcd_gotoxy(1,1); 
          printf(lcd_putc,"\fCam selecionada");  //Siguiente dato
          delay_ms(10);
         }
        
          if((k!=0)&&( k =='*')&&(data!= '1'))
            
            { i++; 
            data = data -1;
            lcd_gotoxy(1,2);
            printf(lcd_putc,"<----");
            delay_ms(10);
            }
            if((k!=0)&&( k =='#')&&(data!='8'))
            { i++; 
            data = data +1;
            lcd_gotoxy(1,2);
            printf(lcd_putc,"----> %c ",data);
            delay_ms(10);
            }
    }
     delay_ms(10);
   for (i=0;i<=8;i++) {             //Pasa datos de eeprom a la matriz clave
   numero[i]=read_eeprom(i);

      } 

   
   if (data== numero[0])
      {  lcd_gotoxy(1,2);
         printf(lcd_putc,"                 ");
          delay_ms(1);
          lcd_gotoxy(1,2);
         printf(lcd_putc,"Popa Br Cam: %c ",data);
         output_high(CAMARA_1);
         output_low(CAMARA_2);
         output_low(CAMARA_3);
         output_low(CAMARA_4);
         output_low(CAMARA_5);
         output_low(CAMARA_6);
         output_low(CAMARA_7);
         output_low(CAMARA_8);
         delay_ms(10); 

       }
   if (data== numero[1])
      {  lcd_gotoxy(1,2);
        printf(lcd_putc,"                 ");
          delay_ms(1);
          lcd_gotoxy(1,2);
         printf(lcd_putc,"Popa Er Cam: %c ",data);
         output_high(CAMARA_2);
         output_low(CAMARA_1);
         output_low(CAMARA_3);
         output_low(CAMARA_4);
         output_low(CAMARA_5);
         output_low(CAMARA_6);
         output_low(CAMARA_7);
         output_low(CAMARA_8);
        delay_ms(10);
        }
   if (data== numero[2])
      {  lcd_gotoxy(1,2);
        printf(lcd_putc,"                 ");
          delay_ms(1);
          lcd_gotoxy(1,2);
         printf(lcd_putc,"Motor Br Cam : %c ",data );
         output_high(CAMARA_3);
         output_low(CAMARA_1);
         output_low(CAMARA_2);
         output_low(CAMARA_4);
         output_low(CAMARA_5);
         output_low(CAMARA_6);
         output_low(CAMARA_7);
         output_low(CAMARA_8);
        delay_ms(10);
     
   
   }
   if (data== numero[8])
      {  lcd_gotoxy(1,2);
          printf(lcd_putc,"                 ");
          delay_ms(1);
          lcd_gotoxy(1,2);
         printf(lcd_putc,"Motor Er Cam: %c ",data);
         output_high(CAMARA_4);
         output_low(CAMARA_1);
         output_low(CAMARA_2);
         output_low(CAMARA_3);
         output_low(CAMARA_5);
         output_low(CAMARA_6);
         output_low(CAMARA_7);
         output_low(CAMARA_8);
         delay_ms(10);
     
   
   }
   if (data == numero[4])
      {  lcd_gotoxy(1,2);
          printf(lcd_putc,"                 ");
          delay_ms(1);
          lcd_gotoxy(1,2);
         printf(lcd_putc,"Salon Cam: %c ",data);
         output_high(CAMARA_5);
         output_low(CAMARA_1);
         output_low(CAMARA_2);
         output_low(CAMARA_3);
         output_low(CAMARA_4);
         output_low(CAMARA_6);
         output_low(CAMARA_7);
         output_low(CAMARA_8);
        delay_ms(10);
     
   
   }
   if (data== numero[5])
      {  lcd_gotoxy(1,2);
         printf(lcd_putc,"                 ");
          delay_ms(1);
          lcd_gotoxy(1,2);
         printf(lcd_putc,"Proa  Cam: %c ",data);
          output_high(CAMARA_6);
         output_low(CAMARA_1);
         output_low(CAMARA_2);
         output_low(CAMARA_3);
         output_low(CAMARA_4);
         output_low(CAMARA_5);
         output_low(CAMARA_7);
         output_low(CAMARA_8);
        delay_ms(10);
      }
   if (data== numero[6])
      {  lcd_gotoxy(1,2);
         printf(lcd_putc,"                 ");
          delay_ms(1);
          lcd_gotoxy(1,2);
         printf(lcd_putc,"----- Cam : %c ",data);
          output_high(CAMARA_7);
         output_low(CAMARA_1);
         output_low(CAMARA_2);
         output_low(CAMARA_3);
         output_low(CAMARA_4);
         output_low(CAMARA_5);
         output_low(CAMARA_6);
         output_low(CAMARA_8);
        delay_ms(10);
     
   
   }
   if (data== numero[7])
      {  lcd_gotoxy(1,2);
          printf(lcd_putc,"                 ");
          delay_ms(1);
          lcd_gotoxy(1,2);
         printf(lcd_putc,"----- Cam: %c ",data);
          output_high(CAMARA_8);
         output_low(CAMARA_1);
         output_low(CAMARA_2);
         output_low(CAMARA_3);
         output_low(CAMARA_4);
         output_low(CAMARA_5);
         output_low(CAMARA_6);
         output_low(CAMARA_7);
        delay_ms(10);
     
   
   }
}}


