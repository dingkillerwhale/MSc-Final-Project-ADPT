# MSc
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

This system utilises the STM32F4 DISCOVERY board to develop an Automatic Detect
People Technology system. The system has three main modules, including module A
(Set in the entrance), module B (Set in the exit) and module C (PC server). Two 
additional modules are served for routeing. 

Both of the entrance and the exit could detect the people. The exit sends the 
detected signal to the entrance to count the number of people in this region. 
Then the number of people is displayed in two LCD displayer. When the signal is
detected, the camera captures the image at the entrance in real time. Additionally
the number of people is also sent to PC server to display.

If the number of people reach the threshold, it stops counting the number of
people. This triggers to play the alarm stored in the SD card, which is used
to warn people stay out of entrance.

/********* (C) COPYRIGHT 2013 IWC Group & STMicroelectronics *****END OF FILE*********/
 
