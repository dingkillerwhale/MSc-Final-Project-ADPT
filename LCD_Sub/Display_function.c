/**
  ******************************************************************************
  * @file   Automatic_Detect_People_Technology/Detect/SensorDisplay/Display_function.c 
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    28-August-2013
  * @brief   LCD display functions
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "LCD_lib.h"

uint16_t ClearLow8Bits;

void LCD_Initpins (void) {
		
	GPIO_InitTypeDef GPIOA_InitStructure;
	GPIO_InitTypeDef GPIOB_InitStructure;
	GPIO_InitTypeDef GPIOD_InitStructure;
  
  /* LCD Pins GPIOD.0-7 Init */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  
  GPIOD_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2 | GPIO_Pin_3 |
										  GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6 |GPIO_Pin_7 | GPIO_Pin_8 |
	                    GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_13 |GPIO_Pin_11| GPIO_Pin_12);
  GPIOD_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIOD_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIOD_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIOD_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOD, &GPIOD_InitStructure);
  
  /* LCD Control line GPIOB.0-2 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  
  GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2;
  GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIOB_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIOB_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOB, &GPIOB_InitStructure);
  
  /* LCD Control line GPIOA.15 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIOA_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIOA_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOA, &GPIOA_InitStructure);
}


/**
  * @brief  Clear LCD1602 screen.
  * @param  None.
  * @retval None.
  */
void Display_Clear (void) {
	LCD_RS(DISABLE);
	LCD_RW(DISABLE);
	LCD_Write(0x01);
	LCD_Clk();
	
}

/**
  * @brief  Back the cursor to the Home position.
  * @param  None.
  * @retval None.
  */
void Home (void) {
	
	LCD_RS(DISABLE);
	LCD_RW(DISABLE);
	LCD_Write(0x02);
	LCD_Clk();

}

/**
  * @brief  Configure Enter Mode.
  * @param  MODE_IN: where it can be 
  *            @arg HOLD_LEFT: Hold pic and cusor moves left 
  *            @arg ROLL_RIGHT: Hold pic rolls right 
  *            @arg HOLD_RIGHT: Hold pic rolls left  
  *            @arg ROLL_LEFT: Hold pic and cusor move right
  * @retval None.
  */
void Input_Mode (uint16_t MODE ) {
	
	assert_param(IS_MODE_IN(MODE));
	
	LCD_RS(DISABLE);
	LCD_RW(DISABLE);
	LCD_Write(MODE);
	LCD_Clk();

}

/**
  * @brief  Turn on/off Display and Cursor.
  * @param  CONTROL_MODE: where it can be 
  *            @arg DISOFF: Turn off display
  *            @arg DISON: Turn on display, turn off cursor 
  *            @arg DISBLINK: Blink display, turn off cursor  
  *            @arg DISCURSOR: Turn on display, turn on cursor
  *            @arg DISCURSORBLINK: Turn on display, blink cursor
  * @retval None.
  */
void Display_Control (uint16_t MODE ) {
	
	assert_param(IS_CONTROL_MODE(MODE));
	
	LCD_RS(DISABLE);
	LCD_RW(DISABLE);
	LCD_Write(MODE);
	LCD_Clk();

}

/**
  * @brief  Shift Cursor or Display.
  * @param  SHIFT_MODE: where it can be 
  *            @arg CURSORLEFT: Left Shift Cursor by one byte
  *            @arg CURSORRIGHT: Right Shift Cursor by one byte
  *            @arg DISPLAYLFET: Left Shift display by one byte  
  *            @arg DISPLAYRIGHT: Right Shift display by one byte
  * @retval None.
  */
void Cursor_Display_Shift (uint16_t SHIFT_MODE ) {
	
	assert_param(IS_SHIFT_MODE(MODE));
	
	LCD_RS(DISABLE);
	LCD_RW(DISABLE);
	LCD_Write(SHIFT_MODE);
	LCD_Clk();

}

/**
  * @brief  Function Set.
  * @param  FUNCTION_MODE: where it can be
  *            @arg F_MODE1: 4 bit mode, 1/16 duty, 5x8 font, 2 lines
  *            @arg F_MODE2: 8 bit mode, 1/16 duty, 5x8 font, 2 lines  
  * @retval None.
  */
void Function_Set (uint16_t MODE) {
	
	assert_param(IS_FUNCTION_MODE(MODE));
	
	LCD_RS(DISABLE);
	LCD_RW(DISABLE);
	LCD_Write(MODE);
	LCD_Clk();

}

/**
  * @brief  Configure CGRAM Address.
  * @param  CGRAM_Address: where it can be 0x40 - 0x7F
  * @retval None.
  */
void CGRAM_Conf (uint16_t CGRAM_Address ) {
		
	LCD_RS(DISABLE);
	LCD_RW(DISABLE);
	LCD_Write(CGRAM_Address);
	LCD_Clk();

}

