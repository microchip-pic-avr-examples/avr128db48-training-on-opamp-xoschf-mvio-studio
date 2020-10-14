/*
 * dac.h
 *
 * Created: 23-Sep-20 11:23:18
 *  Author: M52422
 */ 


#ifndef DAC_H_
#define DAC_H_

#include <avr/io.h>

#define VDD 3.33
#define VDDIO2 1.8
#define VOLTAGE_BELLOW_ACAPTABLE_RANGE 1.5

void dac_init();
void dac_set_voltage(float v_out);

#endif /* DAC_H_ */