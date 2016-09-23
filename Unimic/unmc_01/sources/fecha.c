#include <fecha.h>

static void convertir_a_int(char * array, int * valor){
    *valor = atoi(array);
}

static void guardar_elemento(char tecla, char * array, int * tamanio_array, int validacion,int * dato_fecha ,void (*doit) (int *,const int)){
    
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
        
        convertir_a_int(array,&valor);
        
         if(valor >= valor_min && valor <= valor_max){                  
            doit(dato_fecha,valor);
            __delay_ms(98);
            
        }else{
           *tamanio_array = 0;
           *array = 0;
           lcd_gotoxy(1,2);
           sprintf(buffer2,"valor >=%d y <=%d",valor_min,valor_max);
           lcd_putrs(buffer2);  
           
           for (int i=0;i<4;i++)__delay_ms(98);
            
        }                                                 
    }            
}

static void actualiza_elemento(int * elemento,const int valor){
        
    *elemento = valor;
    Write_RTC();
}

/****************************************************************************
 * 
 FUNCIONES PARA LA ACTUALIZACION DE LA FECHA
 * 
 *****************************************************************************/
void inicializar_fecha(){
    *day = 0;
    *month = 0;
    *year = 0;    
    
    tamanio_dia = 0;
    tamanio_mes = 0;
    tamanio_anio = 0;
}

static void actualiza_dia(int * elemento,const int valor){
        
    actualiza_elemento(elemento,valor);   
    restaurar_comando();
    inicializar_fecha();
}

static void obtener_dia_mes(){
    
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
        valor_max = 31;
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        valor_max = 30;    
    else{
        if ((anio%4==0) && (anio%100!=0) || anio%400==0)
            valor_max =29;
        else
            valor_max =28;
    }
    
}

void cambiar_dia(char tecla){
    
    valor_min = 1;
    obtener_dia_mes();    
    
    int validacion = tamanio_dia < cantidad_elementos - 1;
    guardar_elemento(tecla,day,&tamanio_dia,validacion,&dia,actualiza_dia);
    
}

void cambiar_mes(char tecla){
    
    valor_min = 1;
    valor_max = 12;
    
    int validacion = (tamanio_mes < cantidad_elementos - 1 && tamanio_dia == 0);
    guardar_elemento(tecla,month,&tamanio_mes,validacion,&mes,actualiza_elemento);
    
}

void cambiar_anio(char tecla){
    
    valor_min = 16;
    valor_max = 99;
    
    int validacion = (tamanio_anio < cantidad_elementos - 1 && tamanio_mes == 0 && tamanio_dia == 0);
    guardar_elemento(tecla,year,&tamanio_anio,validacion,&anio,actualiza_elemento);
    
}

void cancelar_cambio_fecha(){
    inicializar_fecha();
    restaurar_comando();
}

void borrar_dia(){
    *day = 0;
    tamanio_dia = 0;
        
}

void borrar_mes(){
    *month = 0;
    tamanio_mes = 0;
}

void borrar_anio(){
    *year = 0;
    tamanio_anio = 0;
}
/****************************************************************************
 * 
 FUNCIONES PARA LA ACTUALIZACION DE LA HORA
 * 
 *****************************************************************************/

void inicializar_hora(){
    *hour = 0;
    *minutes = 0;  
    
    tamanio_hora = 0;
    tamanio_minutos = 0;
}

static void actualizar_hora(int * elemento,const int valor){
        
    actualiza_elemento(elemento,valor);
    Write_RTC();
    restaurar_comando();
    inicializar_hora();    
}

static void actualizar_minutos(int * elemento,const int valor){
        
    *elemento = valor;
    segundo = 00;
    Write_RTC();
}

void cambiar_hora(char tecla){
    
    valor_min = 0;
    valor_max = 23;
    
    int validacion = tamanio_hora < cantidad_elementos - 1;
    guardar_elemento(tecla,hour,&tamanio_hora,validacion,&hora,actualizar_hora);
}

void cambiar_minutos(char tecla){
    
    valor_min = 0;
    valor_max = 59;
    
    int validacion = (tamanio_minutos < cantidad_elementos - 1 && tamanio_hora == 0);
    guardar_elemento(tecla,minutes,&tamanio_minutos,validacion,&minuto,actualizar_minutos);
}

void cancelar_cambio_hora(){
    inicializar_hora();
    restaurar_comando();
}

void borrar_hora(){
    *hour = 0;
    tamanio_hora = 0;
        
}

void borrar_minutos(){
    *minutes = 0;
    tamanio_minutos = 0;
}