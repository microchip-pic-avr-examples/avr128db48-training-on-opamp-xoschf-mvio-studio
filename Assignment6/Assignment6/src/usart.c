/**
 * \file usart.c
 *
 * \brief USART driver source file.
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

#include "usart.h"

void usart_init(void)
{
    VPORTB.DIR |= PIN0_bm;                                  /* set pin 0 of PORT B (TXd) as output*/    USART3.BAUD = (uint16_t)(USART_BAUD_RATE(115200));       /* set the baud rate*/
    USART3.CTRLC = USART_CHSIZE0_bm | USART_CHSIZE1_bm;     /* set the data format to 8-bit*/
    USART3.CTRLB |= (USART_TXEN_bm);        /* enable transmitter*/
    
    data_stream.start_token = START_TOKEN;
    data_stream.end_token = (~START_TOKEN);
}

void usart_transmit_data(uint8_t data)
{
    while (!(USART3.STATUS & USART_DREIF_bm));
    USART3.TXDATAL = data;
}

void DS_transmit_data(void)
{
    usart_transmit_data(data_stream.start_token);
    usart_transmit_data(data_stream.vddio2);
    usart_transmit_data(data_stream.vddio2 >> 8);
    usart_transmit_data(data_stream.end_token);
}
