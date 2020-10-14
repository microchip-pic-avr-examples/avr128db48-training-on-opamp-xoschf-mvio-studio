/*
 * usart.c
 *
 * Created: 23-Sep-20 11:22:52
 *  Author: M52422
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
