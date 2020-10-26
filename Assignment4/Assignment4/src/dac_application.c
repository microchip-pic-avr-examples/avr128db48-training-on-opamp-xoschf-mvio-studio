/**
 * \file dac_application.c
 *
 * \brief DAC application source file.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
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