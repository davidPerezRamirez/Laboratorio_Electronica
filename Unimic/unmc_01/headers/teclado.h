//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
///
/// Teclado
///
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[   

#include <delays.h>
#include <unmc_lcd_216.h>
#include <unmc_inout_03.h>
#include <unmc_config_01.h>

int ocultar_teclas; //voy a ocultar las teclas cuando ingrese contrasenia
char comando[3];
int tamanio_comando;

void (*puntero_funcion)(char);
void (*funcion_pulsador_C)(void);
void (*funcion_pulsador_D)(void);
void (*funcion_pulsador_B)(void);

void inicializar_teclado();
void guardar_comando(char);
void imprimir_tecla(char);
void restaurar_comando();
static void guardar_tecla_presionada(int);
void leer_teclado(int ocultar);