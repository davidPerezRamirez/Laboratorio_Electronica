#include <stdlib.h>
#include <unmc_rtcc_02.h>

#define cantidad_elementos 3

static char day[cantidad_elementos] = "";
static char month[cantidad_elementos] = "";
static char year[cantidad_elementos] = "";

static char hour[cantidad_elementos] = "";
static char minutes[cantidad_elementos] = "";

int tamanio_hora = 0;
int tamanio_minutos = 0;

int tamanio_dia = 0;
int tamanio_mes = 0;
int tamanio_anio = 0;

static int valor_max;
static int valor_min;

static void convertir_a_int(char *, int *);
static void guardar_elemento(char ,char * ,int * ,int ,int * ,void (*doit) (int *,const int));
static void actualiza_elemento(int *,const int);
static void obtener_dia_mes();

static void actualiza_dia(int *,const int);
void inicializar_fecha();
void cambiar_dia(char);
void cambiar_mes(char);
void cambiar_anio(char);

static void actualizar_hora(int * ,const int );
static void actualizar_minutos(int * ,const int );
void inicializar_hora();
void cambiar_hora(char);
void cambiar_minutos(char);

