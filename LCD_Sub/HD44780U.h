/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/Detect/SensorDisplay/HD44780U.h 
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    28-August-2013
  * @brief   LCD configuration header
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/	
#ifndef _HD44780U_H
#define _HD44780U_H

/*********************************************************************************
 *                                                                               *
 *                          Enter Mode Set 0x04 - 0x07                           *
 *                                                                               *
 *********************************************************************************/

#define HOLD_LEFT              ((uint16_t)0x04)  /* Hold pic and cusor moves left */
#define ROLL_RIGHT             ((uint16_t)0x05)  /* Hold pic rolls right */
#define HOLD_RIGHT             ((uint16_t)0x06)  /* Hold pic rolls left */
#define ROLL_LEFT              ((uint16_t)0x07)  /* Hold pic and cusor move right */

#define IS_MODE_IN(MODE)     (((MODE) == HOLD_LEFT) || \
                              ((MODE) == ROLL_RIGHT) || \
                              ((MODE) == HOLD_RIGHT) || \
                              ((MODE) == ROLL_LEFT))
														 
/*********************************************************************************
 *                                                                               *
 *                  Display on/off Control 0x08 - 0xFH                           *
 *                                                                               *
 *********************************************************************************/
														 
#define DISOFF                 ((uint16_t)0x08)  /* Turn off display */
#define DISON                  ((uint16_t)0x0C)  /* Turn on display, turn off cursor */
#define DISBLINK               ((uint16_t)0x0D)  /* Blink display, turn off cursor */
#define DISCURSOR              ((uint16_t)0x0E)  /* Turn on display, turn on cursor */
#define DISCURSORBLINK         ((uint16_t)0x0F)  /* Turn on display, blink cursor */

#define IS_CONTROL_MODE(MODE) (((MODE) == DISOFF)    || \
                               ((MODE) == DISON)     || \
                               ((MODE) == DISBLINK)  || \
			       ((MODE) == DISCURSOR) || \
                               ((MODE) == DISCURSORBLINK))			

/*********************************************************************************
 *                                                                               *
 *              Cursor or Display Shift 0x10, 0x14, 0x18, 0x1C                   *
 *                                                                               *
 *********************************************************************************/

#define CURSORLEFT             ((uint16_t)0x10)  /* Left Shift Cursor by one byte */
#define CURSORRIGHT            ((uint16_t)0x14)  /* Right Shift Cursor by one byte */
#define DISPLAYLFET            ((uint16_t)0x18)  /* Left Shift display by one byte */
#define DISPLAYRIGHT           ((uint16_t)0x1C)  /* Right Shift display by one byte */


#define IS_SHIFT_MODE(MODE)   (((MODE) == CURSORLEFT)  || \
                               ((MODE) == CURSORRIGHT) || \
			       ((MODE) == DISPLAYLFET) || \
                               ((MODE) == DISPLAYRIGHT))	
															 
/*********************************************************************************
 *                                                                               *
 *                               Function Set                                    *
 *                                                                               *
 *********************************************************************************/

#define F_MODE1             ((uint16_t)0x28)  /* 4 bit mode, 1/16 duty, 5x8 font, 2 lines */
#define F_MODE2             ((uint16_t)0x38)  /* 8 bit mode, 1/16 duty, 5x8 font, 2 lines  */


#define IS_FUNCTION_MODE(MODE)   (((MODE) == F_MODE1)  || \
                                 ((MODE) == F_MODE2))	



#endif

/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE************/

