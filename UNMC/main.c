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
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 ***********************************************************************/
#include <xc.h>
#include <delays.h>
#include <stdio.h>
#include <teclado.h>
#include <alarma.h>
#include <fecha.h>
#include <hora.h>

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/// Funcion Caratula
/// Display presentation day hour
/// variable lecture diasem, anio, dia, hora, etc
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[      

    void caratula(char * titulo)
    {                
        lcd_comand(0b00001100);             //Enciende display sin cursor y sin blink  
        lcd_gotoxy(1,1);        
        lcd_putrs(titulo);
        
        sprintf(buffer2,"%02u/%02u/%02u",dia,mes,anio);
        lcd_gotoxy(9,1);
        lcd_putrs(buffer2);
        
        sprintf(buffer2,"%02u:%02u:%02u",hora,minuto,segundo);
        lcd_gotoxy(1,2);
        lcd_putrs(buffer2);
        
        lcd_gotoxy(13,2);
        lcd_putrs((encendida)?"ON":"OFF");
    }
    
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
    OSCCONbits.SCS0=0;          //oscilator INTRC
    OSCCONbits.SCS1=0;
    TRISA = 0b11110000;
    TRISB = 0;
    TRISC = 0b00000111;
    //TRISAbits.TRISA0=1;
    //TRISBbits.TRISB0=0;
    //TRISCbits.TRISC0=0;
    ANCON0=0b11111111;          // Config AN7 to AN0 Digital Ports
    //ANCON1=0b10010111;          // Config AN11 Analog Port
    ANCON1=0b11111111;          // Config AN12 to AN8 Digital Ports
    ADCON0=0b00101101;          // Control AN11 Analog Port
    ADCON1=0b00010000;          // Config Analog Port
    RTCCFGbits.RTCEN=1;
    RTCCFGbits.RTCWREN=1;
    T1CONbits.T1OSCEN=1;
    Write_RTC();
    lcd_init();
    lcd_comand(0b00001100);     //Display=on / Cursor=off / Blink=off
    LED_2_Off;
    LED_3_Off;
    }
    
ingresar_password(){
    char clear[16];
    for (int i=0;i<16;i++) clear[i]=' ';
    
    if(tamanio_password < 6){
        
        lcd_comand(0b00001100);             //Enciende display sin cursor y sin blink  
        lcd_gotoxy(1,1);        
        lcd_putrs("Inserte password");
        lcd_gotoxy(tamanio_password+1,2);        
    }
    
    validar_password();
    if (tamanio_password >= 6 && !autorizado){
        tamanio_password = 0;        
        lcd_gotoxy(1,2);
        lcd_putrs("ERROR pass");
        for (int i=0;i<4;i++)__delay_ms(98);      
        lcd_gotoxy(1,2);
        lcd_putrs(clear);
    }
}    

mostrar_menu(char * titulo_menu){
    lcd_gotoxy(1,1);            
    lcd_putrs(titulo_menu);
    lcd_gotoxy(1,2);
    lcd_putrs("  ");
}

mostrar_guardar_password(char tecla){    
    
    imprimir_tecla(tecla);
    sprintf(buffer2,"%01u",tecla);
    guardar_current_password(*buffer2);
    
}

ingresar_comando(char key){
    guardar_comando(key);
}

/*------------------------------------------------------------------------------
********************************************************************************
Funcion main
Funcion principal del programa
********************************************************************************
--------------------------------------------------------------------------------*/
int main(void)
{
Setup();  
restaurar_comando();

int ocultar_teclas = 1;
int validacion;
void *puntero_funcion;

while(1)
   {
    Read_RTC();
           
    if (!autorizado){ 
        leer_teclado(ocultar_teclas,mostrar_guardar_password);  
        ingresar_password(); 
        
    }else{                        
        puntero_funcion = ingresar_comando;       
        
        validar_comando("xxx",&validacion);            
        if(validacion){     
            caratula("Welcome");
        }
        
        validar_comando("001",&validacion);            
        if(validacion){
            //Limpia la fila 2 del display
            lcd_gotoxy(3,2);
            lcd_putrs("                 "); 
            
            if (tamanio_anio != 2){              
               mostrar_menu("Inserte anio:     ");
               puntero_funcion = cambiar_anio;               
                                
            }else if (tamanio_mes != 2){                            
                mostrar_menu("Inserte mes:     ");
                puntero_funcion = cambiar_mes;
                
            }else if (tamanio_dia != 2){
                mostrar_menu("Inserte dia:     ");
                puntero_funcion = cambiar_dia;
                
            }
        }
        
        validar_comando("002",&validacion);            
        if(validacion){
            //Limpia la fila 2 del display
            lcd_gotoxy(3,2);
            lcd_putrs("                    "); 
            
            if (tamanio_minutos != 2){  
                mostrar_menu("Inserte minutos:     ");
                puntero_funcion = cambiar_minutos;               
                                
            }else if (tamanio_hora != 2){                            
                mostrar_menu("Inserte hora:     ");
                puntero_funcion = cambiar_hora;
                
            }
        }
                   
        if(key == 'C'){            
            lcd_gotoxy(1,2);            
            lcd_putrs("cambiar pass");
            for (int i=0;i<10;i++)__delay_ms(98);
            restaurar_comando();
        }        
                 
        leer_teclado(!ocultar_teclas,puntero_funcion);         
    }    
   }
return 0;
}
