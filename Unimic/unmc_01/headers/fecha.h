#include <stdlib.h>
#include <unmc_rtcc_02.h>

#define cantidad_elementos 3

char day[cantidad_elementos] = "";
char month[cantidad_elementos] = "";
char year[cantidad_elementos] = "";

int tamanio_dia = 0;
int tamanio_mes = 0;
int tamanio_anio = 0;

void inicializar();
void guardar_elemento(char, char *, int *);
void convertir_a_int(char *, int *);
void cambiar_dia(char);
void cambiar_mes(char);
void cambiar_anio(char);
void cambiar_fecha(char);