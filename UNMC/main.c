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
#include <string.h>

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/// Funcion Caratula
/// Display presentation day hour
/// variable lecture diasem, anio, dia, hora, etc
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[      

    void caratula(const char * titulo)
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


void clear_display(const int pos){
    lcd_gotoxy(pos,2);
    lcd_putrs("                         ");
    lcd_gotoxy(pos,2);   
}    
    
void menu_ingresar_password(){    
           
    lcd_comand(0b00001100);             //Enciende display sin cursor y sin blink  
    lcd_gotoxy(1,1);        
    lcd_putrs("Inserte password");    
    lcd_gotoxy(tamanio_password+1,2);            
    
    validar_password();
    if (tamanio_password >= 6 && !autorizado){                
        lcd_gotoxy(1,2);
        lcd_putrs("ERROR pass");
        
        intentos_fallidos++;
        tamanio_password = 0;
        *current_password = 0;;
        
        for (int i=0;i<4;i++)__delay_ms(98);      
        clear_display(tamanio_password);
    }
}    

void mostrar_titulo_menu(const char * titulo_menu){
    lcd_gotoxy(1,1);            
    lcd_putrs(titulo_menu);    
}

void mostrar_guardar_password(char tecla){    
    
    imprimir_tecla(tecla);
    sprintf(buffer2,"%01u",tecla);
    guardar_current_password(*buffer2);    
}

void mostrar_guardar_temporal_password(char tecla){    
    
    imprimir_tecla(tecla);
    sprintf(buffer2,"%01u",tecla);
    guardar_password_temporal(*buffer2);        
}

void mostrar_guardar_nuevo_password(char tecla){    
    
    imprimir_tecla(tecla);
    sprintf(buffer2,"%01u",tecla);
    guardar_nuevo_password(*buffer2);    
}

void confirmar_actualizar_password(char tecla){    
    
    imprimir_tecla(tecla);
    sprintf(buffer2,"%01u",tecla);
    actualizar_password(buffer2[0]);
}

void ingresar_comando(char key){
    guardar_comando(key);
}

void menu_cambiar_fecha(){  
    
    funcion_pulsador_C = cancelar_cambio_fecha;
    
    if (tamanio_anio != 2){              
        mostrar_titulo_menu("Inserte anio:     ");
        puntero_funcion = &cambiar_anio; 
        funcion_pulsador_D = borrar_anio;
        clear_display(tamanio_anio+1);
               
    }else if (tamanio_mes != 2){                            
        mostrar_titulo_menu("Inserte mes:     ");
        puntero_funcion = &cambiar_mes;
        funcion_pulsador_D = borrar_mes;
        clear_display(tamanio_mes+1);
                
    }else if (tamanio_dia != 2){
        mostrar_titulo_menu("Inserte dia:     ");
        puntero_funcion = &cambiar_dia;
        funcion_pulsador_D = borrar_dia;
        clear_display(tamanio_dia+1);
                
    }
}

void menu_cambiar_horario(){
    
    funcion_pulsador_C = cancelar_cambio_hora;
    
    if (tamanio_minutos != 2){  
        mostrar_titulo_menu("Inserte minutos:     ");
        puntero_funcion = cambiar_minutos;
        funcion_pulsador_D = borrar_minutos;
        clear_display(tamanio_minutos+1);
                                
    }else if (tamanio_hora != 2){                            
        mostrar_titulo_menu("Inserte hora:     ");
        puntero_funcion = cambiar_hora;
        funcion_pulsador_D = borrar_hora;
        clear_display(tamanio_hora+1);
                
    }
}

void menu_cambiar_password(){

    int verifica;
    
    funcion_pulsador_C = cancelar_cambio_password;    
            
    verficar_password(&verifica);
    if(!verifica){
        puntero_funcion = &mostrar_guardar_temporal_password;
        mostrar_titulo_menu("Password actual:          ");                 
        clear_display(tamanio_password+1);
                
    }else {                
        if (tamanio_new_password <= tam_pass){  
            puntero_funcion = &mostrar_guardar_nuevo_password;

            mostrar_titulo_menu("Nuevo pass:        ");
            clear_display(tamanio_new_password+1);
                    
            if (tamanio_new_password == tam_pass) tamanio_new_password++;
            tamanio_password = 0;            
        
        }else { 
            puntero_funcion = &confirmar_actualizar_password;

            mostrar_titulo_menu("Confirme pass:        ");
            clear_display(tamanio_password+1);                                                                           
        }               
    }
}

void mensaje_alarma_activada(){               
    lcd_gotoxy(1,1);
    lcd_putrs("#### ALARMA ####");
    lcd_gotoxy(1,2);
    lcd_putrs("### ACTIVADA ###");
    
}

void activar_sonido_alarma(){
    LED_3_Toggle;
    Speaker_Toggle;
    Speaker_2_Toggle;
}

void desactivar_sonido_alarma(){
    activada=0;
    LED_3_Off;
    Speaker_Off;
    Speaker_2_Off;
    inicializar_intentos_fallidos();
}

void desactivar_alarma(){
    if (!autorizado){
        inicializar_intentos_fallidos();
        puntero_funcion = mostrar_guardar_password;
        menu_ingresar_password();
        clear_display(tamanio_password);
    }
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
inicializar_teclado();
int ocultar_teclas = 1;

while(1)
   {
    Read_RTC();
    
    if (intentos_fallidos > 2){
       activada = 1;
       mensaje_alarma_activada();
       funcion_pulsador_B = desactivar_alarma;
    }        
    
    if (activada)
        activar_sonido_alarma();
    
    if (!autorizado && intentos_fallidos <=2){         
        puntero_funcion = mostrar_guardar_password;
        menu_ingresar_password();        
    }       
    
    if (autorizado){ 
        desactivar_sonido_alarma();
        
        puntero_funcion = &ingresar_comando;
        funcion_pulsador_C = restaurar_comando;
        funcion_pulsador_D = restaurar_comando;
        
        switch (atoi(comando))
        {               
            case 10 : menu_cambiar_password(); break;
            case 11 : menu_cambiar_fecha(); break;
            case 12 : menu_cambiar_horario(); break;
            default:  caratula("Welcome "); 
                      if (tamanio_comando >= 2) 
                        tamanio_comando = 0;
                      break;
        }      
    }  
    
    leer_teclado(ocultar_teclas);
   }
return 0;
}
