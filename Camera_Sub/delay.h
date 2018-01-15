/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/Entrance/USER/delay.h 
  * @author  IWC Group
  * @version V1.0.0
  * @date    07-September-2013
  * @brief   Header for delay.c module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DELAY_H
#define _DELAY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported Defines ----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);
void delay(uint32_t count);

#endif /* __DELAY_H */

/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE************/
