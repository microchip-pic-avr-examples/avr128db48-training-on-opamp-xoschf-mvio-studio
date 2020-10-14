/*
 * \file main.c
 *
 * \brief Main source file.
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

#include <atmel_start.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "adc_application.h"
#include "rtc.h"
#include "dac_application.h"
#include "usart_application.h"
#include "rtc_application.h"




int main(void)
{
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    
    /* Sets up the ADC result ready callback */
    ADC_0_register_callback(&ADC_cb);
    
    /* Creates a table with values for the DAC to create a sin wave, see dac.h for sin wave spesifications */
    sin_wave_table_init();
    
    /* Adds the start and end token to the data streamer struct*/
    set_up_data_stream();
    
    /* Enable the timer used to create the sin wave */
    DAC0_SineWaveTimer_enable();
    
    /* Enable the timer used to trigger a new ADC measurement */
    ADC0_SampleTimer_enable();
    
    /* RTC is used to Blink LED at 0.5s = PER (511) / (32768 / 32) */
    RTC_enable();
    
    /* Enables global interrupts */
    sei();
    
    /* Replace with your application code */
    while (1) {
    }
}