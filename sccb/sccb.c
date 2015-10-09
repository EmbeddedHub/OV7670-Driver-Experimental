/*
 * sccb.c
 *
 *  Created on: 08 ott 2015
 *      Author: raidenfox1
 */
#include "sccb.h"

void local_I2C_Initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable the software I2C Clock */
	RCC_AHB1PeriphClockCmd(SOFT_I2C_PORT_CLOCK, ENABLE);

	/* Configure the SDA and SCL pins */
	GPIO_InitStructure.GPIO_Pin = SOFT_I2C_SCL_PIN | SOFT_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SOFT_I2C_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN, Bit_SET);
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_SET);

	local_I2C_Delay();
}

void local_I2C_Start(void)
{
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN, Bit_RESET);
	local_I2C_Delay();
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_RESET);
	local_I2C_Delay();

}

void local_I2C_Stop(void)
{
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN, Bit_RESET);
	local_I2C_Delay();
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_SET);
	local_I2C_Delay();
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN, Bit_SET);
	local_I2C_Delay();
}

uint8_t local_I2C_ReadByte(char ack)
{
	uint8_t data = 0;
	char i;

	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN, Bit_SET); // make input
	for(i = 0; i < 8; i++) {
		local_I2C_Delay();
		GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_SET);
		local_I2C_Delay();
		data |= GPIO_ReadInputDataBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN) & 0x01;
		if(i != 7)
			data <<= 1;
		GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_RESET);
	}

	// issue the ack
	local_I2C_Delay();
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN, ack ? Bit_SET : Bit_RESET);
	local_I2C_Delay();
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_SET);
	local_I2C_Delay();
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_RESET);
	local_I2C_Delay();
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN, Bit_SET);
	local_I2C_Delay();

	return data;
}

// returns ack state, 0 means acknowledged
char local_I2C_WriteByte(uint8_t data)
{
	char i;

	// send the 8 bits
	for(i = 0; i < 8; i++) {
		GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN, (data & 0x80) ? Bit_SET : Bit_RESET);
		data <<= 1;
		local_I2C_Delay();
		GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_SET);
		local_I2C_Delay();
		GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_RESET);
	}

	// read the ack
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN, Bit_SET);
	local_I2C_Delay();
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_SET);
	local_I2C_Delay();
	i = GPIO_ReadInputDataBit(SOFT_I2C_PORT, SOFT_I2C_SDA_PIN);
	GPIO_WriteBit(SOFT_I2C_PORT, SOFT_I2C_SCL_PIN, Bit_RESET);
	local_I2C_Delay();

	return i;
}

// returns ack state, 0 means acknowledged
char local_I2C_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
	char result;

	local_I2C_Start();
	result |= local_I2C_WriteByte(dev_addr); //reset the last bit
	result |= local_I2C_WriteByte(reg_addr); // id address
	result |= local_I2C_WriteByte(data); // id address
	local_I2C_Stop();

	return result;
}

uint8_t local_I2C_ReadReg(uint8_t dev_addr, uint8_t reg_addr)
{
	uint8_t data;

	local_I2C_Start();
	local_I2C_WriteByte(dev_addr & 0xFE);
	local_I2C_WriteByte(reg_addr); // id address
	local_I2C_Stop();
	//if(result) break;

	local_I2C_Start();
	local_I2C_WriteByte(dev_addr);
	data = local_I2C_ReadByte(NACK);
	local_I2C_Stop();

	return data;
}

void local_I2C_Delay(void)
{
	uint32_t d = 100;
	while(d--) {
	}
}
