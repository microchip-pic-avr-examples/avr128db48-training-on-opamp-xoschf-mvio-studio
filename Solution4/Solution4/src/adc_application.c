/*
 * adc.c
 *
 * Created: 16-Jun-20 10:57:20
 *  Author: M52422
 */ 

#include "adc_application.h"

extern data_visualizer data_stream;


void ADC_cb()
{
    data_stream.data_available = 1;
    data_stream.opampVal = ADC_0_get_conversion_result() >> 3; //Avarage 8 conversions. 
    DS_start_data_transmit();
}

void ADC0_SampleTimer_enable(void)
{
    ADC_SAMPLE_TIMER.CTRLA |= TCB_ENABLE_bm;
}

ISR(ADC_SAMPLE_TIMER_vect)
{
    if(!(USART3.CTRLA & USART_DREIE_bm)) {
        ADC_0_start_conversion(ADC_MUXPOS_AIN2_gc);
    }
    
    /* Clear interrupt flag */
    ADC_SAMPLE_TIMER.INTFLAGS = TCB_CAPT_bm;
}