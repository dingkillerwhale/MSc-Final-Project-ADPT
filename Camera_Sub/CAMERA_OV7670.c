/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/SDcard_1/CamSD/CAMERA_OV7670.c
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    02-September-2013
  * @brief   OV7670 Configuration
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "Camera_ov7670.h"
#include "stm32f4xx.h"
#include "misc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_usart.h"
#include "diskio.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "stm32f4_discovery_sdio_sd.h"
#include "ff.h"
#include "string.h"
#include "stdio.h"

#include "Control_Key.h"
#include "Camera_ov7670.h"
#include "delay.h"

/* DCMI interrupt priority initialization*/
void DCMI_NVIC_Config(void) {
	
	NVIC_InitTypeDef NVIC_InitStructure;
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  	NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
}

/* Camera Initialization*/
void Cam_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
  	DCMI_InitTypeDef DCMI_InitStructure;
     	DMA_InitTypeDef  DMA_InitStructure;
	
	/* Open bus clocks */
     	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);//DCMI 
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//DMA2
     	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
                        RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);
	
	/* Open PLLI2S clock to support 24MHz for the external clock source*/
	RCC_HSICmd(ENABLE);
	RCC_PLLI2SCmd(DISABLE);
	RCC_PLLCmd(DISABLE);
	RCC_MCO2Config(RCC_MCO2Source_PLLI2SCLK,RCC_MCO2Div_2);
	RCC_PLLI2SConfig(192,4);
	RCC_PLLI2SCmd(ENABLE);
	
	/* Config PA8 as the MCO port */	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);//MCO1:PA8
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  	GPIO_Init(GPIOA, &GPIO_InitStructure);    
    
    	/* Config PD6 as the PowerDown port */
   	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PD6:PWRDOWN
    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
    	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
    	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; 
    	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_Pin_6);//power on

    	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);//DCMI_HSYNC 
    	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_PIXCLK
    	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_D5 			  
    	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);//DCMI_VSYNC 
   	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_DCMI);//DCMI_D6 
    	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_DCMI);//DCMI_D7 			  
    	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_DCMI);//DCMI_D0 
    	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_DCMI);//DCMI_D1 			  
    	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);//DCMI_D2 
    	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);//DCMI_D3 
    	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_DCMI);//DCMI_D4 

    	/* Config GPIOs as the DCMI data input ports*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_8 | GPIO_Pin_9 ;
    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
   	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; 
    	GPIO_Init(GPIOC, &GPIO_InitStructure); 
    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
    	GPIO_Init(GPIOB, &GPIO_InitStructure);   
    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_9 | GPIO_Pin_10; 
    	GPIO_Init(GPIOA, &GPIO_InitStructure);	
   
	 /* DeInit DCMI*/
	 DCMI_DeInit();
		
	/* Config DCMI fucntion, Continuous mode, 8-bit input*/
  	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
  	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
  	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
  	DCMI_Init(&DCMI_InitStructure);
		
	/* Config NVIC */
	DCMI_NVIC_Config();
	/* Enable DCMI Frame Interrupt */
	DCMI_ITConfig(DCMI_IT_FRAME,ENABLE);
	
	/* DeInit DMA */
  	DMA_DeInit(DMA2_Stream1);
	
	/* Config DMA fucntion,
		Choose Channel 1 to transmit,		
		Peripheral Address = DCMI_DR,
		Memory Address = SRAM, 
		Peripheral to Memory, 
		Word to Halfword transmission,
		Circular Mode		
	*/
  	DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  	DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  	DMA_InitStructure.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;
  	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  	DMA_InitStructure.DMA_BufferSize = 1;
  	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
  	DMA_Init(DMA2_Stream1, &DMA_InitStructure);	  
}


/* OV7670 registers configuration */
void OV7670_Init(void) {
	  
	uint8_t i;
	
	/* Init Cmaera pins */
	Cam_Init();
	/* Config SCCB lines*/
	SCCB_Init();
	/* Reset OV7670 */
	OV_Reset();
	delay_ms(5);
	/* Write the configuration value into OV7670 registers */
	for(i=0;i<OV7670_REG_NUM;i++){
		OV_WriteReg(OV7670_reg[i][0],OV7670_reg[i][1]);
 	}
}

