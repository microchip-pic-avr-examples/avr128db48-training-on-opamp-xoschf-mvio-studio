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
#include "adc.h"
#include "dac.h"
#include "opamp.h"
#include "usart.h"


int main(void)
{
    adc0_init();
    dac_init();
    op_amp_init();
    usart_init();
    
    /* Set all PINs running on VDDIO2 to high so they can be measured */
    PORTC.DIRSET = 0xFF;;
    PORTC.OUTSET = 0xFF;
    while (1)
    {
        /*Read the VDDIO2 voltage continuously*/
        data_stream.vddio2 =  (read_VDDIO2()*VREFF_ADC*10*1000)/ADC_RESOLUTION; //Convert the ADC reading to millivolts
        DS_transmit_data();
    }
}








