/**
  ******************************************************************************
  * @file   Automatic_Detect_People_Technology/Detect/SensorDisplay/LCD_lib.h
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    28-August-2013
  * @brief   LCD display configuration
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#ifndef _LCD_H
#define _LCD_H

#define LCD_NUM 8    /* Number of user LCDs          */


#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "HD44780U.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "stm32f4xx_it.h"
#include "delay.h"

void LCD_Configuration (void);
void LCD_Initpins (void);
void LCD_E (FunctionalState NewState);
void LCD_RS (FunctionalState NewState);
void LCD_RW (FunctionalState NewState);
void LCD_DataWrite (uint16_t value);
void LCD_DataClear (void);

void LCD_Driver (FunctionalState NewState);

void LCD_Clk (void);
void LCD_Write (uint16_t value);
void LCD_Clear (void);
void LCD_PutChar (uint16_t c);
void LCD_PutS (const char * s);
void LCD_GotoXY (uint16_t x, uint16_t y);

void Display_Clear (void);
void Home (void);
void Input_Mode (uint16_t MODE );
void Display_Control (uint16_t MODE );
void Cursor_Display_Shift (uint16_t SHIFT_MODE );
void Function_Set (uint16_t MODE);
void CGRAM_Conf (uint16_t CGRAM_Address );
void LCD_Write_4Bit (uint16_t value);
void LCD_Change (uint16_t x, uint16_t y, char i );

void Control_NVIC_Init (void);
void LED_On(void);
void LED_Off(void);
void Control_Exit_Init (void);

#endif
/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE****/
