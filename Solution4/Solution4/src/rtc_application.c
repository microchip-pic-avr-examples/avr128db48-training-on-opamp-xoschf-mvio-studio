/*
 * rtc_application.c
 *
 * Created: 18-Aug-20 19:34:23
 *  Author: M52422
 */ 

#include "rtc_application.h"

void RTC_enable(void)
{
    while(RTC.STATUS & RTC_CTRLABUSY_bm){
    } //Wait for RTC CTRAL to be unsynchronized
    RTC.CTRLA |= RTC_RTCEN_bm; //Enable RTC
}

ISR(RTC_CNT_vect)
{

    /* Insert your RTC Overflow interrupt handling code */
    LED0_toggle_level();
    /* Overflow interrupt flag has to be cleared manually */
    RTC.INTFLAGS = RTC_OVF_bm;
}