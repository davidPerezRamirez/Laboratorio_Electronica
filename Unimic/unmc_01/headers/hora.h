#include <stdlib.h>


#define cantidad_elementos 3

char hour[cantidad_elementos] = "";
char minutes[cantidad_elementos] = "";

int tamanio_hora = 0;
int tamanio_minutos = 0;

static int valor_max;
static int valor_min;

void inicializar_hora();
void cambiar_hora(char);
void cambiar_minutos(char);

static void guardar_elemento_hora(char ,char * ,int * ,int * ,int * ,void *doit(int *,int *));
static void actualizar_hora(int * ,int * );
static void actualizar_minutos(int * , int * );
static void convertir_a_int_hora(char *, int *);