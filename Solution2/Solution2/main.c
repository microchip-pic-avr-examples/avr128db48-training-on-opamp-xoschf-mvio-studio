/*
 * Solution2.c
 *
 * Created: 29-Sep-20 14:46:48
 * Author : M52422
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