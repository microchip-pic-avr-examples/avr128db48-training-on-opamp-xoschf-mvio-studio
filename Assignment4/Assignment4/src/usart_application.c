/*
 * usart.c
 *
 * Created: 16-Jun-20 11:28:26
 *  Author: M52422
 */ 

#include "usart_application.h"

char TX_buffer[sizeof(data_stream)];

void DS_start_data_transmit(void) {
    for(uint8_t i = 0; i < sizeof(data_visualizer) -1; i++){
        USART_0_write(((uint8_t *)&data_stream)[i]);
    }
}

void set_up_data_stream(void)
{
    data_stream.start_token = START_TOKEN;
    data_stream.end_token = (~START_TOKEN);
}