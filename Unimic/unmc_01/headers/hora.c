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

static void convertir_a_int_hora(char * array, int * valor){
    *valor = atoi(array);
}

static void guardar_elemento_hora(char tecla, char * array, int * tamanio_array,int * validacion,int * dato_hora,void *doit(int *,int *)){
    
    int valor = 0;           
    
    if (validacion){
        
        sprintf(buffer2,"%01u",tecla);
        array[*tamanio_array] = *buffer2;      
        array [(*tamanio_array)+1] = 0;
        (*tamanio_array)++;
        
        lcd_gotoxy(1,2);
        lcd_putrs(array);        
    }
    
    if (*tamanio_array >= cantidad_elementos - 1){             
        
        convertir_a_int_hora(array,&valor);
        
         if(valor >= valor_min && valor <= valor_max){                  
            doit(dato_hora,&valor);
            
        }else{
           *tamanio_array = 0;
           *array = 0;
           lcd_gotoxy(1,2);
           sprintf(buffer2,"valor >=%d y <=%d",valor_min,valor_max);
           lcd_putrs(buffer2);  
            
        } 
                                
        for (int i=0;i<2;i++)__delay_ms(98);        
    }   
}

static void actualizar_hora(int * elemento, int * valor){
        
    *elemento = *valor;
    Write_RTC();
    restaurar_comando();
    inicializar_hora();
}

static void actualizar_minutos(int * elemento, int * valor){
        
    *elemento = *valor;
    segundo = 00;
    Write_RTC();
}

void cambiar_hora(char tecla){
    
    valor_min = 0;
    valor_max = 23;
    
    int validacion = tamanio_hora < cantidad_elementos - 1;
    guardar_elemento_hora(tecla,hour,&tamanio_hora,validacion,&hora,actualizar_hora);
}

void cambiar_minutos(char tecla){
    
    valor_min = 0;
    valor_max = 59;
    
    int validacion = (tamanio_minutos < cantidad_elementos - 1 && tamanio_hora == 0);
    guardar_elemento_hora(tecla,minutes,&tamanio_minutos,validacion,&minuto,actualizar_minutos);
}