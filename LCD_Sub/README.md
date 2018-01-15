# MSc-ADPT-LCD_HD44780U
LCD Display Codes
/**
  @page Automatic Detect People Technology
  
  @verbatim
  *********** Portions COPYRIGHT 2013 IWC Group & STMicroelectronics ***********
  * @file    readme.txt 
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    09-September-2013
  * @brief   Individual part of the Automatic Detect People Technology Project
  ******************************************************************************
   @endverbatim
  */

@par Local Proejct Description

This sub-project is applied for detection. There are four sub-folders 
and a project file. This project adopts STM32F4 official library.

"\Automatic Detect People Tchnology\Detect\StartUp" folder and 
"\Automatic Detect People Tchnology\Detect\CMSIS" folder contain STM32F4 
system file.

"\Automatic Detect People Tchnology\Detect\FWlib" folder contains STM32F4 
official library.

"\Automatic Detect People Tchnology\Detect\USER" folder contains the user functions.

  In this folder, it includes the function ".c" file and the the header of each file.
  
  display_test_main.c  The main program, calculate the total number of people entering
          depending on the signal from the sensor.

  stm432f4xx_it.c and  stm432f4xx_it.h  Main Interrupt Service. Sensor and key Interrupt 
  
  delay.c and delay.h  Main delay functions
  
  Display_function.c, HD44780U.h and LCD_lib.h   LCD display configuration
  
  Control_Init.c  EXTI configuration

@par Hardware and Software environment 

  - This example has been tested with the following environments:
     - STM32F4DISCOVERY board
     - Carrier Board
     - Infrared Sensor

  - Software development tools
    - MDK-ARM V4.60

  - Hardware Set-up
     - Mount STM322F4DISCOVERY board onto Carrier board
     - Mount Sensor onto discovery board

@par How to use it ?

   In order to load the Project code, you have do the following:
    - MDK-ARM
      - Open the Project.uvproj project
      - Rebuild all files: Project->Rebuild all target files
      - Load project image: Debug->Start/Stop Debug Session
      - Run program: Debug->Run (F5)


/********* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE*********/
 
