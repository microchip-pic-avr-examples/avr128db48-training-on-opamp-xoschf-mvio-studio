/*
 * \file adc.c
 *
 * \brief ADC conversion of the OPAMP output signal.
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

extern data_visualizer data_stream;

void ADC0_init(void)
{
    /* Disable digital input buffer */
    PORTD.PIN2CTRL |= PORT_ISC_INPUT_DISABLE_gc;
  
    /* Disable pull-up resistor */
    PORTD.PIN2CTRL &= ~PORT_PULLUPEN_bm;

    ADC0.CTRLC = ADC_PRESC_DIV12_gc;      /* CLK_PER divided by 12 */

    VREF.ADC0REF |= VREF_REFSEL_1V024_gc; /* 1.024 reference */

    ADC0.CTRLA = ADC_ENABLE_bm          /* ADC Enable: enabled */
                | ADC_RESSEL_10BIT_gc;   /* 10-bit mode */
                
    ADC0.MUXPOS  = ADC_MUXPOS_AIN2_gc;

    /* Result Ready Interrupt Enable */
    ADC0.INTCTRL = ADC_RESRDY_bm;

    /* Set the accumulator mode to accumulate 8 samples */
    ADC0.CTRLB = ADC_SAMPLES;
  
    ADC0_SampleTimer_init();
}

ISR (ADC0_RESRDY_vect)
{
    data_stream.data_available = 1;
    data_stream.opampVal =  (ADC0.RES >> ADC_SAMPLES);
    DS_start_data_transmit();
}

void ADC0_StartConversion(void)
{
    /* Start ADC conversion */
    ADC0.COMMAND = ADC_STCONV_bm;
}

void ADC0_SampleTimer_init(void)
{
    /** Timer configured to overflow at ...Hz **/
    ADC_SAMPLE_TIMER.CCMP = (F_CPU/SAMPLE_NUM)/OUTPUT_FREQ;
    /* Clock prescaler */
    ADC_SAMPLE_TIMER.CTRLA = TCB_CLKSEL_DIV1_gc;
    ADC_SAMPLE_TIMER.INTCTRL = TCB_CAPT_bm;
}

void ADC0_SampleTimer_enable(void)
{
    ADC_SAMPLE_TIMER.CTRLA |= TCB_ENABLE_bm;
}

ISR(ADC_SAMPLE_TIMER_vect) {
    if (data_stream.data_available == 0) {
        ADC0_StartConversion();
    }

    /* Clear interrupt flag */
    ADC_SAMPLE_TIMER.INTFLAGS = TCB_CAPT_bm;
}