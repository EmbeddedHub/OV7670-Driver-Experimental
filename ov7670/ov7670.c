/*
 * ov7670.c
 *
 *  Created on: 08 ott 2015
 *      Author: raidenfox1
 */

#include "ov7670.h"

void OV7670_DCMI_Init();

struct regval_list {
        unsigned char reg_num;
        unsigned char value;
};

struct regval_list ov7670_qqvga_regs[] =
{
	{0x3a, 0x04},
    {0x40, 0xC0},	//changed this Was 0xD0
    {0x12, 0x00},	//changed this 0x14 for QVGA
    {0x32, 0x80},
    {0x17, 0x16},
    {0x18, 0x04},
    {0x19, 0x02},
    {0x1a, 0x7b},	//0x7a,
    {0x03, 0x06},	//0x0a,
    {0x0c, 0x00},
    {0x3e, 0x1A},//
    {0x70, 0x00},
    {0x71, 0x00},
    {0x72, 0x22},
    {0x73, 0x02},//
    {0xa2, 0x02},
    {0x11, 0x80},

    {0x7a, 0x20}, //Gamma correction
    {0x7b, 0x1c},
    {0x7c, 0x28},
    {0x7d, 0x3c},
    {0x7e, 0x55},
    {0x7f, 0x68},
    {0x80, 0x76},
    {0x81, 0x80},
    {0x82, 0x88},
    {0x83, 0x8f},
    {0x84, 0x96},
    {0x85, 0xa3},
    {0x86, 0xaf},
    {0x87, 0xc4},
    {0x88, 0xd7},
    {0x89, 0xe8},

    {0x13, 0xe0},	//AEC.AGC
    {0x00, 0x00},	//AGC
    {0x10, 0x00},
    {0x0d, 0x00},
    {0x14, 0x28},	//0x38, limit the max gain
    {0xa5, 0x05},
    {0xab, 0x07},
    {0x24, 0x75},
    {0x25, 0x63},
    {0x26, 0xA5},
    {0x9f, 0x78},
    {0xa0, 0x68},
    {0xa1, 0x03},//0x0b,
    {0xa6, 0xdf},//0xd8,
    {0xa7, 0xdf},//0xd8,
    {0xa8, 0xf0},
    {0xa9, 0x90},
    {0xaa, 0x94},
    {0x13, 0xe5},
    {0x0e, 0x61},
    {0x0f, 0x4b},
    {0x16, 0x02},
    {0x1e, 0x37},	//Bit[4]=VFLIP
    {0x21, 0x02},
    {0x22, 0x91},
    {0x29, 0x07},
    {0x33, 0x0b},
    {0x35, 0x0b},
    {0x37, 0x1d},
    {0x38, 0x71},
    {0x39, 0x2a},
    {0x3c, 0x78},
    {0x4d, 0x40},
    {0x4e, 0x20},
    {0x69, 0x00},
    {0x6b, 0x00},//Bypass PLL
    {0x74, 0x19},
    {0x8d, 0x4f},
    {0x8e, 0x00},
    {0x8f, 0x00},
    {0x90, 0x00},
    {0x91, 0x00},
    {0x92, 0x00},//0x19,//0x66
    {0x96, 0x00},
    {0x9a, 0x80},
    {0xb0, 0x84},
    {0xb1, 0x0c},
    {0xb2, 0x0e},
    {0xb3, 0x82},
    {0xb8, 0x0a},
    {0x43, 0x14},
    {0x44, 0xf0},
    {0x45, 0x34},
    {0x46, 0x58},
    {0x47, 0x28},
    {0x48, 0x3a},
    {0x59, 0x88},
    {0x5a, 0x88},
    {0x5b, 0x44},
    {0x5c, 0x67},
    {0x5d, 0x49},
    {0x5e, 0x0e},
    {0x64, 0x04},	//Lens correction
    {0x65, 0x20},	//Lens correction
    {0x66, 0x05}, //Lens correction
    {0x94, 0x04}, //Lens correction
    {0x95, 0x08}, //Lens correction
    {0x6c, 0x0a},
    {0x6d, 0x55},
    {0x6e, 0x11},
    {0x6f, 0x9f},//0x9e for advance AWB
    {0x6a, 0x40}, //G Gain
    {0x01, 0x40}, //B Gain
    {0x02, 0x40}, //R Gain
    {0x13, 0xe7},
    {0x15, 0x00},	//originally Vsync was negative, 0x02

