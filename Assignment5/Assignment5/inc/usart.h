/*
 * usart.h
 *
 * Created: 23-Sep-20 11:23:43
 *  Author: M52422
 */ 


#ifndef USART_H_
#define USART_H_

#include <avr/io.h>

#define USART_BAUD_RATE(BAUD_RATE)     ((float)(64 * F_CPU / (16 * (float)BAUD_RATE)) + 0.5)

#define START_TOKEN     0x55

typedef struct {
    uint8_t start_token;
    uint16_t vddio2;
    uint8_t end_token;    
}data_visualizer_t;

data_visualizer_t data_stream;

void usart_init(void);
void DS_transmit_data(void);

#endif /* USART_H_ */