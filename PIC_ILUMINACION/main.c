/*********************************************************************
 *
 *                Unimic 01 Version 1.1   10 September 2015
 *
 ***********************************************************************
 * FileName:        main.c
 * Dependencies:
 * Processor:       PIC18F26J50
 * Compiler:        XC8 1.34
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * ||
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 ***********************************************************************/
#include <xc.h>
#include<delays.h>
#include<stdio.h>
#include <unmc_lcd_216.h>
#include <unmc_rtcc_01.h>
#include <unmc_config_01.h>
#include <unmc_inout_03.h>

#define MAX_NIVEL_INTENSIDAD 32
#define RETARDO_INTENSIDAD 500


//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/// Funcion Setup
///
///
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

    void Setup(void)
    {
    OSCTUNEbits.INTSRC=1;       //setea el oscilador de 32768 para el RTC
    OSCTUNEbits.PLLEN=0;        //desactiva PLL
    OSCCONbits.IRCF0=1;         //selecciona el clock en 8MHz
    OSCCONbits.IRCF1=1;
    OSCCONbits.IRCF2=1;
    OSCCONbits.SCS0=0;              //oscilator INTRC
    OSCCONbits.SCS1=0;
    TRISA = 0b01010011;
    TRISB = 0;
    TRISC = 0b00000111;
    //TRISAbits.TRISA0=1;
    //TRISBbits.TRISB0=0;
    //TRISCbits.TRISC0=0;
    ANCON0=0b11111110;          // Config AN7 to AN0 Digital Ports
    //ANCON1=0b10010111;        // Config AN11 Analog Port
    ANCON1=0b1111111;          // Config AN12 to AN8 Digital Ports
    ADCON0=0b00000000;          // Control AN11 Analog Port
    ADCON1=0b00111000;           //Sin Conversor AD
    RTCCFGbits.RTCEN=1;
    RTCCFGbits.RTCWREN=1;
    T1CONbits.T1OSCEN=1;
    Write_RTC();
    LED_1_Off;
    LED_2_Off;
    LED_3_Off;
    lista_leds_rojo_off;
    lista_leds_azul_off;
    lista_leds_verde_off;
    }
    
    void encender_led(int led){
        switch(led){
            case 1: LED_1_On;LED_2_Off;LED_3_Off;break;
            case 2: LED_2_On;LED_1_Off;LED_3_Off;break;
            case 3: LED_3_On;LED_1_Off;LED_2_Off;break;
            case 4: lista_leds_rojo_on;break;
            case 5: lista_leds_azul_on;break;
            case 6: lista_leds_verde_on;break;
        }
    }
    
    void apagar_led(int led){
        switch(led){
            case 1: LED_1_Off;break;
            case 2: LED_2_Off;break;
            case 3: LED_3_Off;break;
            case 4: lista_leds_rojo_off; break;
            case 5: lista_leds_azul_off; break;
            case 6: lista_leds_verde_off; break;
        }
    }
    
    void intensidad_led(int num_led, int intensidad){     
        
        int i = 1;
        
        while (i < MAX_NIVEL_INTENSIDAD + 1){            
            if (i < intensidad)
                encender_led(num_led);            
            else
               apagar_led(num_led);
            
            __delay_us(RETARDO_INTENSIDAD);
            i++;
        }   
    }
    
    void leer_teclado(){
        row1=1;
        row2=0;
        row3=0;
        row4=0;
        {
            if (column1==1&&row1==1){key=1;intensidad_led(1,1);}
            if (column2==1&&row1==1){key=2;intensidad_led(2,2);}
            if (column3==1&&row1==1){key=3;intensidad_led(3,4);}
        }
        row1=0;
        row2=1;
        row3=0;
        row4=0;
        {
            if (column1==1&&row2==1){key=4;intensidad_led(1,8);}
            if (column2==1&&row2==1){key=5;intensidad_led(2,16);}
            if (column3==1&&row2==1){key=6;intensidad_led(3,31);}
        }
    }
    
    void flash_leds(int intensidad){
        int contador = 0;
        while (contador < 15){
            intensidad_led(4,intensidad);
            intensidad_led(5,intensidad);
            intensidad_led(6,intensidad);
            apagar_led(4);
            apagar_led(5);            
            apagar_led(6);           
            contador++;
        }   
    }
   
    void activar_led(int intensidad, int *id_led){
                
        int contador = 0;
        
        while (contador < 15){
                intensidad_led((*id_led),intensidad);            
                contador++;
        }
        contador = 0;
        (*id_led)++;
        if ((*id_led) > 6)
            (*id_led) = 4;   
        apagar_led((*id_led));
    }
    
/****************************************************/    
    int calcular_intensidad(int voltage){    
        return (int)(0.125 * voltage);
    }    
    
    int leer_intensidad(){
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
    int voltage;
    
    while (ADCON0bits.GO);
    __delay_ms(1);
    voltage = ADRESH;
    ADCON0bits.ADON = 0;   
    return calcular_intensidad(voltage);
}
    
/****************************************************/ 
    
    
/*------------------------------------------------------------------------------
********************************************************************************
Funcion main
Funcion principal del programa
********************************************************************************
--------------------------------------------------------------------------------*/
int main(void)
{
Setup();
int intensidad = 32;
int id_led = 4;

while(1)
    {   
    
        intensidad = leer_intensidad();
        if (switch1 == 0){            
            if (intensidad > 28)
                flash_leds(leer_intensidad());
            else
                activar_led(intensidad, &id_led);                  
        }            
    }
return 0;
}
