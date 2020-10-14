/*
 * opamp.h
 *
 * Created: 23-Sep-20 11:23:31
 *  Author: M52422
 */ 


#ifndef OPAMP_H_
#define OPAMP_H_

#include <avr/io.h>
#include <math.h>

#define OPAMP_MAX_SETTLE_TIME 0x7F
#define OPAMP_TIMEBASE_US     (ceil(F_CPU /1e6)-1)

void op_amp_init();



#endif /* OPAMP_H_ */