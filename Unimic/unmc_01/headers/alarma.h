//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/// 
///Password
///
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 

#include <xc.h>
#include <unmc_inout_02.h>

#define tam_pass 6

char password[7]="123456";
char current_password[7]="";
char temporal[7] = "";
char new_password[7] = "";

int tamanio_password=0;
int tamanio_new_password=0;
int autorizado=0;
int encendida = 0;
int activada = 1;


void guardar_current_password(char);
void validar_password();

void verficar_password(int *);
void guardar_password_temporal(char);
void guardar_nuevo_password(char);
void actualizar_password(int *, char);

