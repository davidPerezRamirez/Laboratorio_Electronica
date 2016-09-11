#include <stdlib.h>


#define cantidad_elementos 3

char hour[cantidad_elementos] = "";
char minutes[cantidad_elementos] = "";

int tamanio_hora = 0;
int tamanio_minutos = 0;

void inicializar_hora();
void guardar_elemento_hora(char, char *, int *);
void convertir_a_int_hora(char *, int *);
void cambiar_hora(char);
void cambiar_minutos(char);