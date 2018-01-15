# MSc

  COPYRIGHT 2013 IWC Group & STMicroelectronics
  * @file    readme.txt 
  * @author  Mengjia Ding
  * @version V1.0.0
  * @date    09-September-2013
  * @brief   Individual part of the Automatic Detect People Technology Project
  ******************************************************************

@par System Description

This system utilises the STM32F4 DISCOVERY board to develop an Automatic People Detection Technology system. The system at least has three modules, including module A (Set in the entrance), module B (Set in the exit) and module C (PC server). Two 
additional modules are serveing for routeing. The entrance can detect the signal when people come. The exit sends the detected signal of leaving people back to the entrance to calculate the current number of people in the region. Then, the total number of people is displayed on the LCD. When the signal is detected, the camera captures the image of the entrance in real time.

If the number of people reached the limit, it would stop to count. That would trigger the audio alarm to notice the queueing people to wait out of the entrance. 

*** (C) COPYRIGHT 2013 IWC Group & STMicroelectronics ***
 
