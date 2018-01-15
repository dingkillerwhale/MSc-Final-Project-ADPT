/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/SDcard_1/CamSD/stm32f4xx_it.c
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    02-September-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine. Include DCMI interrupt
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "stm32f4_discovery_sdio_sd.h"
extern uint32_t ntime;
extern uint16_t KeyFlag;

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void){
}
/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void){
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1){
  	}
}
/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void){
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1){
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
  while (1){
  }
}
/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void){
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1){
  }
}
/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void){
}
/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void){
}
/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void){
}

void SysTick_Handler(void){
	if(ntime>0) ntime--;
}

void SDIO_IRQHandler(void){
	/* Process All SDIO Interrupt Sources */
  	SD_ProcessIRQSrc();
}

void SD_SDIO_DMA_IRQHANDLER(void){
	/* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
  	SD_ProcessDMAIRQ();
}

/* DCMI_Frame Interrupt*/
void DCMI_IRQHandler(void){
	if (DCMI_GetITStatus(DCMI_IT_FRAME)!=RESET){
		/* When finish one completed frame and the flag is 1,
		the function of DCMI will be stoped and flag will be 2*/
		if(KeyFlag == 1){
			/* Disable DCMI function */
			DCMI_Cmd(DISABLE);
			DCMI_CaptureCmd(DISABLE);
			KeyFlag =2;
		}
	}
	/* Clear the Wakeup Button DCMI line pending bit */
	DCMI_ClearITPendingBit(DCMI_IT_FRAME);
}

/* External Interrupt from control key*/
void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0) != RESET){  
		/* Set flag as 1*/
		KeyFlag = 1;
		/* Clear the Wakeup Button EXTI line pending bit */
    		EXTI_ClearITPendingBit(EXTI_Line0);
	} 
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
