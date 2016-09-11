#include <hora.h>
#include <stdio.h>
#include <unmc_lcd_216.h>
#include <unmc_rtcc_02.h>
#include <teclado.h>

#define cantidad_elementos 3

void inicializar_hora(){
    *hour = 0;
    *minutes = 0;  
    
    tamanio_hora = 0;
    tamanio_minutos = 0;
}

void guardar_elemento_hora(char tecla, char * array, int * tamanio_array){
    
    sprintf(buffer2,"%01u",tecla);
    array[*tamanio_array] = *buffer2;      
    array [(*tamanio_array)+1] = 0;
    (*tamanio_array)++;
}

void convertir_a_int_hora(char * array, int * valor){
    *valor = atoi(array);
}


void cambiar_hora(char tecla){
    int valor = 0;           
    
    if (tamanio_hora < cantidad_elementos - 1){
        guardar_elemento_hora(tecla,hour,&tamanio_hora);
        lcd_gotoxy(1,2);
        lcd_putrs(hour);        
    }
    
    if (tamanio_hora >= cantidad_elementos - 1){
        convertir_a_int_hora(hour,&valor);        
        hora = valor;
        Write_RTC();
        
        restaurar_comando();
        inicializar_hora();
        for (int i=0;i<4;i++)__delay_ms(98);        
    }
}

void cambiar_minutos(char tecla){
    
    int valor = 0;           
      
    if (tamanio_minutos < cantidad_elementos - 1 && tamanio_hora == 0){
        guardar_elemento_hora(tecla,minutes,&tamanio_minutos);
        lcd_gotoxy(1,2);
        lcd_putrs(minutes);        
    }
    
    if (tamanio_minutos >= cantidad_elementos - 1){
                
        convertir_a_int_hora(minutes,&valor);        
        minuto = valor;
        segundo = 00;
        Write_RTC();        
        for (int i=0;i<4;i++)__delay_ms(98);        
    }
}