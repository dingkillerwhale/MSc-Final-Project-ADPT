#include "Device_main.h"


uint16_t KeyFlag = 0x0000;
// FATFS fys;
// FRESULT ret;
// FIL f;

int main(void) {
	SystemInit();
	//STM32f4_Discovery_Debug_Init();
	//USART6_Config();
	STM32f4_Discovery_LCD_Init();
// 	 	USART_SendData(USART6,0x42);
// 	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);
   //while(1 != OV7670_Init());
	OV7670_Init();
// 		 	USART_SendData(USART2,0x43);
// 	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);

//GPIO_SetBits(GPIOD, GPIO_Pin_13);
   Key_Init();

	//NVIC_Configuration();
	
	delay_ms(500);
	//OV7670_HW(uint16_t hstart,uint16_t vstart,uint16_t hstop,uint16_t vstop)
	//OV7670_HW(184,11,40,492);
	//LCD_Clear(Blue);
	//LCD_WriteReg(SSD2119_ENTRY_MODE_REG, 0x6810);
LCD_SetDisplayWindow(0, 0, 320, 240);
   LCD_WriteRAM_Prepare();
	Cam_Start();
	//USART_SendData(USART2,DCMI->DR);
	//while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);
	
// ret = f_mount(0, &fys);
// if(ret == FR_OK)
// {
// 	USART_SendData(USART6,0x44);
// }
// else
// {
// 	USART_SendData(USART6,0x45);
// }
// ret=f_open(&f, "a.bmp", FA_WRITE | FA_CREATE_ALWAYS);
// if(ret == FR_OK)
// {
// 	USART_SendData(USART6,0x46);
// }
// else
// {
// 	USART_SendData(USART6,0x47);
// }
	while(1)
	{
		if(KeyFlag == 0)
				{
					//OV7670_Init();
    	DCMI_Cmd(ENABLE);
			DCMI_CaptureCmd(ENABLE);
    }
// 		if(KeyFlag == 2) {
// 			    init_picture_count();
// // 		SD_Init(); 
// 			
// 			 	USART_SendData(USART6,0x44);
// 			delay(10);
// 	 			//Save_Frame(); 
// 			Capture_Image_TO_Bmp();
// 			//KeyFlag = 2;
// 			while(1);
//      }
// 	if(KeyFlag ==3) {
// 		OV7670_Init();
// 	}
}
// 		
		
		//OV_DCMI();
		//USART_SendData(USART2,DCMI->DR);
  }
	

