/**
 * \file adc.c
 *
 * \brief ADC driver source file.
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

#include "adc.h"

void adc0_init(void)
{
    /*Select the 1.024V reference for ADC0*/
    VREF.ADC0REF = VREF_REFSEL_1V024_gc;
    
    /*Configure accumulation of 16 samples*/
    ADC0.CTRLB = ADC_SAMPNUM_ACC16_gc;
    
    
    /*Select VDDIO2DIV10 as input for ADC0*/
    ADC0.MUXPOS = ADC_MUXPOS_VDDIO2DIV10_gc;

    /*Enable ADC0*/
    ADC0.CTRLA = ADC_ENABLE_bm;// | ADC_CONVMODE_bm | ADC_RESSEL_12BIT_gc;
}

uint16_t read_VDDIO2()
{
    /*Measure VDDIO2 using the internal ADC*/

    /*Start an ADC conversion*/
    ADC0.COMMAND = ADC_STCONV_bm;

    /*Wait for the ADC conversion to be done*/
    while(!(ADC0.INTFLAGS & ADC_RESRDY_bm));
    
    /*Read the RES register and shift the result 4 bits to compensate for the 16 over samples, the result is actual voltage divided by 10*/
    volatile uint16_t result = (ADC0.RES>>4);
    
    return result;
}