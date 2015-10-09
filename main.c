#include "stm32f4xx.h"
#include <stdio.h>
#include "ov7670/ov7670.h"
#include "usb/usb_virtual_com_port.h"
#include "usb/usbd_cdc_vcp.h"
#include "usart/libUART.h"

void MCO_init();

int
main(void)
{
		MCO_init();
    	OV7670_Init();
    	OV7670_init_QQVGA();
    	OV7670_IDTypeDef ID;
    	OV7670_read_ID(&ID);
    	initUSART();
    	usart_put(0x02);
    	while(1){
    		uint8_t *buf_temp;
    				//Because of bug in PCB, capturing in 10bit mode so data is packed as 16bit value.
    		buf_temp = (uint8_t*) OV7670_capture_image();
        	usart_put(*buf_temp);
        	Delay(2000);
    	}
}

void MCO_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	 RCC_ClockSecuritySystemCmd(ENABLE);

	 /* Enable GPIOs clocks */
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	 GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);

	 /* Configure MCO (PA8) */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);

	 RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_5);
}


