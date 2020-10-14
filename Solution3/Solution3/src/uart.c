/*  
 * \file uart.c
 *
 * \brief Send data stream to Data Visualizer.
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

#include <avr/interrupt.h>
#include <string.h>
#include "uart.h"

char TX_buffer[sizeof(data_stream)];

/*
 * Communication interface functions
 */
void USART_init(void)
{
    VPORTB.DIR &= ~PIN1_bm;                                 /* set pin 1 of PORT B (RXd) as input*/
    VPORTB.DIR |= PIN0_bm;                                  /* set pin 0 of PORT B (TXd) as output*/    USART3.BAUD = (uint16_t)(USART_BAUD_RATE(115200));       /* set the baud rate*/
    USART3.CTRLC = USART_CHSIZE0_bm | USART_CHSIZE1_bm;     /* set the data format to 8-bit*/
    USART3.CTRLB |= (USART_TXEN_bm | USART_RXEN_bm);        /* enable transmitter*/
    
    data_stream.start_token = START_TOKEN;
    data_stream.end_token = (~START_TOKEN);
}

void DS_start_data_transmit(void) {
    memcpy(TX_buffer, &data_stream, sizeof(data_stream));

    USART3.CTRLA =  USART_DREIE_bm;     /* Enable Transmit Complete interrupt*/
    USART3.TXDATAL = TX_buffer[0];  /* Send the first byte of the buffer*/
                                               /* once the first byte is transmitted the ISR will kick in*/
}

ISR (USART3_DRE_vect) {
    volatile static uint8_t tx_count = 1;

    if (data_stream.data_available) {

        if (tx_count < (sizeof(TX_buffer) - 1)) {
            USART3.TXDATAL = TX_buffer[tx_count];
            tx_count++;
        }
        else{
            
            tx_count = 1;
            data_stream.data_available = 0;
            USART3.CTRLA &=  ~USART_DREIE_bm;   /* Disable Transmit Complete interrupt*/
                                                /* No more bytes available*/
        }
    }
}