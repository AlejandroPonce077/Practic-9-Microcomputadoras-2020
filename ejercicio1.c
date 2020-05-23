///////////////////////////////////////////////////////////////////////////////
//   
// Programa el cual obtenga una señal analógica a través del canal de su 
// elección, se realice la conversión y el resultado de esta, la muestre en un 
// puerto paralelo y a su vez lo transmita al puerto serie.
//
///////////////////////////////////////////////////////////////////////////////

#include <16F877A.h>
#fuses NOWDT, NOLVP, NOPROTECT
#device adc=8                                   //CAD con resolución de 8 bits
#use delay(clock=20000000)
#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7)

void main()
{
   unsigned int8 resultadoAD;
   setup_port_a(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   delay_ms(20);
   
   while(TRUE)
   {
      resultadoAD=read_adc();
      output_b(resultadoAD);
      printf("\n\rEl resultado de la conversion AD es: %3u", resultadoAD);
      delay_ms(1000);
   }
}
