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

    dac_set_voltage(VDDIO2);
    
    /*Enable DAC and enable the DAC output*/
    DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm;
}

void dac_set_voltage(float v_out)
{
    uint16_t data = (v_out/VDD)*1023;
    DAC0.DATA = data << DAC_DATA_gp;
}