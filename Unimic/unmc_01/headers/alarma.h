//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/// 
///Password
///
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 

#include <xc.h>
#include <unmc_inout_02.h>
#include <stdio.h>
#include <unmc_lcd_216.h>

#define tam_pass 6

char password[7];
char current_password[7];
char temporal[7];
char new_password[7];

int tamanio_password;
int tamanio_new_password;

int autorizado;
int encendida;
int activada;
int intentos_fallidos;

static void guardar_elemento_arreglo(char*,const char, int *);
void inicializar_alarmar();

void cancelar_cambio_password();
void inicializar_intentos_ingreso();

void guardar_current_password(const char);
void validar_password();

void verficar_password(int *);
void guardar_password_temporal(const char);
void guardar_nuevo_password(const char);
static void confirmar_nuevo_password(int *, char);
void actualizar_password(char);

void borrar_nuevo_password();
void borrar_temporal_password(); 
void borrar_current_password();

