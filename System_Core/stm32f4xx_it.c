/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/Entrance/USER/stm32f4xx_it.c 
  * @author  IWC Group
  * @version V1.0.0
  * @date    07-September-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "xbeeAPI.h"
#include "xbee.h"
#include "LCD_lib.h"

extern uint16_t SensorFlag;
extern uint16_t Coordinator_Flag;
extern uint16_t Alarm_Flag;
extern uint32_t ntime;
extern int atflag;

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if (ntime>0)ntime--;
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles USART2 Handler.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{	
	char c;
	/* Check the flag of USART2 receiving register */
	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)==SET)
	{
		/* Get the value from USART2 */
		c = USART_ReceiveData(USART2);
	  		 
		/* Clear the RXNE pending bit */
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
 
	}
}

/**
  * @brief  This function handles infrared sensor Handler.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {  
		/* Update the light */ 
		GPIO_WriteBit(GPIOD,GPIO_Pin_8, 
					(BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_8))));
		  
      /* Update the flags including Amounts of people for positive and alarm */		
		SensorFlag = 1;
		Alarm_Flag = 0x01;
	   
	   /* Send the amouts of people positive */
	   apiTX16frame(0x01,SensorFlag);
	  
		/* Clear the Wakeup Button EXTI line pending bit */
		EXTI_ClearITPendingBit(EXTI_Line3);		
  } 
} 

/**
  * @brief  This function handles keys Handler.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
  /* Check the key of GPIOE->Pin 8 */
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
  {  
      /* Manually updating the amounts of people for positive */
			GPIO_WriteBit(GPIOD,GPIO_Pin_8, 
						(BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_8))));
			
			SensorFlag = 1;
		
			/* Clear the Wakeup Button EXTI line pending bit */
			EXTI_ClearITPendingBit(EXTI_Line8);
		
  } 
	
	/* Check the key of GPIOE->Pin 9 */
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
  {  
		/* Manually updating the amounts of people for nagative */ 
		GPIO_WriteBit(GPIOD,GPIO_Pin_9, 
					(BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_9))));
		
	  SensorFlag = 2;
		
    /* Clear the Wakeup Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line9);
		
  } 
} 

/**
  * @brief  This function handles keys Handler.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line13) != RESET)
  {  
    /* Updating the xbee flag to initial the configuration of XBee */
		Coordinator_Flag = 0x01; 
				
    /* Clear the Wakeup Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line13);
		
  } 
}

/**
  * @brief  This function handles USART3 Handler.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
	char b;

	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE)==SET)
	{
			b = USART_ReceiveData(USART3);
	 
			if (atflag == 1)
			{
				waitforOK(b);
			}
			else decodeRX(b);

			//USART_SendData(USART2,USART_ReceiveData(USART3));
		 
	/* Clear USART RXNE pending bit */ 
	USART_ClearITPendingBit(USART3,USART_IT_RXNE);
 
	}
}

/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE****/
