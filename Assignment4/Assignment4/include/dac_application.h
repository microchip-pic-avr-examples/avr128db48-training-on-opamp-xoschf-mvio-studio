/*
 * dac.h
 *
 * Created: 16-Jun-20 11:13:55
 *  Author: M52422
 */ 


#ifndef DAC_H_
#define DAC_H_


#include <math.h>
#include <avr/interrupt.h>
#include "adc_application.h"



#define DEGREE 0.0245   //2pi /256 = 6.28/ 256.

#define SINE_WAVE_TIMER                  TCB0

#define SINE_WAVE_TIMER_vect             TCB0_INT_vect

/* VREF Startup time */
#define VREF_STARTUP_MICROS              (25)

/* REsolution of DAC */
#define DAC0_RESOLUTION                  (0x3FF)

/*Amplitude Volts*/
#define SINE_WAVE_AMPLITUDE_VOLTS		(0.092)
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

void sin_wave_table_init(void);

void DAC0_SineWaveTimer_enable(void);


#endif /* DAC_H_ */