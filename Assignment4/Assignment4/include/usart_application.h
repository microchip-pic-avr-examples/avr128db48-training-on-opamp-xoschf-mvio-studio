/**
 * \file usart_application.h
 *
 * \brief USART application header file.
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