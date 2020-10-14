/*
 * opamp.c
 *
 * Created: 23-Sep-20 11:22:30
 *  Author: M52422
 */ 

#include "opamp.h"

void op_amp_init()
{
    /*Disable input on op amp output pin*/
    PORTD.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;
    
    /*Set up op amp*/
    OPAMP.CTRLA = OPAMP_ENABLE_bm;
    OPAMP.TIMEBASE = OPAMP_TIMEBASE_US; /*Number of peripheral clock cycles that amounts to 1us*/
    OPAMP.OP0CTRLA = OPAMP_RUNSTBY_bm | OPAMP_ALWAYSON_bm | OPAMP_OP0CTRLA_OUTMODE_NORMAL_gc;
    
    /* Set op amp as a voltage follower with the DAC as input */
    OPAMP.OP0RESMUX = OPAMP_MUXWIP0_bm | OPAMP_OP0RESMUX_MUXBOT_OFF_gc | OPAMP_OP0RESMUX_MUXTOP_OFF_gc;
    OPAMP.OP0INMUX = OPAMP_OP0INMUX_MUXNEG_OUT_gc | OPAMP_OP0INMUX_MUXPOS_DAC_gc;
    OPAMP.OP0SETTLE = OPAMP_MAX_SETTLE_TIME; //As the settle time is unknown, the maximums should be set
    
    /* Wait for the operational amplifiers to settle */
    while (!(OPAMP.OP0STATUS & OPAMP_SETTLED_bm))
    {
        ;
    }
}
