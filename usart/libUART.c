/*
 * gpio.c
 *
 *  Created on: 29/mag/2014
 *      Author: raidenfox
 */

#include "libUART.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"

uint8_t received_string[MAX_STRLEN];
uint8_t head = 0;
uint8_t tail = 0;
uint8_t inmsg;

void initUSART(){

	/*
	 * Si inizializza una struttura GPIO
	 */
	GPIO_InitTypeDef structGPIO;

	/*
	 * Abilitazione del clock su APB2 -> USART1
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/*
	 * Inizializzo la struttura del GPIO
	 * Modalitˆ: AF USART1
	 * Configurazione: TX ! RX
	 */
	structGPIO.GPIO_Mode = GPIO_Mode_AF;
	structGPIO.GPIO_OType = GPIO_OType_PP;
	structGPIO.GPIO_Pin = TX_PIN | RX_PIN;
	structGPIO.GPIO_PuPd = GPIO_PuPd_UP;
	structGPIO.GPIO_Speed = GPIO_Speed_50MHz;

	/*
	 * Conferma la configurazione definita sopra
	 */
	GPIO_Init(GPIOD,&structGPIO);


	GPIO_PinAFConfig(GPIOD, TX_PIN_SOURCE, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, RX_PIN_SOURCE, GPIO_AF_USART2);

	/*
	 * Inizializzazione della struttura per la USART
	 */
	USART_InitTypeDef USARTInit;
	/*
	 * Abilitazione del segnale di clock
	 */

	/*
	 * Configurazione della periferica USART
	 */

    USART_OverSampling8Cmd(USART2, ENABLE);
	USARTInit.USART_BaudRate = BAUDRATE;
	USARTInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USARTInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //TODO:attenzione
	USARTInit.USART_Parity = USART_Parity_No;
	USARTInit.USART_StopBits = USART_StopBits_1;
	USARTInit.USART_WordLength = USART_WordLength_8b;

	/*
	 * Conferma della configurazione
	 */
	USART_Init(USART2,&USARTInit);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* Inizializzazione della struttura per
	 * l'uso del NVIC
	 */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitTypeDef NVIC_Inits;

	NVIC_Inits.NVIC_IRQChannel = USART1_IRQn;
	NVIC_Inits.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Inits.NVIC_IRQChannelPreemptionPriority =  14;
	//NVIC_Inits.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_Inits);

	USART_Cmd(USART2, ENABLE);



}

uint16_t USART_get_buffer(uint8_t* buffer){

	uint8_t tmp;
	uint16_t index=0;
	while (usart_get(&tmp))
	{
		*(buffer+index) = tmp;
		index++;

	}
	return index;

}

void usart_put(uint8_t buf){

	while(!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
	USART_SendData(USART2, buf);
	while(!USART_GetFlagStatus(USART2, USART_FLAG_TC));

}

void usart_send(uint8_t* buf, uint32_t len)
{
	uint32_t i;
	for(i=0; i<len; i++)
	{
		usart_put(*(buf+i));

	}
}
