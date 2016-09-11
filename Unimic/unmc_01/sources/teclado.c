//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
///
/// Teclado
///
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[   

#include <teclado.h>
#include <stdio.h>

void guardar_comando(char tecla){
    
    unsigned char aux[20];
    sprintf(aux,"%01u",tecla);
    if (tamanio_comando < 2){
        comando[tamanio_comando] = *aux;      
        comando [tamanio_comando+1] = 0;
        tamanio_comando++;
    }    
}

void guardar_array_comando(char * array_comando){
    comando[0] = array_comando[0];
    comando[1] = array_comando[1];
    comando[2] = 0;
    
    tamanio_comando = 2;
}

void validar_comando(char * candidato, int * validar){
    
    *validar=1;
    int i = 0;
    while (i < 2 && *validar == 1){        
        if (comando[i] != *(candidato+i))
            *validar = 0;
        
        i++;
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

void restaurar_comando(){
     tamanio_comando = 0;

     comando[0]='x';
     comando[1]='x';
     comando[2]=0;     
 }
    
void guardar_tecla_presionada(char * letra, int i,char* (*doit)(char *)){
    if (column1==1){key=i;doit(key);while(column1==1){};}
    if (column2==1){key=(i)+1;doit(key);while(column2==1){};}
    if (column3==1){key=(i)+2;doit(key);while(column3==1){};}
    if (column4==1){key=letra[0];/**(i)+10;lcd_putrs(letra);while(column4==1){};**/}
}

void leer_teclado(int ocultar,char* (*doit)()){
    int i;
    ocultar_teclas = ocultar;
    
    row1=1;row2=0;row3=0;row4=0;i=1;
    guardar_tecla_presionada("A",i,doit);
    
    row1=0;row2=1;row3=0;row4=0;i=4;
    guardar_tecla_presionada("B",i,doit);
    
    row1=0;row2=0;row3=1;row4=0;i=7;
    guardar_tecla_presionada("C",i,doit);
    
    row1=0;row2=0;row3=0;row4=1;
    {
        if (column1==1){key='*';lcd_putrs("*");while(column1==1){};}
        if (column2==1){key=0;doit(key);while(column2==1){};}
        if (column3==1){key='#';lcd_putrs("#");while(column3==1){};}
        if (column4==1){key='D';lcd_putrs("D");while(column4==1){};}
    }
    __delay_ms(98);             // 98ms retardo maximo para esta funcion

}