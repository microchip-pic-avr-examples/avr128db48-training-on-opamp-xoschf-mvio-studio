/*
 * dac.c
 *
 * Created: 23-Sep-20 11:23:01
 *  Author: M52422
 */ 


#include "dac.h"

void dac_init()
{
    /*Setting the reference for the DAC to VDD*/
    VREF.DAC0REF = VREF_REFSEL_VDD_gc;

    uint16_t data = (VDDIO2/VDD)*1023;
    DAC0.DATA = data << DAC_DATA_gp;
    
    /*Enable DAC and enable the DAC output*/
    DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm;
}