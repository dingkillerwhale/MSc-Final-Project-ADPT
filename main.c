/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/Entrance/USER/main.c 
  * @author  IWC Group
  * @version V1.0.0
  * @date    07-September-2013
  * @brief   Main program body
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/	
#include "stm32f4xx.h" 
#include "USART.h"
#include "stdio.h"
#include "delay.h"
#include "xbee.h"
#include "xbeeAPI.h"
#include "key.h"
#include "led.h"
#include "lcd_lib.h"
#include "tim3.h"

/* Init Flag variables */
uint16_t SensorFlag = 0x00;
uint16_t Coordinator_Flag = 0x00;
uint16_t Alarm_Flag = 0x00;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
*/
int main(void)
{	
	uint16_t Counter = 0;
	uint16_t Counter1 = 0;
	SystemInit();
	
	/* Initial TIM3 for the alarm sound */
	Tim3_Config();
	TIM3_GPIO_Config();
	
	/* Config the LED, LCD and the corresponding interrupt */
	LCD_Configuration();
	LED_On();
	Control_NVIC_Init();
	Control_Exit_Init();
	
	/* Config the LED, key and key interrupt */
	//Key_Config();
	LED_GPIO_Config();
	
	/* Initial the pulse pins */
	Pulse_GPIO_Config();
	
	/* Initial USART3,2 and USART3,2 Interrupt */	
	USART3_NVIC_Config();
	USART2_NVIC_Config();
	USART2_Config();
	USART3_Config();
	
	/* Initial the result displayed in LCD */
	LCD_PutS("Counting Number");
	LCD_GotoXY(0,1);
	LCD_PutS("PPLNo: 000ppl");
	
	GPIO_WriteBit(GPIOD,GPIO_Pin_13, 
		    (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_13))));
			
while(1) {
	
	/* Update the amounts of people in LCD displayer (Positive) */	
	if (SensorFlag==1) {
		/* When detect one entering, transmit signal to LCD SSD2119 */
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		
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
			Display_Control(DISBLINK); // Set a blink signal
			SensorFlag = 0;
		}	
		
	}
	
	/* Update the amounts of people in LCD displayer (Nagative) */
	if (SensorFlag==2) {
		/*when detect one leaving, transimit signal to LCD SSD2119 */
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		GPIO_SetBits(GPIOB, GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		
		/* Send the amounts of people nagative */
		apiTX16frame(0x02,SensorFlag);
		
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
	
	/* Check to play the audio to warn the customer when people in the region get full, whcih is 8 person */
	if (Counter > 8)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		
		/* Check the Alarm status */
		if (Alarm_Flag == 0x01)
		{
			/* Generate the Alarm */
			TIM_Cmd(TIM3,ENABLE);
			
			/* Send the alarm inform */
			apiTX16frame(0x03,0x00);
		}
	}
	
	Alarm_Flag = 0x00;
	
	/* Check to execute initial configuration of the XBee module */ 
	if (Coordinator_Flag == 0x01)
	{
		/* Initial XBee module, the DL and DH require to match the source address of destination XBee module */
		Coordinator_Config();
		
		GPIO_WriteBit(GPIOD,GPIO_Pin_13, 
		    (BitAction)((1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_13))));
		
		Coordinator_Flag = 0x00;
	}		
	
	}
}

/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE************/
