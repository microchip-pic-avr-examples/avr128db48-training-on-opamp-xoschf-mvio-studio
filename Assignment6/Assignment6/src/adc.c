/*
 * adc.c
 *
 * Created: 23-Sep-20 11:22:41
 *  Author: M52422
 */ 

#include "adc.h"

void adc0_init(void)
{
    /*Select the 1.024V reference for ADC0*/
    VREF.ADC0REF = VREF_REFSEL_1V024_gc;
    
    /*Configure accumulation of 16 samples*/
    ADC0.CTRLB = ADC_SAMPNUM_ACC16_gc;
    
    
    /*Select VDDIO2DIV10 as input for ADC0*/
    ADC0.MUXPOS = ADC_MUXPOS_VDDIO2DIV10_gc;

    /*Enable ADC0*/
    ADC0.CTRLA = ADC_ENABLE_bm;// | ADC_CONVMODE_bm | ADC_RESSEL_12BIT_gc;
}

uint16_t read_VDDIO2()
{
    /*Measure VDDIO2 using the internal ADC*/

    /*Start an ADC conversion*/
    ADC0.COMMAND = ADC_STCONV_bm;

    /*Wait for the ADC conversion to be done*/
    while(!(ADC0.INTFLAGS & ADC_RESRDY_bm));
    
    /*Read the RES register and shift the result 4 bits to compensate for the 16 over samples, the result is actual voltage divided by 10*/
    volatile uint16_t result = (ADC0.RES>>4);
    
    return result;
}