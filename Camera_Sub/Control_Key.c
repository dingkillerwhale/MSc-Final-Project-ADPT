/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/SDcard_1/CamSD/Control_Key.c
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    02-September-2013
  * @brief   Control key initialization
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/	
#include "Control_Key.h"

/* Congfig PB0 as the control key input*/
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	/* GPIO Configuration*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Config EXTI function to PB0*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    
	  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
}

/* Config PD12 as the output */
void LED_Init(void) {
	
   GPIO_InitTypeDef GPIO_InitStructure;
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
	 GPIO_ResetBits(GPIOD,GPIO_Pin_12);


}

/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE****/
