# MSc-ADPT-Camera_Sub
Camera Sub-system 
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

@par System Description

This system utilises the STM32F4 DISCOVERY board to develop an Automatic People Detection Technology system. The system at least has three modules, including module A (Set in the entrance), module B (Set in the exit) and module C (PC server). Two 
additional modules are serveing for routeing. The entrance can detect the signal when people come. The exit sends the detected signal of leaving people back to the entrance to calculate the current number of people in the region. Then, the total number of people is displayed on the LCD. When the signal is detected, the camera captures the image of the entrance in real time.

If the number of people reached the limit, it would stop to count. That would trigger the audio alarm to notice the queueing people to wait out of the entrance. 

@par Local Proejct Description

This sub-project is applied for Camera-Sub System. There are four sub-folders 
and a project file. This project uses STM32F4 official library.

"\Automatic Detect People Tchnology\Detect\StartUp" folder and 
"\Automatic Detect People Tchnology\Detect\CMSIS" folder contain STM32F4 
system file.

"\Automatic Detect People Tchnology\Detect\FWlib" folder contains STM32F4 
official library.

"\Automatic Detect People Tchnology\Detect\USER" folder contains the user functions.

  In this folder, it includes the function ".c" file and the the header of each file.
  
  main.c  The main program, start the camera to monitor the real time situation and when
          press the button, it will capture the current frame and use FatFs
          to save this picture.

  stm432f4xx_it.c and  stm432f4xx_it.h  Main Interrupt Service. DCMI and key Interrupts 
  
  delay.c and delay.h  Main delay functions
  
  CAMERA_OV7670.c and camera_ov7670.h  Camera configuration
  
  Control_Key.c  Key configuration

@par Hardware and Software environment 

  - This example has been tested with the elements used as follows:
     - STM32F4DISCOVERY board
     - Carrier Board
     - OV7670
     - STM32F4DIS-Base Board
     - Sandisk Micro SD card 2GB
     - External Button

  - Software development tools
    - MDK-ARM V4.60

  - Hardware Set-up
     - Add STM322F4DISCOVERY board onto STM32F4DIS-Base Board
     - Add Camera onto STM32F4DISCOVERY board

@par How to use it ?

   To load the Project code, you have do the following:
    - MDK-ARM
      - Open the Project.uvproj project
      - Rebuild all files: Project->Rebuild all target files
      - Load project image: Debug->Start/Stop Debug Session
      - Run program: Debug->Run (F5)


/********* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE*********/
 
