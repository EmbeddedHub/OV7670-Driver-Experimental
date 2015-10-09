
#ifndef GPIO_H_
#define GPIO_H_

//#include "misc.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdint.h>
#include "stm32f4xx.h"

#define PRIORITY 0
#define SUBPRIORITY 0
#define MAX_STRLEN 1024
#define	MAX_BUFFER		1024

#define TX_PIN GPIO_Pin_5
#define RX_PIN GPIO_Pin_6

#define TX_PIN_SOURCE GPIO_PinSource5
#define RX_PIN_SOURCE GPIO_PinSource6


#define BAUDRATE 9600


uint8_t usart_get();
uint16_t USART_get_buffer(uint8_t* buffer);
int sizebuffer();
void initUSART();
void usart_send(uint8_t* buf, uint32_t len);
void usart_put(uint8_t buf);


#endif /* GPIO_H_ */
