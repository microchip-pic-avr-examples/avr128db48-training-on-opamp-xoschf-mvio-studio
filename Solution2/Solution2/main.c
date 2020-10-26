/**
 * \file main.c
 *
 * \brief main source file.
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

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

#define PERIOD 512

void CLOCK_OSCHF_crystal_PLL_init(void);
void TIMER_TCD0_init(void);

int main(void)
{
    CLOCK_OSCHF_crystal_PLL_init();
    TIMER_TCD0_init();
    sei();
    
    /* Replace with your application code */
    while(1)
    {
    }
}


void CLOCK_OSCHF_crystal_PLL_init(void)
{
    /* Set the OSCHF frequency to 16 MHz */
    ccp_write_io((uint8_t *)&CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_16M_gc);

    /* Set the PLL to use OSCHF as source, and select 3x multiplication factor */
    ccp_write_io((uint8_t *) &CLKCTRL.PLLCTRLA, CLKCTRL_MULFAC_3x_gc);
}


void TIMER_TCD0_init(void)
{
    /* Configure the TCD with PLL (48 MHz) as source */
    TCD0.CTRLA = TCD_CLKSEL_PLL_gc | TCD_CNTPRES_DIV1_gc | TCD_SYNCPRES_DIV1_gc;
    
    /*Set one ramp mode*/
    TCD0.CTRLB = TCD_WGMODE_ONERAMP_gc;
    
    /*Set TCD pins as output*/
    PORTA.DIRSET = PIN4_bm | PIN5_bm;
    ccp_write_io((uint8_t *) &TCD0.FAULTCTRL, TCD_CMPAEN_bm | TCD_CMPBEN_bm);
    
    TCD0.INTCTRL = TCD_OVF_bm; // Enable overflow interrupts
     
    
    /*Set the period and duty cycle of the PWM signals*/
    TCD0.CMPASET = 0;
    TCD0.CMPBSET = 0;
    
    TCD0.CMPACLR = 1;
    TCD0.CMPBCLR = PERIOD;
    

    /* Wait for synchronization */
    while(!(TCD0.STATUS & TCD_ENRDY_bm))
    {
        ;
    }
    /* Enable TCD0 */
    TCD0.CTRLA |= TCD_ENABLE_bm;
}

ISR(TCD0_OVF_vect)
{
    TCD0.INTFLAGS = TCD_OVF_bm; //Clear overflow flag
    
    /* Wait for no synchronization */
    while(!(TCD0.STATUS & TCD_CMDRDY_bm))
    {
        ;
    }
    
    /* Update WOA duty cycle */
    TCD0.CMPACLR = (TCD0.CMPACLR + 1)%PERIOD;
    /* Synchronize the update at the end of the next cycle */
    TCD0.CTRLE = TCD_SYNCEOC_bm;
    
}