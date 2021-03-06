/*********************************************************************
 *
 *                Unimic XC8  Version 1.1   10 September 2015
 *
 *********************************************************************
 * FileName:        unmc_config_01.h
 * Dependencies:
 * Processor:       PIC18F26J50
 * Compiler:        XC8 1.34
 * Company:         Microchip Technology, Inc.
 *
 *********************************************************************/

char key;         //variable key

//
///** L E D **********************************************************/

#define LED_1           LATBbits.LATB2
#define LED_2           LATBbits.LATB1
#define LED_3           LATBbits.LATB0

#define LED_1_On        LED_1 = 1;
#define LED_2_On        LED_2 = 1;
#define LED_3_On        LED_3 = 1;

#define LED_1_Off       LED_1 = 0;
#define LED_2_Off       LED_2 = 0;
#define LED_3_Off       LED_3 = 0;

#define LED_1_Toggle    LED_1 = !LED_1;
#define LED_2_Toggle    LED_2 = !LED_2;
#define LED_3_Toggle    LED_3 = !LED_3;

#define Speaker          LATCbits.LATC7
#define Speaker_On       Speaker = 1;
#define Speaker_Off      Speaker = 0;

//
///** S W I T C H *****************************************************/
#define switch1         PORTAbits.RA1
#define switch2         PORTAbits.RA0

///** KEYBOARD *****************************************************/
#define row1            LATAbits.LATA0
#define row2            LATAbits.LATA1
#define row3            LATAbits.LATA2
#define row4            LATAbits.LATA3
#define column1         PORTAbits.RA5
#define column2         PORTAbits.RA7
#define column3         PORTAbits.RA6
#define column4         PORTCbits.RC2

/********************************************************************/

#define lista_leds_rojo_on       row4=1;
#define lista_leds_rojo_off      row4=0;
#define lista_leds_verde         LATAbits.LATA5
#define lista_leds_verde_on      lista_leds_verde = 1;
#define lista_leds_verde_off     lista_leds_verde = 0; 
#define lista_leds_azul          LATAbits.LATA7
#define lista_leds_azul_on       lista_leds_azul = 1;
#define lista_leds_azul_off      lista_leds_azul = 0;

