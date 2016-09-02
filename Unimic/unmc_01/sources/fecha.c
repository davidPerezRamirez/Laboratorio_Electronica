#include <fecha.h>
#include <stdio.h>
#include <unmc_lcd_216.h>
#include <teclado.h>

#define cantidad_elementos 3

void inicializar(){
    *day = 0;
    *month = 0;
    *year = 0;    
    
    tamanio_dia = 0;
    tamanio_mes = 0;
    tamanio_anio = 0;
}

void guardar_elemento(char tecla, char * array, int * tamanio_array){
    
    sprintf(buffer2,"%01u",tecla);
    array[*tamanio_array] = *buffer2;      
    array [(*tamanio_array)+1] = 0;
    (*tamanio_array)++;
}

void convertir_a_int(char * array, int * valor){
    *valor = atoi(array);
}


void cambiar_dia(char tecla){
    int valor = 0;           
    
    if (tamanio_dia < cantidad_elementos - 1 && tamanio_mes == 0 && tamanio_anio == 0){
        guardar_elemento(tecla,day,&tamanio_dia);
        lcd_gotoxy(1,2);
        lcd_putrs(day);        
    }
    
    if (tamanio_dia >= cantidad_elementos - 1){
        convertir_a_int(day,&valor);        
        dia = valor;
        Write_RTC();
        
        for (int i=0;i<4;i++)__delay_ms(98);
        //restaurar_comando();
    }
}

void cambiar_mes(char tecla){
    
    int valor = 0;           
      
    if (tamanio_mes < cantidad_elementos - 1 && tamanio_anio == 0){
        guardar_elemento(tecla,month,&tamanio_mes);
        lcd_gotoxy(1,2);
        lcd_putrs(month);        
    }
    
    if (tamanio_mes >= cantidad_elementos - 1){
                
        convertir_a_int(month,&valor);        
        mes = valor;
        Write_RTC();        
        for (int i=0;i<4;i++)__delay_ms(98);        
    }
}

void cambiar_anio(char tecla){
    int valor = 0;           
      
    if (tamanio_anio < cantidad_elementos - 1){
        guardar_elemento(tecla,year,&tamanio_anio);
        lcd_gotoxy(1,2);
        lcd_putrs(year);        
    }
    
    if (tamanio_anio >= cantidad_elementos - 1){
                
        convertir_a_int(year,&valor);        
        anio = valor;
        Write_RTC();        
        
        restaurar_comando();
        inicializar();
        for (int i=0;i<4;i++)__delay_ms(98);        
    } 
}
void cambiar_fecha(char tecla){
    
    cambiar_dia(tecla);
    cambiar_mes(tecla);
    cambiar_anio(tecla);
}    