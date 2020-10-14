/*
 * dac.c
 *
 * Created: 16-Jun-20 11:14:12
 *  Author: M52422
 */ 

#include "dac_application.h"


void sin_wave_table_init(void)
{
    //uint16_t sine_amplitude = ((uint32_t)SINE_WAVE_AMPLITUDE_MVOLTS * 1024)/DAC_VOLTAGE_REF_MVOLTS;

    //uint16_t sine_dc_offset = ((uint32_t)SINE_DC_OFFSET_MVOLTS * 1024 )/DAC_VOLTAGE_REF_MVOLTS;

    for(uint16_t i = 0; i < SINE_WAVE_STEPS; i++)
    {
        sine_wave[i] = SINE_DC_OFFSET + SINE_AMPLITUDE * sin(i * M_2PI / SINE_WAVE_STEPS);;
    }
}

void DAC0_SineWaveTimer_enable(void)
{
    SINE_WAVE_TIMER.CTRLA |= TCB_ENABLE_bm;
}

ISR(SINE_WAVE_TIMER_vect)
{
    volatile static uint16_t sine_wave_index = 0;
    
    data_stream.dacVal = sine_wave[sine_wave_index];
    DAC_0_set_output(data_stream.dacVal);
    sine_wave_index++;
    sine_wave_index = sine_wave_index % SINE_WAVE_STEPS;
    
    SINE_WAVE_TIMER.INTFLAGS = TCB_CAPT_bm;
}