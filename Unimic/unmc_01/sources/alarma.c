#include <alarma.h>

void cancelar_cambio_password(){
    new_password[0] = 0;        
    temporal[0] = 0;        
        
    tamanio_new_password = 0;
    tamanio_password = 0;
    
    restaurar_comando();        
}

void inicializar_intentos_fallidos(){
    intentos_fallidos = 0;
}

static void guardar_elemento_arreglo(char* arreglo,const char valor, int * tamanio){
    
    if (*tamanio < tam_pass){
        arreglo[*tamanio] = valor;      
        arreglo [*tamanio + 1] = '\0';
        (*tamanio)++;
    }
    
}

void guardar_current_password(const char valor){    
    guardar_elemento_arreglo(current_password,valor, &tamanio_password );
}

void guardar_password_temporal(const char valor){
    guardar_elemento_arreglo(temporal,valor, &tamanio_password );
}

void guardar_nuevo_password(char valor){
    guardar_elemento_arreglo(new_password,valor, &tamanio_new_password );
}

void validar_password(){
    
    autorizado = 1;
    int i = 0;
    while (i < tam_pass && autorizado==1){        
        if (current_password[i] != password[i])
            autorizado = 0;        
        i++;
    }
    
    if (autorizado == 1){
        tamanio_password = 0;
        encendida = 1;
        LED_2_On;
    }
}

void verficar_password(int * verifica){
        
    *verifica=1;
    int i = 0;
    while (i < 6 && *verifica == 1){        
        if (password[i] != *(temporal+i))
            *verifica = 0;
        
        i++;
    } 
}

static void confirmar_nuevo_password(int * confirmar, char valor){
    
    guardar_current_password(valor);
    
    if (tamanio_password >= tam_pass && *confirmar){
        int i = 0;
        while (i < tam_pass && *confirmar){
            if (new_password[i] != current_password[i])
                *confirmar = 0;
            i++;
        }
    }
}

void actualizar_password(char valor){
    
    int confirmar=1;
    confirmar_nuevo_password(&confirmar,valor);
    
    if (confirmar && tamanio_password >= tam_pass){        
        
        int j;
        for (j=0; j < tam_pass; j++ )
            password[j] = new_password[j];        
        restaurar_comando(); 
        
        new_password[0] = 0;        
        temporal[0] = 0;        
        
        tamanio_new_password = 0;
        tamanio_password = 0;
    }
}

void borrar_nuevo_password(){
    *new_password = 0;
    tamanio_new_password = 0;
}

void borrar_temporal_password(){
    *temporal = 0;
    tamanio_password = 0;
}