/*----------------------------------------------------------------------------
  Function that turns on/off LCD E Signal
 *----------------------------------------------------------------------------*/
void LCD_E(FunctionalState NewState) {
	if (NewState != DISABLE)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	}
}

/*----------------------------------------------------------------------------
  Function that turns on/off LCD RS Signal
 *----------------------------------------------------------------------------*/
void LCD_RS(FunctionalState NewState) {
	if (NewState !=DISABLE)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	}
}

/*----------------------------------------------------------------------------
  Function that turns on/off LCD RW Signal   Read notWrite
 *----------------------------------------------------------------------------*/
void LCD_RW(FunctionalState NewState) {
	if (NewState != DISABLE)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	}
}


/*----------------------------------------------------------------------------
  Function that outputs value to LCD Data Signals
 *----------------------------------------------------------------------------*/
void LCD_DataWrite(uint16_t value) {
	
	ClearLow8Bits = GPIO_ReadOutputData(GPIOD) & 0xFF00;
	value &= 0x00FF; 
	value |= ClearLow8Bits;
	GPIO_Write(GPIOD, value);
	
}

/*----------------------------------------------------------------------------
  Function that clears value on LCD Data Signals
 *----------------------------------------------------------------------------*/
void LCD_DataClear(void) {
	
	 LCD_DataWrite(0x20); // Insert SPACE

}

/*----------------------------------------------------------------------------
  Function that Enables LCD driver
 *----------------------------------------------------------------------------*/
void LCD_Driver (FunctionalState NewState) {
	if (NewState != DISABLE)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_15);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_15);
	}		

}

/*----------------------------------------------------------------------------
  Function that sets LCD Clock
 *----------------------------------------------------------------------------*/
void LCD_Clk (void) {
	LCD_E(ENABLE);
	delay_ms(1);
	LCD_E(DISABLE);
	
}

/*----------------------------------------------------------------------------
  Function that Writes a byte to the LCD - 4 bit mode
 *----------------------------------------------------------------------------*/
void LCD_Write_4Bit (uint16_t value) {
	

	LCD_DataClear();
	LCD_DataWrite(value & 0xF0);
	LCD_Clk();
	delay_ms(1);
	
	LCD_DataClear();
	LCD_DataWrite((value<<4) & 0xF0);
	LCD_Clk();
	delay_ms(1);

}

/*----------------------------------------------------------------------------
  Function that Writes a byte to the LCD - 8 bit mode
 *----------------------------------------------------------------------------*/
void LCD_Write (uint16_t value) {
	
	LCD_DataClear();
	LCD_DataWrite(value);
	LCD_Clk();
	delay_ms(1);
	

}


/*----------------------------------------------------------------------------
  Function that Writes a Character to the LCD
 *----------------------------------------------------------------------------*/
void LCD_PutChar (uint16_t c) {

  LCD_RS(ENABLE);
	LCD_Write(c);
	delay_ms(1);
}	
	
/*----------------------------------------------------------------------------
  Function that Writes a string to the LCD
 *----------------------------------------------------------------------------*/
void LCD_PutS (const char * s) {

  LCD_RS(ENABLE);
	while(*s)
	LCD_Write(*s++);
	delay_ms(1);
}	

/*----------------------------------------------------------------------------
  Function that Sets the Cursor Postion on the LCD
 *----------------------------------------------------------------------------*/
void LCD_GotoXY (uint16_t x, uint16_t y) {

  LCD_RS(DISABLE);
	// x is 0 to 15
	// y is 0 or 1 for line
	if( y == 0 )
		LCD_Write( 0x80 | (x & 0x3F));
	else
		if( y == 1 )
			LCD_Write( 0xC0 | (x & 0x3F));

	delay_ms(1);
}

/*----------------------------------------------------------------------------
  Function that Config LCD 
 *----------------------------------------------------------------------------*/
void LCD_Configuration (void) {
	
	/* LCD pins Init*/
	LCD_Initpins();
	
	/* Enable LCD */
	LCD_Driver(ENABLE);
	
	delay_ms(20);
	
	/* Disable LCD control lines*/
	LCD_E(DISABLE);
	LCD_RS(DISABLE);
	LCD_RW(DISABLE);
	
	/* Delay to config */
	delay_ms(20);
	LCD_Clk();
	delay_ms(1);
	LCD_Clk();
	delay_ms(1);
	LCD_Clk();
	delay_ms(20);
	
	/* Clear Display */
	Display_Clear();
	
	/* Config LCD Mode */
	Function_Set(F_MODE2);
	Display_Control(DISON);
	Input_Mode(HOLD_RIGHT);
	

}

/*----------------------------------------------------------------------------
  Function that write character in the certain place
 *----------------------------------------------------------------------------*/
void LCD_Change (uint16_t x, uint16_t y, char i ) {
   
     LCD_GotoXY (x, y);
     LCD_PutChar((uint16_t)i);
     
}
/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE****/
