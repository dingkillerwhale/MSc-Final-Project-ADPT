/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/SDcard_1/CamSD/delay.c 
  * @author  IWC Group
  * @version V1.0.0
  * @date    07-September-2013
  * @brief   Main delay functions
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "delay.h"

__IO uint16_t ntime;

/**
  * @brief  This function generates delay in the unit of ms.
  * @param  nms: the required delay time in ms
  * @retval None
*/
void delay_ms(uint16_t nms) {
	ntime = nms;
	SysTick_Config(168000);// 1ms Interrupt
	while(ntime);
	SysTick->CTRL = 0x00;	
}

/**
  * @brief  This function generates delay in the unit of nus.
  * @param  nus: the required delay time in us
  * @retval None
*/
void delay_us(uint32_t nus) {
	
	ntime = nus;
	SysTick_Config(168);
	while(ntime);
	SysTick->CTRL = 0x00;	
}

/**
  * @brief  This function generates delay.
  * @param  None
  * @retval None
*/
void delay(uint32_t count) {
	
	while(count--);
	
}

/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE************/
