/*********************************************************************
 *
 *                Unimic 01 Version 1.1   10 September 2015
 *
 ***********************************************************************
 * FileName:        unmc_rtcc_01.h
 * Dependencies:    
 * Processor:       PIC18F26J50
 * Compiler:        XC8 1.34
 * Company:         Microchip Technology, Inc.
 *
 ***********************************************************************/

#include<plib/rtcc.h>

rtccTimeDate RtccTimeDate ,RtccAlrmTimeDate, Rtcc_read_TimeDate ;

char segundo_u;         //variables BCD donde se guradan o leen los
char segundo_d;         //datos del RTCC
char minuto_u;
char minuto_d;
char hora_u;
char hora_d;
char fecha_u;
char fecha_d;
char mes_u;
char mes_d;
char dia_semana;
char anio_u;
char anio_d;
bit flag=0;
int i=0;
int j=0;
int a=0;
int b=0;
int c=0;
int k=0;
int anio=15;                //año 2013 -> 00001110
int mes=9;                  //mes enero-> 00000001 (1) .... dici-> 00001100 (12)
int diasem=3;               //0 Dom , 1 Lun , 2 Mar......, 6 Sab
int dia=8;                  //dia 01 -> 00000001.....31 -> 00011111
int hora=18;                 //hora 00 -> 00000000.....24 -> 00011000
int minuto=30;               //variables de numeros enteros que permiten
int segundo=0;              //representar los valores en el LCD

//---Global structures used in deep sleep library---
//rtccTimeDate, RtccTimeDate ,RtccAlrmTimeDate, Rtcc_read_TimeDate ;

rtccTime RtccTime; // Inicializa la estructura de tiempo
rtccTime RtccTimeVal;
rtccDate RtccDate;//Inicializa la estructura de Fecha

unsigned char buffer2[20];

void DelayFor18TCY(void);
void DelayPORXLCD(void);
void Write_RTC(void);
void Read_RTC(void);

