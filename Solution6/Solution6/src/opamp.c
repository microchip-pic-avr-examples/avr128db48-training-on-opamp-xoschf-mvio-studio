/**
 * \file opamp.c
 *
 * \brief OPAMP driver source file.
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
