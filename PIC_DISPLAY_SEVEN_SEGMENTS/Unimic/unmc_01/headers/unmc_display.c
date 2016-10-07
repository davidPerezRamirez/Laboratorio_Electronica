#include <unmc_display.h>

void tiempo_encendido_segmento(){
    __delay_ms(1);
}
void encender_A(){
   DSS_A_On;    
    tiempo_encendido_segmento();
    DSS_A_Off; 
}

void encender_B(){
   DSS_B_On;    
   tiempo_encendido_segmento();
   DSS_B_Off; 
}

void encender_C(){
   DSS_C_On;    
   tiempo_encendido_segmento();
   DSS_C_Off; 
}

void encender_D(){
   DSS_D_On;    
   tiempo_encendido_segmento();
   DSS_D_Off; 
}

void encender_E(){
   DSS_E_On;    
   tiempo_encendido_segmento();
   DSS_E_Off; 
}

void encender_F(){
   DSS_F_On;    
   tiempo_encendido_segmento();
   DSS_F_Off; 
}

void encender_G(){
   DSS_G_On;    
   tiempo_encendido_segmento();
   DSS_G_Off; 
}

void apagar_segmentos(){
    DSS_A_Off;
    DSS_B_Off;
    DSS_C_Off;
    DSS_D_Off;
    DSS_E_Off;
    DSS_F_Off;
    DSS_G_Off;
}

void number_0(void){
    encender_A();
    encender_B();
    encender_C();
    encender_D();
    encender_E();
    encender_F();     
}

void number_1(void){     
    encender_B();
    encender_C();
}

void number_2(void){
    encender_A();
    encender_B();  
    encender_D();
    encender_E();
    encender_G(); 
}

void number_3(void){    
    encender_A();
    encender_B();
    encender_C();
    encender_D();
    encender_G(); 
}

void number_4(void){       
    encender_B();
    encender_C();        
    encender_F();
    encender_G();    
}

void number_5(void){
    encender_A();    
    encender_C();
    encender_D();    
    encender_F();
    encender_G();
}

void number_6(void){    
    encender_A();    
    encender_C();
    encender_D();
    encender_E();
    encender_F();
    encender_G();
}

void number_7(void){
    encender_A();
    encender_B();
    encender_C();
}

void number_8(void){
    encender_A();
    encender_B();
    encender_C();
    encender_D();
    encender_E();
    encender_F();
    encender_G();
}

void number_9(void){   
    encender_A();
    encender_B();
    encender_C();
    encender_D();    
    encender_F();
    encender_G();    
}

void construir_numero(int number){
    apagar_segmentos();
    switch(number){
        case 0:
            number_0();
            break;
        case 1:
            number_1();
            break;
        case 2:
            number_2();
            break;
        case 3:
            number_3();
            break;
        case 4:
            number_4();
            break;
        case 5:
            number_5();
            break;
        case 6:
            number_6();
            break;
        case 7:
            number_7();
            break;
        case 8:
            number_8();
            break;
        case 9:
            number_9();
            break;
    }
}