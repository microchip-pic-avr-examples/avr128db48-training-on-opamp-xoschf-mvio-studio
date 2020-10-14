/*
 * Solution6.c
 *
 * Created: 23-Sep-20 11:02:15
 * Author : M52422
 */ 

#include <avr/io.h>
#include "adc.h"
#include "dac.h"
#include "opamp.h"
#include "usart.h"


int main(void)
{
    adc0_init();
    dac_init();
    op_amp_init();
    usart_init();
    
    /* Set all PINs running on VDDIO2 to high so they can be measured */
    PORTC.DIRSET = 0xFF;;
    PORTC.OUTSET = 0xFF;
    while (1)
    {
        /*Read the VDDIO2 voltage continuously*/
        data_stream.vddio2 =  (read_VDDIO2()*VREFF_ADC*10*1000)/ADC_RESOLUTION; //Convert the ADC reading to millivolts
        DS_transmit_data();
    }
}








