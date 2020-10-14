/*
 * \file rtc.c
 *
 * \brief RTC generates a 2Hz interrupt. In the interrupt the LED is toggled. 
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

#include "rtc.h"

void RTC_init(void)
{
    /* Initialize RTC: */
    while (RTC.STATUS > 0)
    {
        ; /* Wait for all register to be synchronized */
    }

    /* Set period */
    RTC.PER = RTC_PERIOD;

    /* 32.768kHz Internal Crystal Oscillator */
    RTC.CLKSEL = RTC_CLKSEL_OSC32K_gc;

    RTC.CTRLA = RTC_PRESCALER_DIV32_gc  /* 32 */
                | RTC_RUNSTDBY_bm;      /* Run In Standby: enabled */

    /* clear Interrupt flags */
    RTC.INTFLAGS = RTC_OVF_bm | RTC_CMP_bm;

    /* Enable Overflow Interrupt */
    RTC.INTCTRL |= RTC_OVF_bm;
}

void RTC_enable(void)
{
    RTC.CTRLA |= RTC_RTCEN_bm;      /* Enable */
}

ISR(RTC_CNT_vect)
{
    /* Clear flag by writing '1': */
    RTC.INTFLAGS = RTC_OVF_bm;

    LED0_toggle();
}

void LED0_init(void)
{
    // Set (PB3) as output
    PORTB.DIR |= PIN3_bm;
}

void LED0_toggle(void)
{
    // Toggle LED0 (PB3)
    PORTB.OUTTGL = PIN3_bm;
}