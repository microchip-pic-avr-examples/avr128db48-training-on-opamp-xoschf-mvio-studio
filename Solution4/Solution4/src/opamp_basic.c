/**
 * \file
 *
 * \brief OPAMP related functionality implementation.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
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

/**
 * \defgroup doc_driver_opamp_basic opamp Basic Driver
 * \ingroup doc_driver_opamp
 *
 * \section doc_driver_opamp_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <opamp_basic.h>

/**
 * \brief Initialize opamp interface
 * \return Initialization status.
 */
int8_t OPERATIONAL_AMPLIFIER_0_init()
{

	OPAMP.CTRLA = 1 << OPAMP_ENABLE_bp; /* OPAMP Peripheral Enable: enabled */

	// OPAMP.DBGCTRL = 0 << OPAMP_DBGRUN_bp; /* Run in Debug mode: disabled */

	OPAMP.TIMEBASE = OPAMP_TIMEBASE_VALUE << OPAMP_TIMEBASE_gp;

	// OPAMP.PWRCTRL = OPAMP_PWRCTRL_IRSEL_FULL_gc; /* Full Input Range */

	OPAMP.OP0SETTLE = 0x7f << OPAMP_SETTLE_gp; /* Setting: 0x7f */

	OPAMP.OP0CTRLA = 1 << OPAMP_ALWAYSON_bp             /* Always ON: enabled */
	                 | 0 << OPAMP_EVENTEN_bp            /* Event Enable: disabled */
	                 | OPAMP_OP0CTRLA_OUTMODE_NORMAL_gc /* Output Driver in Normal Mode */
	                 | 0 << OPAMP_RUNSTBY_bp;           /* Run is standby mode: disabled */

	OPAMP.OP0RESMUX = OPAMP_OP0RESMUX_MUXTOP_OUT_gc     /* OPn output */
	                  | OPAMP_OP0RESMUX_MUXBOT_GND_gc   /* Ground */
	                  | OPAMP_OP0RESMUX_MUXWIP_WIP3_gc; /* R1 = 8R, R2 = 8R, R2/R1 = 1 */

	OPAMP.OP0INMUX = OPAMP_OP0INMUX_MUXPOS_DAC_gc    /* DAC output */
	                 | OPAMP_OP0INMUX_MUXNEG_WIP_gc; /* Wiper from OPn's resistor ladder */

	return 0;
}

void OPERATIONAL_AMPLIFIER_0_EnableSystem()
{
	OPAMP.CTRLA |= OPAMP_ENABLE_bm;
}

void OPERATIONAL_AMPLIFIER_0_DisableSystem()
{
	OPAMP.CTRLA &= ~OPAMP_ENABLE_bm;
}

/* OP0 Basic Application Interfaces */

void OPERATIONAL_AMPLIFIER_0_SetOP0PositiveInMux(OPAMP_OP0INMUX_MUXPOS_t value)
{
	OPAMP.OP0INMUX = (OPAMP.OP0INMUX & ~OPAMP_MUXPOS_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP0NegativeInMux(OPAMP_OP0INMUX_MUXNEG_t value)
{
	OPAMP.OP0INMUX = (OPAMP.OP0INMUX & ~OPAMP_MUXNEG_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP0TopResMux(OPAMP_OP0RESMUX_MUXTOP_t value)
{
	OPAMP.OP0RESMUX = (OPAMP.OP0RESMUX & ~OPAMP_MUXTOP_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP0BottomResMux(OPAMP_OP0RESMUX_MUXBOT_t value)
{
	OPAMP.OP0RESMUX = (OPAMP.OP0RESMUX & ~OPAMP_MUXBOT_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP0WiperResMux(OPAMP_OP0RESMUX_MUXWIP_t value)
{
	OPAMP.OP0RESMUX = (OPAMP.OP0RESMUX & ~OPAMP_MUXWIP_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP0SettleTime(uint8_t settleTime)
{
	OPAMP.OP0SETTLE = settleTime;
}

bool OPERATIONAL_AMPLIFIER_0_OPAMP_IsOP0Settled(void)
{
	return OPAMP.OP0STATUS > 0;
}

void OPERATIONAL_AMPLIFIER_0_SetOP0OffsetCalibration(uint8_t calValue)
{
	OPAMP.OP0CAL = calValue;
}

/* OP1 Basic Application Interfaces */

void OPERATIONAL_AMPLIFIER_0_SetOP1PositiveInMux(OPAMP_OP1INMUX_MUXPOS_t value)
{
	OPAMP.OP1INMUX = (OPAMP.OP1INMUX & ~OPAMP_MUXPOS_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP1NegativeInMux(OPAMP_OP1INMUX_MUXNEG_t value)
{
	OPAMP.OP1INMUX = (OPAMP.OP1INMUX & ~OPAMP_MUXNEG_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP1TopResMux(OPAMP_OP1RESMUX_MUXTOP_t value)
{
	OPAMP.OP1RESMUX = (OPAMP.OP1RESMUX & ~OPAMP_MUXTOP_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP1BottomResMux(OPAMP_OP1RESMUX_MUXBOT_t value)
{
	OPAMP.OP1RESMUX = (OPAMP.OP1RESMUX & ~OPAMP_MUXBOT_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP1WiperResMux(OPAMP_OP1RESMUX_MUXWIP_t value)
{
	OPAMP.OP1RESMUX = (OPAMP.OP1RESMUX & ~OPAMP_MUXWIP_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP1SettleTime(uint8_t settleTime)
{
	OPAMP.OP1SETTLE = settleTime;
}

bool OPERATIONAL_AMPLIFIER_0_OPAMP_IsOP1Settled(void)
{
	return OPAMP.OP1STATUS > 0;
}

void OPERATIONAL_AMPLIFIER_0_SetOP1OffsetCalibration(uint8_t calValue)
{
	OPAMP.OP1CAL = calValue;
}

/* OP2 Basic Application Interfaces */

void OPERATIONAL_AMPLIFIER_0_SetOP2PositiveInMux(OPAMP_OP2INMUX_MUXPOS_t value)
{
	OPAMP.OP2INMUX = (OPAMP.OP2INMUX & ~OPAMP_MUXPOS_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP2NegativeInMux(OPAMP_OP2INMUX_MUXNEG_t value)
{
	OPAMP.OP2INMUX = (OPAMP.OP2INMUX & ~OPAMP_MUXNEG_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP2TopResMux(OPAMP_OP2RESMUX_MUXTOP_t value)
{
	OPAMP.OP2RESMUX = (OPAMP.OP2RESMUX & ~OPAMP_MUXTOP_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP2BottomResMux(OPAMP_OP2RESMUX_MUXBOT_t value)
{
	OPAMP.OP2RESMUX = (OPAMP.OP2RESMUX & ~OPAMP_MUXBOT_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP2WiperResMux(OPAMP_OP2RESMUX_MUXWIP_t value)
{
	OPAMP.OP2RESMUX = (OPAMP.OP2RESMUX & ~OPAMP_MUXWIP_gm) | value;
}

void OPERATIONAL_AMPLIFIER_0_SetOP2SettleTime(uint8_t settleTime)
{
	OPAMP.OP2SETTLE = settleTime;
}

bool OPERATIONAL_AMPLIFIER_0_OPAMP_IsOP2Settled(void)
{
	return OPAMP.OP2STATUS > 0;
}

void OPERATIONAL_AMPLIFIER_0_SetOP2OffsetCalibration(uint8_t calValue)
{
	OPAMP.OP2CAL = calValue;
}
