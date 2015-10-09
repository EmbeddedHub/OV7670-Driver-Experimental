/*
 * sccb.h
 *
 *  Created on: 08 ott 2015
 *      Author: raidenfox1
 */

#ifndef SCCB_SCCB_H_
#define SCCB_SCCB_H_

#include "stm32f4xx.h"
#define SOFT_I2C_PORT_CLOCK RCC_APB1Periph_I2C1
#define SOFT_I2C_SCL_PIN GPIO_Pin_8
#define SOFT_I2C_SDA_PIN GPIO_Pin_9
#define SOFT_I2C_PORT GPIOB
#define ACK 0
#define NACK 1

void local_I2C_Initialize(void);
void local_I2C_Start(void);
void local_I2C_Stop(void);
uint8_t local_I2C_ReadByte(char ack);
char local_I2C_WriteByte(uint8_t data);
char local_I2C_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
uint8_t local_I2C_ReadReg(uint8_t dev_addr, uint8_t reg_addr);
void local_I2C_Delay(void);


#endif /* SCCB_SCCB_H_ */
