//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
///
/// Teclado
///
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[   

#include <teclado.h>
#include <stdio.h>

void restaurar_comando(){
     tamanio_comando = 0;

    comando[0] = 'x';
    comando[1] = 'x';
    comando[2] = 0;
     
 }

void guardar_comando(char tecla){
    
    unsigned char aux[20];
    sprintf(aux,"%01u",tecla);
    if (tamanio_comando < 2){
        comando[tamanio_comando] = *aux;      
        comando [tamanio_comando+1] = 0;
        tamanio_comando++;
    }    
}

void imprimir_tecla(char tecla){    
    
    unsigned char aux[20];
    sprintf(aux,"%01u",tecla);
    if (ocultar_teclas == 1){
        lcd_putrs("*");
    }else{        
        lcd_putrs(aux);
    }               
}
    
static void guardar_tecla_presionada(const char * letra, int i){
    if (column1==1){key=i;puntero_funcion(key);while(column1==1){};}
    if (column2==1){key=(i)+1;puntero_funcion(key);while(column2==1){};}
    if (column3==1){key=(i)+2;puntero_funcion(key);while(column3==1){};}
    if (column4==1){key=letra[0];/**(i)+10;lcd_putrs(letra);while(column4==1){};**/}
}

void leer_teclado(int ocultar){
    int i;
    ocultar_teclas = ocultar;
    
    row1=1;row2=0;row3=0;row4=0;i=1;
    guardar_tecla_presionada("A",i);
    
    row1=0;row2=1;row3=0;row4=0;i=4;
    guardar_tecla_presionada("B",i);
    
    row1=0;row2=0;row3=1;row4=0;i=7;
    guardar_tecla_presionada("C",i);
    
    row1=0;row2=0;row3=0;row4=1;
    {
        if (column1==1){key='*';lcd_putrs("*");while(column1==1){};}
        if (column2==1){key=0;puntero_funcion(key);while(column2==1){};}
        if (column3==1){key='#';lcd_putrs("#");while(column3==1){};}
        if (column4==1){key='D';lcd_putrs("D");while(column4==1){};}
    }
    __delay_ms(98);             // 98ms retardo maximo para esta funcion

}