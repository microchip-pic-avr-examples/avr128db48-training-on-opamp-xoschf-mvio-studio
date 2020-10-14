/*
 * \file dac.h
 *
 * \brief
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

#ifndef DAC_H_
#define DAC_H_

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

#include "adc.h"

#define DEGREE 0.0245   //2pi /256 = 6.28/ 256.

#define SINE_WAVE_TIMER                  TCB0

#define SINE_WAVE_TIMER_vect             TCB0_INT_vect

/* VREF Startup time */
#define VREF_STARTUP_MICROS              (25)

/* REsolution of DAC */
#define DAC0_RESOLUTION                  (0x3FF)

/*Amplitude Volts*/
#define SINE_WAVE_AMPLITUDE_VOLTS		(0.128)
/*Offset Volts*/
#define SINE_DC_OFFSET_VOLTS			(0.256)
/*DAC Voltage Reference*/
#define DAC_VOLTAGE_REF					(1.024)
/* Number of steps for a sine wave period */
#define SINE_WAVE_STEPS                  (92)
/* Sine wave amplitude */
#define SINE_AMPLITUDE                   (uint16_t)(SINE_WAVE_AMPLITUDE_VOLTS/DAC_VOLTAGE_REF*DAC0_RESOLUTION)
/* Sine wave DC offset */
#define SINE_DC_OFFSET                   (uint16_t)(SINE_DC_OFFSET_VOLTS/DAC_VOLTAGE_REF*DAC0_RESOLUTION)
/* 2*PI */
#define M_2PI                            (2 * M_PI)
/* Frequency of the sine wave */
#define OUTPUT_FREQ                      (25)

/* Buffer to store the sine wave samples */
uint16_t sine_wave[SINE_WAVE_STEPS];

void DAC0_init(void);
void DAC0_setVal(uint16_t val);

void sine_wave_table_init(void);

void DAC0_SineWaveTimer_init(void);

void DAC0_SineWaveTimer_enable(void);

#endif /* DAC_H_ */
