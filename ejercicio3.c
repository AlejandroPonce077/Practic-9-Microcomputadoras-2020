///////////////////////////////////////////////////////////////////////////////
//
// Realizar un programa el cual constantemente transmita el resultado de la 
// conversion a la terminal, y cada 30 segundos interrumpa la ejecución de este 
// y envíe el siguiente texto "Laboratorio de microcomputadoras"
//
///////////////////////////////////////////////////////////////////////////////

#include <16F877A.h>
#fuses HS, NOWDT, NOPROTECT
#device ADC=8
#use delay(clock = 20000000)
#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7)
#org 0x1F00, 0x1FFF void loader16F877A(void){}

#define CUENTAS 3000 //Número de cuentas para 30 s
static int16 contador;

#INT_RTCC
void clock_isr()
{
   if(contador >= CUENTAS)
   {
      printf("\n\rLaboratorio de microcomputadoras");
      contador=0;
   }
   contador++;   
   set_timer0(61);
}

void main()
{
   setup_counters(RTCC_INTERNAL,RTCC_DIV_256);   //Fuente de reloj y predivisor
   set_timer0(61);                     //Inicia el TIMER 0 en 61 decimal
   enable_interrupts(INT_RTCC);        //Habilitar la interrupción por TIMER 0
   enable_interrupts(GLOBAL);          //Habilita interrupciones generales
   setup_port_a(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   delay_us(20);
   
   while(TRUE)
   {
      printf("\n\rResultado de la conversion AD: %3u",read_adc());
      delay_ms(1000);
   }
}

