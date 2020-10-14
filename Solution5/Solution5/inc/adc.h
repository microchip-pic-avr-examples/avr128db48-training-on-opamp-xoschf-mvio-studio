/*
 * adc.h
 *
 * Created: 23-Sep-20 11:23:10
 *  Author: M52422
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define VREFF_ADC 1.024
#define ADC_RESOLUTION 4096

void adc0_init(void);
uint16_t read_VDDIO2();



#endif /* ADC_H_ */