    {0x4f, 0x80}, //Color Matrix
    {0x50, 0x80},
    {0x51, 0x00},
    {0x52, 0x22},
    {0x53, 0x5e},
    {0x54, 0x80},
    {0x58, 0x9e},

    {0x41, 0x08},
    {0x3f, 0x00},
    {0x75, 0x05},
    {0x76, 0xe1},
    {0x4c, 0x00},
    {0x77, 0x01},
    {0x3d, 0xc2},   //0xc0,
    {0x4b, 0x09},
    {0xc9, 0x60},
    {0x41, 0x38},
    {0x56, 0x40},//0x40,  change according to Jim's request
    {0x34, 0x11},
    {0x3b, 0x02},//0x00,//0x02,
    {0xa4, 0x89},//0x88,
    {0x96, 0x00},
    {0x97, 0x30},
    {0x98, 0x20},
    {0x99, 0x30},
    {0x9a, 0x84},
    {0x9b, 0x29},
    {0x9c, 0x03},
    {0x9d, 0x4c},
    {0x9e, 0x3f},
    {0x78, 0x04},
    {0x79, 0x01},
    {0xc8, 0xf0},
    {0x79, 0x0f},
    {0xc8, 0x00},
    {0x79, 0x10},
    {0xc8, 0x7e},
    {0x79, 0x0a},
    {0xc8, 0x80},
    {0x79, 0x0b},
    {0xc8, 0x01},
    {0x79, 0x0c},
    {0xc8, 0x0f},
    {0x79, 0x0d},
    {0xc8, 0x20},
    {0x79, 0x09},
    {0xc8, 0x80},
    {0x79, 0x02},
    {0xc8, 0xc0},
    {0x79, 0x03},
    {0xc8, 0x40},
    {0x79, 0x05},
    {0xc8, 0x30},
    {0x79, 0x26},
    {0x09, 0x03},
    {0x3b, 0x00},//0x82,//0xc0,//0xc2,  //night mode
    {0xff, 0xff},
};

/* Private variables ---------------------------------------------------------*/

uint32_t image_buffer[IMG_SIZE/sizeof(uint32_t)];

void OV7670_Init(){
		GPIO_InitTypeDef GPIO_InitStructure;

		//Camera Reset pin
		RCC_AHB1PeriphClockCmd(CAM_RST_GPIO_CLK, ENABLE);

		GPIO_InitStructure.GPIO_Pin = CAM_RST_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(CAM_RST_GPIO_PORT, &GPIO_InitStructure);

		OV7670_DCMI_Init();
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

		local_I2C_Initialize();

		  //Remove camera reset
		GPIO_ResetBits(CAM_RST_GPIO_PORT, CAM_RST_PIN);
		Delay(1000);
		GPIO_SetBits(CAM_RST_GPIO_PORT, CAM_RST_PIN);
}

