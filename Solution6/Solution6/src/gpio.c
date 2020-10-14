/*
 * SW0.c
 *
 * Created: 29-Sep-20 09:50:14
 *  Author: M52422
 */ 

#include "gpio.h"

ISR(PORTB_PORT_vect)
{
    /*Clear the interrupt flag*/
    PORTB.INTFLAGS = PIN2_bm;
    /*Delay for debouncing*/
    _delay_ms(1);
    /*If VDDIO2 is withing acceptable range sett it bellow, if bellow acceptable range set it back to VDDIO2*/
    if(MVIO.STATUS & MVIO_VDDIO2S_bm){
        dac_set_voltage(VOLTAGE_BELLOW_ACAPTABLE_RANGE);
    } else {
        dac_set_voltage(VDDIO2);
    }
    
}