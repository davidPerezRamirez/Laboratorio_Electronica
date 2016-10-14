/*******************************************************************************
 *
 *                Unimic 01 Version 1.1   6 September 2016
 *
 *******************************************************************************
 * FileName:        main.c
 * Dependencies:
 * Processor:       PIC18F26J50
 * Compiler:        XC8 1.34
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO
 * THIS SOFTWARE. THE COMPANY SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR
 * SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 ******************************************************************************/
#include <xc.h>
#include <delays.h>
#include <unmc_config_01.h>
#include <unmc_inout_01.h>
#include <unmc_display.h>

void setup(void){  
    
    OSCTUNEbits.INTSRC=1;       //setea el oscilador de 32768 para el RTC
    OSCTUNEbits.PLLEN=0;        //desactiva PLL
    OSCCONbits.IRCF0=1;         //selecciona el clock en 8MHz
    OSCCONbits.IRCF1=1;
    OSCCONbits.IRCF2=1;
    OSCCONbits.SCS0=0;          //oscilator INTRC
    OSCCONbits.SCS1=0;
    TRISA = 0b11111000;
    TRISB = 0;
    TRISC = 0b00000111;
    //TRISAbits.TRISA0=1;
    //TRISBbits.TRISB0=0;
    //TRISCbits.TRISC0=0;
    ANCON0=0b11111110;          // Config AN7 to AN0 Digital Ports
    //ANCON1=0b10010111;        // Config AN11 Analog Port
    ANCON1=0b11111111;          // Config AN12 to AN8 Digital Ports
    ADCON0=0b01000000;          // Control AN11 Analog Port
    ADCON1=0b00111000;          // Config Analog Port   
    RTCCFGbits.RTCEN=1;
    RTCCFGbits.RTCWREN=1;
    T1CONbits.T1OSCEN=1;
}

void imprimir_temperatura(int temp){
    
    int decena = (int)temp / 10;
    int unidad = temp - (decena*10);
    
    DSS_TEN_On;    
    construir_numero(decena);      
    DSS_TEN_Off; 
    
    DSS_UNIT_On;         
    construir_numero(unidad);
    DSS_UNIT_Off;
  
}

int calcular_temperatura(int voltage){
    
    return (int)(0.588 * voltage - 50);
}

int leer_temperatura(){
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
    int voltage;
    
    while (ADCON0bits.GO);
    __delay_ms(1);
    voltage = ADRESH;
    ADCON0bits.ADON = 0;   
    return calcular_temperatura(voltage);
}

int main(void){
    
    setup();
    int temperatura = 0; 
    int valor = 99;
    int i;
    
    while(1){  
        
        temperatura = leer_temperatura();
        if (temperatura < valor){
            valor--;
        }else{
            if (temperatura > valor){
                valor++;
            }
            else
                valor = temperatura;
        }

        i = 0;
        while (i < 10){
            imprimir_temperatura(valor);
            i++;
        }         
    }
    
    return 0;
    
}