void OV7670_DCMI_Init(){
	GPIO_InitTypeDef GPIO_InitStructure;

	DCMI_InitTypeDef DCMI_InitStructure;
	//DCMI_CROPInitTypeDef DCMI_CROPInitStructure;

	RCC_AHB1PeriphClockCmd(
			RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC
					| RCC_AHB1Periph_GPIOE, ENABLE);

	// Connect DCMI pins to AF13
	// PORTA
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI); // HSYNC
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI); // PCLK
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_DCMI); // D0
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_DCMI); // D1
	// PORTB
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI); // D5
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI); // VSYNC
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI); // D6
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI); // D7				   -
	// PORTC
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_DCMI); // D4
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI); // D0
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI); // D1
	// PORTE
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_DCMI); // D2
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_DCMI); // D3
	// DCMI GPIO configuration
	// D0..D1(PA9/10), HSYNC(PA4), PCLK(PA6)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// D5..D7(PB6/8/9), VSYNC(PB7)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// D4(PC11)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// D2..D3(PE0/1)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	//---------------------------------------------------------------------------------------
	//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI); //d0
	//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);	//d1
	//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);	//d2

	//---------------------------------------------------------------------------------------
	// Configures the DCMI to interface with the OV7670 camera module
	// Enable DCMI clock
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
	// Reinitialize
	DCMI_DeInit();

	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;
	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;
	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
	DCMI_Init(&DCMI_InitStructure);

}

uint8_t OV7670_write_reg(uint16_t Addr, uint8_t Data)
{

	local_I2C_WriteReg(OV7670_DEVICE_WRITE_ADDRESS, Addr, Data);
	return 0;
}

uint8_t OV7670_read_reg(uint16_t Addr)
{

  return local_I2C_ReadReg(OV7670_DEVICE_READ_ADDRESS, Addr);
}

void OV7670_init_QQVGA()
{

	int i;
	for(i=0;i<sizeof(ov7670_qqvga_regs)/2;++i)
	{
		OV7670_write_reg(ov7670_qqvga_regs[i].reg_num, ov7670_qqvga_regs[i].value );
	}

	//For some reason need to write to these registers again, to get a good color image.
	OV7670_write_reg(0x0C,0x04); //enable down sampling
	OV7670_write_reg(0x72,0x22); //Down sample by 4
	OV7670_write_reg(0x73,0x02); //Clock div4
	OV7670_write_reg(0x3E,0x1A); //Clock div4
}

void OV7670_reset(void)
{
  OV7670_write_reg(REG_COM7, COM7_RESET);
}

void OV7670_read_ID(OV7670_IDTypeDef *OV7670ID)
{
//  OV7670_WriteReg(OV7670_DSP_RA_DLMT, 0x01);
  OV7670ID->Manufacturer_ID1 = OV7670_read_reg(REG_MIDH);
  OV7670ID->Manufacturer_ID2 = OV7670_read_reg(REG_MIDL);
  OV7670ID->PIDH = OV7670_read_reg(REG_PID);
  OV7670ID->PIDL = OV7670_read_reg(REG_VER);
}

uint8_t * OV7670_capture_image()
{
	DCMI_InitTypeDef DCMI_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;

	/* DMA2 Stream1 Configuration */
	DMA_DeInit(DMA2_Stream1);

	DMA_InitStructure.DMA_Channel = DMA_Channel_1;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DCMI->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) image_buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = (IMG_SIZE/sizeof(uint32_t));
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  /* DMA2 IRQ channel Configuration */
  DMA_Init(DMA2_Stream1, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream1, ENABLE);

  DCMI_Cmd(ENABLE);

  DCMI_CaptureCmd(ENABLE);

  int temp;
  // Wait until DCMI DMA Rx transfer is complete
  while (DMA_GetFlagStatus(DMA2_Stream1, DMA_FLAG_TCIF1) == RESET)
  {
    temp = DMA_GetCurrDataCounter(DMA2_Stream1);
    temp = DCMI->CR;
    temp = DCMI->RISR;
  }

  /* Clear all DMA Streams flags */
  DMA_ClearFlag(DMA2_Stream1, DMA_FLAG_HTIF1 | DMA_FLAG_TCIF1);

  /* Disable the DMA Rx Stream */
  DMA_Cmd(DMA2_Stream1, DISABLE);

  //Do not disable DCMI peripheral untill DMA disable command gets through
  while(DMA_GetCmdStatus(DMA2_Stream1) == ENABLE)
  {}

  DCMI_Cmd(DISABLE);

  return  (uint8_t*) image_buffer;

}
