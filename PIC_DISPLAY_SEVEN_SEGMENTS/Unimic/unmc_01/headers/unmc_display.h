/* 
 * File:   unmc_inout_display.h
 * Author: ddavi
 *
 * Created on 6 de octubre de 2016, 19:20
 */

#ifndef UNMC_INOUT_DISPLAY_H
#define	UNMC_INOUT_DISPLAY_H

#include <xc.h>
#include <unmc_inout_01.h>
#include <unmc_config_01.h>

    void number_0();
    void number_1();
    void number_2();
    void number_3();
    void number_4();
    void number_5();
    void number_6();
    void number_7();
    void number_8();
    void number_9(); 
    
    void apagar_segmentos();
    void construir_numero(int );
    void tiempo_encendido_segmento();
    void mostrar_fuera_rango();


#endif	/* UNMC_INOUT_DISPLAY_H */

