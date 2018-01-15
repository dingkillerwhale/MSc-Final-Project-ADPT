/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/SDcard_1/CamSD/CAMERA_OV7670.h
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    02-September-2013
  * @brief   OV7670 Configuration Header
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#ifndef __DCMI_H
#define __DCMI_H

#include "stm32f4xx_conf.h"
#include "string.h"

#define DCMI_DR_ADDRESS       	0x50050028 //DCMI Data Register  
#define FSMC_LCD_ADDRESS      	0x60100000 // SRAM First Address
#define OV7670_REG_NUM  88 

#define SCCB_SIC_H()     GPIOC->BSRRL = GPIO_Pin_13
#define SCCB_SIC_L()     GPIOC->BSRRH = GPIO_Pin_13
#define SCCB_SID_H()     GPIOC->BSRRL = GPIO_Pin_14
#define SCCB_SID_L()     GPIOC->BSRRH = GPIO_Pin_14
#define SCCB_DATA_IN      SCCB_SID_IN()
#define SCCB_DATA_OUT     SCCB_SID_OUT()
#define SCCB_SID_STATE	 GPIOC->IDR&0x1000


void Cam_Init(void);
void OV7670_Init(void);
void Cam_Start(void);
void SCCB_Init(void);
void SCCB_SID_OUT(void);
void SCCB_SID_IN(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void noAck(void);
uint8_t SCCB_Write(uint8_t m_data);
uint8_t SCCB_Read(void);
uint8_t OV_WriteReg(uint8_t regID, uint8_t regDat);
uint8_t OV_ReadReg(uint8_t regID, uint8_t *regDat);
void OV_Reset(void);
uint8_t OV_ReadID(void);

/* Config the OV7670 registers*/
static const uint8_t OV7670_reg[OV7670_REG_NUM][2]=
{	 
	// 30fps PCLK=24MHz 
	{0x11,0x80},
  	{0x6b,0x0a},
	{0x2a,0x00}, 
  	{0x2b,0x00}, 
  	{0x92,0x00}, 
  	{0x93,0x00}, 
	{0x3b,0x0a},

  	//Enable QVGA, RGB
  	{0x12,0x14},

 	 // Enable RGB565 Disable RGB444
 	 {0x40,0x10},
  	{0x8c,0x00},

  	//Special Effect
  	{0x3a,0x0c},
  	{0x67,0xc0},
  	{0x68,0x80},

  	//Mirror/VFlip Enable
	//{0x1e,0x37},

  	// Enable Banding Filter, AWB, AEC, AGC
	{0x13,0xe7},
	//Simple White Balance
	{0x6f,0x9f},
	
	// Frame Location
 	{0x17,0x16},
	{0x18,0x04},
	{0x19,0x02},
	{0x1a,0x7a},
	{0x32,0x80},
	{0x03,0x05},

	 // Config PCLK,HREF,VSYNC
	 {0x15,0x08},
	
   	//Automatic black Level compensation
   	{0xb0,0x84},
   	{0x3d,0x98},
   	//{0x0c,0x00},
		
	 //AWBC - Automatic white balance control
   	{0x43, 0x14},
  	{0x44, 0xf0},
   	{0x45, 0x34},        
   	{0x46, 0x58},
   	{0x47, 0x28},
   	{0x48, 0x3a},
 
   	//AWB Control
   	{0x59, 0x88},
   	{0x5a, 0x88},        
   	{0x5b, 0x44},
   	{0x5c, 0x67},
   	{0x5d, 0x49},
   	{0x5e, 0x0e},
 
  	 //AWB Control
   	{0x6c, 0x0a},
   	{0x6d, 0x55},       
   	{0x6e, 0x11},
   
   	//AGC/AEC - Automatic Gain Control/Automatic exposure Control
   	{0x00, 0x00},
   	{0x14, 0x20},
   	{0x24, 0x75},
   	{0x25, 0x63},
   	{0x26, 0xA5},
 
  	//AEC algorithm selection - AEC  
  	{0xaa, 0x94},//AEC Average-based AEC algorithm AEC Histogram-based AEC algorithm  
 
  	//AGC
   	{0x9f, 0x78},
   	{0xa0, 0x68},       
   	{0xa6, 0xdf},
   	{0xa7, 0xdf},
   	{0xa8, 0xf0},
  	{0xa9, 0x90},
 
  	//Fix Gain Control   
   	{0x69, 0x5d},//Fix gain for Gr channel/for Gb channel/for R channel/for B channel
 
  	//Color saturation
  	{0x4f, 0x80},
   	{0x50, 0x80},
   	{0x51, 0x00},
   	{0x52, 0x22},
   	{0x53, 0x5e},
   	{0x54, 0x80},
  	{0x58, 0x9e},
 
  	//Brightness
  	 {0x55, 0x01},
 
  	//Contrast 
   	{0x56, 0x50},
 
  	//Gamma Curve 
   	{0x7a, 0x20},
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
	 
 	//Matrix Coefficient           
   	{0x4f, 0x80},
   	{0x50, 0x80},
   	{0x51, 0x00},
   	{0x52, 0x22},
   	{0x53, 0x5e},
   	{0x54, 0x80},

   	//Automatic black Level Compensation
   	{0xb0, 0x84},
   	{0xb1, 0x0c},
   	{0xb2, 0x0e},      
   	{0xb3, 0x82},
   	{0xb8, 0x0a},

};
#endif 
/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE****/
