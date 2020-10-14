/*
 * gpio.h
 *
 * Created: 29-Sep-20 12:56:43
 *  Author: M52422
 */ 


#ifndef GPIO_H_
#define GPIO_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "dac.h"

static inline void SW0_init(void)
{
    /* Set pull up to be able to read the switch and enable interrupt on falling edges */
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc; //
}

static inline void LED0_init(void)
{
    PORTB.DIRSET = PIN3_bm;
    PORTB.OUTSET = PIN3_bm;
}

static inline void LED0_toggle(void)
{
    PORTB.OUTTGL = PIN3_bm;
}



#endif /* GPIO_H_ */