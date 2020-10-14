/*
 * \file dac.c
 *
 * \brief Generating the sine wave as input for the OPAMP.
 *
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms,you may use this software and
 *  any derivatives exclusively with Microchip products.It is your responsibility
 *  to comply with third party license terms applicable to your use of third party
 *  software (including open source software) that may accompany Microchip software.
 *
 *  THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 *  EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 *  WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 *  PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 *  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 *  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 *  ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 *  THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 */

#include "dac.h"

void sine_wave_table_init(void)
{
  for(uint16_t i = 0; i < SINE_WAVE_STEPS; i++)
  {
    sine_wave[i] = SINE_DC_OFFSET + SINE_AMPLITUDE * sin(i * M_2PI / SINE_WAVE_STEPS);
  }
}

void DAC0_init(void)
{
    /*Create sinusoidal wave table of values*/
    sine_wave_table_init();
    
    /* DAC output pin */
    /* Disable digital input buffer */
    PORTD.PIN6CTRL &= ~PORT_ISC_gm;
    PORTD.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;
    /* Disable pull-up resistor */
    PORTD.PIN6CTRL &= ~PORT_PULLUPEN_bm;

    /* Select DAC Voltage reference and always one */
    VREF.DAC0REF |= VREF_REFSEL_1V024_gc | VREF_ALWAYSON_bm;
    
    /* Wait VREF start-up time */
    _delay_us(VREF_STARTUP_MICROS);

    DAC0_setVal(0x00);

    /* Enable DAC output to pin */
    DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm;

    DAC0_SineWaveTimer_init();
}


void DAC0_setVal(uint16_t val)
{
  DAC0.DATA = (val << DAC_DATA0_bp);
}

void DAC0_SineWaveTimer_init(void)
{
  /** Timer configured to overflow at ... **/
  SINE_WAVE_TIMER.CCMP = (F_CPU/SINE_WAVE_STEPS)/OUTPUT_FREQ;
  /* Clock prescaler */
  SINE_WAVE_TIMER.CTRLA = TCB_CLKSEL_DIV1_gc;
  SINE_WAVE_TIMER.INTCTRL = TCB_CAPT_bm;
}

void DAC0_SineWaveTimer_enable(void)
{
    SINE_WAVE_TIMER.CTRLA |= TCB_ENABLE_bm;
}

ISR(SINE_WAVE_TIMER_vect) {
    volatile static uint16_t sine_wave_index = 0;

    data_stream.dacVal = sine_wave[sine_wave_index];
    DAC0_setVal(data_stream.dacVal);
    sine_wave_index++;
    sine_wave_index = sine_wave_index % SINE_WAVE_STEPS;

    /* Clear interrupt flag */
    SINE_WAVE_TIMER.INTFLAGS = TCB_CAPT_bm;
}