/**
  ******************************************************************************
  * @file    Automatic_Detect_People_Technology/SDcard_1/CamSD/main.c
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    02-September-2013
  * @brief   Main program body
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/	
#include "stm32f4xx.h"
#include "misc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_usart.h"
#include "diskio.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "stm32f4_discovery_sdio_sd.h"
#include "ff.h"
#include "string.h"
#include "stdio.h"

#include "Control_Key.h"
#include "Camera_ov7670.h"
#include "delay.h"

/* Init varibles */
uint8_t R,G,B = 0;
char  file_str[30] = {0};
uint32_t pic_counter = 0;

uint16_t KeyFlag = 0x0000;

static int32_t set_pic_count(void);
static int32_t get_pic_count(void);
void Save(void);

FIL fileW;
FATFS fs;
UINT bw =0;       

/* The image buffer to store */
uint8_t image_buf[960] = {0};

/* BMP 24 bit Header */
static uint8_t bmp_header[54]={
  0x42, 0x4D, 0x36, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 
  0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/**
  * @brief  Main program.
  * @param  None
  * @retval None
*/
int main(void) {
	/* System Init*/
  	SystemInit();
	
	/* LCD SSD2119 Init*/
	STM32f4_Discovery_LCD_Init();
	
	/* OV7670 Init*/
	OV7670_Init();
	
	/* LED Init */
	LED_Init();
	
	/* Key Init */
	Key_Init();
	delay_ms(500);
	
	/* Set the window size of the LCD SSD2119 */
	LCD_SetDisplayWindow(0, 0, 320, 240);
  	LCD_WriteRAM_Prepare();
	
	/* Start the camera */
	Cam_Start();
	
	while(1){ 
	  	/* Judge the KeyFlag to execute the following steps */
		switch(KeyFlag){
			/* Keep Continuous state */
			case 0:
				DCMI_Cmd(ENABLE);
				DCMI_CaptureCmd(ENABLE);
				break;
			/* Change to Capture state */
			case 2:	
				/* Power Down the camera */		
	    			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
				/* Save the picture */		
	    			Save();
				/* Clear Key Flag */
		  		KeyFlag =0;
				/* Set LED12 when finish the saving */
	    			GPIO_SetBits(GPIOD, GPIO_Pin_12);
 				break;

  			default:
				break;
		}
	}

}
/**
  * @brief  Save picture program.
  * @param  None
  * @retval None
*/
void Save(void)
{	
  	/* Init variables */
  	int32_t  i = 0;
  	int32_t  j = 0;
  	int16_t  data_temp = 0;
	
	/* Get teh picture number */
 	 pic_counter = get_pic_count();

	/* Register a file system object to the FatFs module */
	f_mount(0,&fs);		   
  
	/* Name this new file name */
	sprintf(file_str, "0:/Demo%d.bmp",pic_counter);
	
	/* Create a new file */
	f_open(&fileW,file_str,FA_CREATE_NEW | FA_WRITE);
	
	/* Write the header into this file */
  	f_write(&fileW, bmp_header, sizeof(bmp_header), &bw); 
  
	/* Loop to read one frame data from SRAM */
	for (j = 0; j < 240; j++){
    		for(i=0;i<320;i++){ 
      			data_temp = LCD_ReadRAM();
			/* Change to RGB888 */
      			R = (data_temp>>8)&0xF8;
      			G = (data_temp>>3)&0xFC;
      			B = (data_temp<<3)&0xF8;
			
      			image_buf[i*3+2] = R;
      			image_buf[i*3+1] = G;
      			image_buf[i*3+0] = B;
		}
	/* Write the frame data into this new file */
    	f_write(&fileW, image_buf, 960, &bw);
	}

	/* Close this file */
  	f_close(&fileW); 
	f_mount(0,NULL);
  
	/* Save the picture number point*/
	pic_counter++;  
	set_pic_count();

}
/**
  * @brief  Save picture number point program.
  * @param  None
  * @retval number 
*/
static int32_t set_pic_count(void){
	/* Init variables */
  	int32_t ret = -1;
  	uint32_t bw = 0;
  	FIL file;		

 	/* mount the filesys */
  	if (f_mount(0, &fs) != FR_OK) {
    		return -1;
	}
  
	/* Open data file to store the picture number point */
  	ret = f_open(&file, "counter.dat", FA_OPEN_EXISTING | FA_WRITE);
  
	/* If this file exists, write the new point */
	if (ret == FR_OK) {
    		ret = f_write(&file, &pic_counter, sizeof(uint32_t), &bw);
    		f_close(&file);
    		f_mount(0, NULL);
    		return pic_counter;
	} 
	/* If this file doesn't exist, close it  */
	else {
    	f_close(&file);
    	f_mount(0, NULL);
   	return -1;
  	}

}
/**
  * @brief  Get picture number point program.
  * @param  None
  * @retval number 
*/
static int32_t get_pic_count(void)
{
	int32_t ret = -1;
  	uint32_t bw = 0;
  	FIL file;		

  	/* Mount the filesys */
  	f_mount(0, &fs);
  	/* Read the data file to find the picture number point */
  	ret = f_open(&file, "counter.dat", FA_OPEN_EXISTING | FA_READ);
  
	/* If this file doesn't exist, create it */
	if (ret != FR_OK){
    		f_close(&file);
    		ret = f_open(&file,"counter.dat", FA_CREATE_ALWAYS | FA_WRITE);
    		if (ret == FR_OK){
      			pic_counter = 0;
      			ret = f_write(&file, &pic_counter, sizeof(uint32_t), &bw);
      			f_close(&file);
      			f_mount(0, NULL);
      			return pic_counter;
		} 
		else{
      			f_close(&file);
      			f_mount(0, NULL);
      			return -1;
		}
	} 
	/* If this file exists, read it */
	else{
    		ret = f_read(&file, &pic_counter, sizeof(uint32_t), &bw);
    		f_close(&file);
    		f_mount(0, NULL);
    		return pic_counter;
	}
}
/******************* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE****/