/* Start Camera */	
void Cam_Start(void)
{
  	/* Enable DMA */
  	DMA_Cmd(DMA2_Stream1, ENABLE); 
	/* Enable DCMI*/
  	DCMI_Cmd(ENABLE); 
	/* Enable DCMI caputure mode*/
  	DCMI_CaptureCmd(ENABLE); 
}	

/* Config SCCB pins */
void SCCB_Init(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructure;
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;  //SCCB_SIC:PC13
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			        //SCCB_SID:PC14
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/* Config S_IOD as output mode */	
void SCCB_SID_OUT(void)// SID Out
{
  	GPIO_InitTypeDef  GPIO_InitStructure;

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;               
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/* Config S_IOD as input mode */	
void SCCB_SID_IN(void)// SID In
{
  	GPIO_InitTypeDef  GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;               
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
}	

/* SCCB start transmission */
void SCCB_Start(void)
{
	SCCB_SID_H();     
    	delay_us(50);
    	SCCB_SIC_H();	   
    	delay_us(50);
   	SCCB_SID_L();
    	delay_us(50);
    	SCCB_SIC_L();	 
    	delay_us(50);
}	

/* SCCB stop transmission */
void SCCB_Stop(void)
{
    	SCCB_SID_L();
   	delay_us(50);
    	SCCB_SIC_H();	
    	delay_us(50);  
    	SCCB_SID_H();	
   	delay_us(50);  
}	
/* No acknwledgement */	
void noAck(void)
{	
	SCCB_SID_H();	
	delay_us(50);	
	SCCB_SIC_H();	
	delay_us(50);	
	SCCB_SIC_L();	
	delay_us(50);	
	SCCB_SID_L();	
	delay_us(50);
}	

/* SCCB write function */	
uint8_t SCCB_Write(uint8_t m_data)
{
	uint8_t j,tem;

	for(j=0;j<8;j++){ //Loop for 8 times to send data
		if((m_data<<j)&0x80)SCCB_SID_H();
		else SCCB_SID_L();
		delay_us(50);
		SCCB_SIC_H();	
		delay_us(50);
		SCCB_SIC_L();	
		delay_us(50);
	}
	delay_us(10);
	SCCB_DATA_IN;
	delay_us(50);
	SCCB_SIC_H();	
	delay_us(10);
	if(SCCB_SID_STATE)tem=0;
	else tem=1;
	SCCB_SIC_L();	
	delay_us(50);	
    	SCCB_DATA_OUT;
	return tem;  
}

/* SCCB read function */	
uint8_t SCCB_Read(void)
{
	uint8_t read,j;
	read=0x00;
	
	SCCB_DATA_IN;
	delay_us(50);
	for(j=8;j>0;j--){ // Loop for 8 times to receive data	     
		delay_us(50);
		SCCB_SIC_H();
		delay_us(50);
		read=read<<1;
		if(SCCB_SID_STATE)read=read+1; 
		SCCB_SIC_L();
		delay_us(50);
	}	
    	SCCB_DATA_OUT;
	return read;
}

/* Write value into register*/
uint8_t OV_WriteReg(uint8_t regID, uint8_t regDat)
{
	SCCB_Start();
	if(SCCB_Write(0x42)==0){
		SCCB_Stop();
		return 1;
	}
	delay_us(10);
  	if(SCCB_Write(regID)==0){
		SCCB_Stop();
		return 2;
	}
	delay_us(10);
  	if(SCCB_Write(regDat)==0){
		SCCB_Stop();
		return 3;
	}
  	SCCB_Stop();
  	return 0;
}

/* Read value from register*/
uint8_t OV_ReadReg(uint8_t regID, uint8_t *regDat)
{
	SCCB_Start();
	if(SCCB_Write(0x42)==0)
	{
		SCCB_Stop();
		return 1;
	}
	delay_us(10);
  	if(SCCB_Write(regID)==0)
	{
		SCCB_Stop();
		return 2;
	}
	SCCB_Stop();
	delay_us(10);	
	SCCB_Start();
	if(SCCB_Write(0x43)==0)
	{
		SCCB_Stop();
		return 3;
	}
	delay_us(10);
  	*regDat=SCCB_Read();
  	noAck();
  	SCCB_Stop();
  	return 0;
}

/* Reset OV7670 */
void OV_Reset (void) {
	OV_WriteReg(0x12,0x80);
	
}

/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE****/	
