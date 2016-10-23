#include <password.h>

void guardar_current_password(char valor){
    
    //La constrasenia no tendrá mas de 6 digitos
    if (tamanio_password < 6){
        current_password[tamanio_password] = valor;      
        current_password [tamanio_password+1] = '\0';
        tamanio_password++;
    }    
}

void validar_password(){
    
    autorizado = 1;
    int i = 0;
    while (i < 6 && autorizado==1){
        
        if (current_password[i] != password[i])
            autorizado = 0;
        
        i++;
    }
}