/**
 * \file main.c
 *
 * \brief Main source file.
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

#define F_CPU 16000000ul

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void CLOCK_XOSCHF_crystal_init(void);
void CLOCK_CFD_CLKMAIN_init(void);

static inline void LED0_init(void)
{
	PORTB.DIRSET = PIN3_bm;
}

static inline void LED0_toggle(void)
{
	PORTB.OUTTGL = PIN3_bm;
}

static inline void SW0_init(void)
{
    /* Set pull up to be able to read the switch and enable interrupt on falling edges */
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc; //
}


int main(void)
{
	CLOCK_XOSCHF_crystal_init();
	CLOCK_CFD_CLKMAIN_init();
	LED0_init();
    SW0_init();

	/* Enable global interrupts */
	sei();

	/* Replace with your application code */
	while(1)
	{
		LED0_toggle();
		_delay_ms(200);
	}
}


void CLOCK_XOSCHF_crystal_init(void)
{
	/* Enable crystal oscillator
	 * with frequency range 16MHz and 4K cycles start-up time
	 */
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL_RUNSTDBY_bm
	             | CLKCTRL_CSUTHF_4K_gc
	             | CLKCTRL_FRQRANGE_16M_gc
	             | CLKCTRL_SELHF_XTAL_gc
	             | CLKCTRL_ENABLE_bm);

	/* Confirm crystal oscillator start-up */
	while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_EXTS_bm))
	{
		;
	}

	/* Set the main clock to use XOSCHF as source, and enable the CLKOUT pin */
	ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_EXTCLK_gc
	             | CLKCTRL_CLKOUT_bm);

	/* Wait for system oscillator changing to complete */
	while(CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
	{
		;
	}

	/* Clear RUNSTDBY for power save when not in use */
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL.XOSCHFCTRLA & ~CLKCTRL_RUNSTDBY_bm);

	/* Change complete and the main clock is 16 MHz */
    ccp_write_io((uint8_t * ) &CLKCTRL.OSCHFCTRLA, (CLKCTRL.OSCHFCTRLA & ~CLKCTRL_FREQSEL_gm) | CLKCTRL_FREQSEL_8M_gc | CLKCTRL_RUNSTDBY_bm);
}


void CLOCK_CFD_CLKMAIN_init(void)
{
	/* Enable Clock Failure Detection on main clock */
	ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLC, CLKCTRL_CFDSRC_CLKMAIN_gc
	             | CLKCTRL_CFDEN_bm);

	/* Enable interrupt for CFD */
	ccp_write_io((uint8_t *) &CLKCTRL.MCLKINTCTRL, CLKCTRL_INTTYPE_bm
	             | CLKCTRL_CFD_bm);
}


ISR(NMI_vect)
{
	/* Check which NMI has triggered*/
	if(CLKCTRL.MCLKINTFLAGS & CLKCTRL_CFD_bm)
	{
		/* This interrupt will trigger if the source for the main clock fails
		* and the CFD is able to switch to a different working clock.
		* In this case that means XOSCHF has failed and is replaced by OSCHF.
		* The main clock is therefore reduced to 4 MHz.
		*/

		/* Toggle the LED forever */
		while(1)
		{
			LED0_toggle();
			_delay_ms(200); // 200 ms calculated from 16 MHz == 800 ms
		}

	}
	else
	{
		/* A different NMI has been triggered */
	}

	/* Non-Maskable Interrupt bits can only be cleared by a reset */
}

ISR(PORTB_PORT_vect)
{
    /*Clear the interrupt flag*/
    PORTB.INTFLAGS = PIN2_bm;
    /* Introduce the error condition into the CFD */
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLC, CLKCTRL.MCLKCTRLC | CLKCTRL_CFDTST_bm);
}