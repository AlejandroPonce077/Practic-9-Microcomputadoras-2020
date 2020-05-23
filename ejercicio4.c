#include <16f877.h>     //Tipo de MicroControlador a utilizar
#fuses HS,NOPROTECT,
#use delay(clock=20000000) //Frec. de Osc. 20Mhz
//Configuraci�n Puerto SERIAL
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
#org 0x1F00, 0x1FFF

void loader16F877(void) {}

//Definici�n de variables 
int var;
int var2;
int16 contador=0;

#int_rb //Rutina de interrupci�n

port_rb(){
    
    var2=input_b(); //Lee la entrada en el puerto B
    
    if(var2==0x80)  //Interrupci�n PB7 Activada?
    printf("Interrupcion PB7 activada\n\r");
    if(var2==0x40)  //Interrupci�n PB6 Activada?
    printf("Interrupcion PB6 activada\n\r");              
    if(var2==0x20)  //Interrupci�n PB5 Activada?
    printf("Interrupcion PB5 activada\n\r");
    if(var2==0x10)  //Interrupci�n PB4 Activada?
    printf("Interrupcion PB4 activada\n\r");
    if(var2==0x00)  //Interrupci�n desactiada?
    printf("Pulso de bajada\n\r");
 }
 
#int_rtcc      //Para timer0

clock_isr(){   //Rutina de atenci�n a la interrupci�n por Timer0
     contador++;
     if(contador==770){
     contador=0;
   }
}

void main(){

    Enable_interrupts(INT_RB); //Habilita interrupci�n por cambio
    // de nivel en los cuatro bits m�s significativos del puerto B

    set_timer0(0);             //Inicia el timer0 en 00H
    //Fuente de reloj y pre-divisor
    setup_counters(RTCC_INTERNAL,RTCC_DIV_256); 
    enable_interrupts(INT_RTCC);//Habilita la interrupci�n TIMER0
    enable_interrupts(GLOBAL);  //Habilita interrupciones generales

     while(1){
        delay_us(20);     //Retardo 
        var=read_adc();   //Lee el resultado de la Conversi�n
        delay_us(20);     //Retardo
        //Imprime en la terminal el resultado de la Conv.
        printf("valor= %u \n\r",var); 
        delay_ms(100);    //Retardo
     }
}
