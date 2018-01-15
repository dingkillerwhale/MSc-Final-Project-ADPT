/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/Detect/SensorDisplay/display_test_main.c 
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    28-August-2013
  * @brief   Main program
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "LCD_lib.h"

uint16_t SensorFlag= 0;


int main (void) {

	uint16_t Counter = 0;
	uint16_t Counter1 = 0;
	SystemInit();
	
  /* Config the LED, LCD and the corresponding interrupt */
	LCD_Configuration();
	LED_On();
  Control_NVIC_Init();
	Control_Exit_Init();

	/* Initial the result displayed in LCD */
  LCD_PutS("Counting Number ");
  LCD_GotoXY(0,1);
  LCD_PutS("PPLNo: 000ppl");
	
	while(1) {
		
	/* Update the amounts of people in LCD displayer (Positive) */		
	if (SensorFlag==1) {
		/* Calculate the number of unit's digit */		
		if(Counter < 9) {
			 Display_Control(DISON);
			 LCD_GotoXY(10,1);
       LCD_PutS("ppl");
		   LCD_Change(9,1,(char)(Counter + '1'));
	     SensorFlag = 0;
		}
			
		Counter++;
		/* Calculate the number of ten's digit */
	  if(Counter==10 && Counter1 < 2) {
			
			LCD_Change(8,1,(char)(Counter1 + '1'));
			LCD_Change(9,1,'0');
		  Counter1++;
			Counter = 0;
			SensorFlag = 0;
		  
	  }
		/* Get warning when it reaches 30 ppl */
		else if(Counter==10 && Counter1==2) {
			Counter = 0;
	   	Counter1 = 0;
      LCD_Change(9,1,'0');
			LCD_Change(8,1,(char)(Counter1 +'0'));
			LCD_GotoXY(10,1);
			LCD_PutS("W   ");
			LCD_GotoXY(10,1);
			Display_Control(DISBLINK);// Set a blink signal
			SensorFlag = 0;
		}	
		
	}
	/* Update the amounts of people in LCD displayer (Nagative) */
	if (SensorFlag==2) {
		/* Decrease in unit's digit*/
    if(Counter!=0) {
			Counter -= 1 ;
		   LCD_Change(9,1,(char)(Counter + '0'));
	     SensorFlag = 0;
		}
		/* Decrease in ten's digit*/
		else if(Counter1!=0) {
			Counter1 -= 1;
			Counter = 9;
			LCD_Change(8,1,(char)(Counter1 + '0'));
			LCD_Change(9,1,(char)(Counter  + '0'));
		SensorFlag = 0;
    }
	}
 }
}
/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE************/
