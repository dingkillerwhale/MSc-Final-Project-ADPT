
#include "bmp.h"
#include "stm32f4_discovery_lcd.h"

uint8_t R,G,B = 0;
char  file_str[30] = {0};
uint32_t pic_counter = 0;


static int32_t set_pic_count(void);
static int32_t get_pic_count(void);

FIL fileW;
FATFS fs;
UINT br, bw;            // File R/W count
//BYTE buffer[512];       // file copy buffer
//BYTE textFileBuffer[] = "1234567 \r\n";

/*read the image buf*/
uint8_t image_buf[1024] = {0};

static uint8_t bmp_header[54]={
  0x42, 0x4D, 0x36, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 
  0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void Save_Frame(void){	

  int32_t  i = 0;
  int32_t  j = 0;
  int16_t  data_temp = 0;
  uint32_t bw = 0;

	pic_counter = get_pic_count();
	f_mount(0,&fs);		   
  	sprintf(file_str, "0:/Demo%d.bmp",pic_counter);
	f_open(&fileW,file_str,FA_CREATE_NEW | FA_WRITE); 
	f_write(&fileW, bmp_header, sizeof(bmp_header), &bw); 
 
	for (j = 0; j < 240; j++){
    		for(i=0;i<320;i++){ 
     			data_temp = LCD_ReadRAM();;
      			R = (data_temp>>8)&0xF8;
      			G = (data_temp>>3)&0xFC;
      			B = (data_temp<<3)&0xF8;
      			image_buf[i*3+2] = R;
      			image_buf[i*3+1] = G;
      			image_buf[i*3+0] = B;
    		}
    		f_write(&fileW, image_buf, 960, &bw);
  	}
	
   	f_close(&fileW); 
	
	    f_mount(0, NULL);
       pic_counter++;  
	     set_pic_count();
	  
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/


static int32_t set_pic_count(void){
	int32_t ret = -1;
  	uint32_t bw = 0;
  	FIL file;		

 	/* mount the filesys */
  	if (f_mount(0, &fs) != FR_OK) {
    		return -1;
  	}

  	ret = f_open(&file, "counter.dat", FA_OPEN_EXISTING | FA_WRITE);
  	if (ret == FR_OK) {
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

static int32_t get_pic_count(void){
	int32_t ret = -1;
  	uint32_t bw = 0;
  	FIL file;		

  	/* mount the filesys */
  	f_mount(0, &fs);
 	ret = f_open(&file, "counter.dat", FA_OPEN_EXISTING | FA_READ);
  	if (ret != FR_OK) {
    		f_close(&file);
    		ret = f_open(&file,"counter.dat", FA_CREATE_ALWAYS | FA_WRITE);
    		if (ret == FR_OK) {
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
	else{
    		ret = f_read(&file, &pic_counter, sizeof(uint32_t), &bw);
    		f_close(&file);
    		f_mount(0, NULL);
    		return pic_counter;
  	}
}
