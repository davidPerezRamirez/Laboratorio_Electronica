//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
///
/// Teclado
///
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[   

#include <delays.h>
#include <unmc_lcd_216.h>
#include <unmc_inout_02.h>
#include <unmc_config_01.h>

int ocultar_teclas; //voy a ocultar las teclas cuando ingrese contrasenia
char comando[3]="xx";
int tamanio_comando = 0;

void guardar_comando(char);
void guardar_array_comando(char *);
void validar_comando(char *, int *);
void imprimir_tecla(char);
void restaurar_comando();
void guardar_tecla_presionada(char *, int,char* (*doit)(char *));
void leer_teclado(int ocultar,char* (*doit)());