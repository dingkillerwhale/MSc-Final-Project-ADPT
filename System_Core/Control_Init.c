/**
  ******************************************************************************
  * @file   Automatic_Detect_People_Technology/Entrance/USER/Control_Init.c 
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    02-September-2013
  * @brief   EXTI configuration
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/

#include "LCD_lib.h"

/**
  * @brief  NVIC Configuration.
  * @param  None
  * @retval None
*/
void Control_NVIC_Init (void) {
	
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3); // 3 bits for Preemption Priority
	
	/* Set EXTI9_5_IRQn */
	NVIC_InitStructure.NVIC_IRQChannel =  EXTI9_5_IRQn; // PA-PG.9-5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	/* Set EXTI15_10_IRQn */
	NVIC_InitStructure.NVIC_IRQChannel =  EXTI15_10_IRQn; // PA-PG.9-5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	/* Set EXTI1_IRQn */
	NVIC_InitStructure.NVIC_IRQChannel =  EXTI3_IRQn ; // PA-PG.9-5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	
}

/**
  * @brief  Turn on LED8,9,13.
  * @param  None
  * @retval None
*/
void LED_On(void) {
	
	GPIO_SetBits(GPIOD,GPIO_Pin_8);
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
}

/**
  * @brief  Turn off LED8,9,13.
  * @param  None
  * @retval None
*/
void LED_Off(void) {
	GPIO_ResetBits(GPIOD,GPIO_Pin_8);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
}
/**
  * @brief  Set EXTI PE3,8,9,13.
  * @param  None
  * @retval None
*/
void Control_Exit_Init (void) {
	
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Open the AHB and APB clock*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	/* Config GPIOE */	
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_13 | GPIO_Pin_3);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/* Congig the EXTI function */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource13);
	
	EXTI_InitStructure.EXTI_Line = ( EXTI_Line3 | EXTI_Line8 | EXTI_Line9 |  EXTI_Line13);
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}

/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE****/
