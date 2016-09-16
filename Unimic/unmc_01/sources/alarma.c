#include <alarma.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void guardar_current_password(char valor){
    
    //La constrasenia no tendrá mas de 6 digitos
    if (tamanio_password < tam_pass){
        current_password[tamanio_password] = valor;      
        current_password [tamanio_password+1] = '\0';
        tamanio_password++;
    }
}

void guardar_password_temporal(char valor){
     //La constrasenia no tendrá mas de 6 digitos
    if (tamanio_password < tam_pass){
        temporal[tamanio_password] = valor;      
        temporal [tamanio_password+1] = '\0';
        tamanio_password++;
    }           
}

void guardar_nuevo_password(char valor){
     //La constrasenia no tendrá mas de 6 digitos
    if (tamanio_new_password < tam_pass){
        new_password[tamanio_new_password] = valor;      
        new_password [tamanio_new_password+1] = 0;
        tamanio_new_password++;
    }        
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

void actualizar_password(int * confirmar, char valor){
    
    *confirmar=1;
    int j=0;
    
    if ( *confirmar == 1 && tamanio_new_password - tam_pass - 1 < tam_pass){        
        if (new_password[tamanio_new_password - tam_pass - 1] != valor)
            *confirmar = 0;
        
        else
            tamanio_new_password++;                
    }
    
    if (*confirmar && tamanio_new_password - tam_pass - 1 >= tam_pass){        
        
        for (int j=0; j < tam_pass; j++ )
            password[j] = new_password[j];
        
        restaurar_comando(); 
        
        new_password[0] = 0;        
        temporal[0] = 0;        
        
        tamanio_new_password = 0;
        tamanio_password = 0;
    }
}

