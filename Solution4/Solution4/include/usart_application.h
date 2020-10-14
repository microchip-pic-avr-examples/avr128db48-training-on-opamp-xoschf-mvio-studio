/*
 * usart.h
 *
 * Created: 16-Jun-20 11:28:46
 *  Author: M52422
 */ 


#ifndef USART_H_
#define USART_H_

#include "usart_basic.h"

#define START_TOKEN     0x55

typedef struct {
    uint8_t start_token;           /* Start token for the data streamer protocol */   
    uint16_t dacVal;               /* DAC output used as input to the Voltage Follower */
    uint16_t opampVal;             /* Output from the Voltage Follower */
    uint8_t end_token;             /* End token for the data streamer protocol */
    uint8_t data_available;        /* Flag indicating if data is ready to be streamed to data visualizer */
}data_visualizer;

data_visualizer data_stream;

void DS_start_data_transmit(void);
void set_up_data_stream(void);



#endif /* USART_H_ */