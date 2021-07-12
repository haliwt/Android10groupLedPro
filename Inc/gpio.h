/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private defines -----------------------------------------------------------*/
//the first group LED 
#define LEDBCUT_Pin 						GPIO_PIN_6   //PC6--->COM
#define LEDBCUT_GPIO_Port 					GPIOC
//PWM TIM1 PB3 PWM OUT
#define LEDBPWM_Pin 						GPIO_PIN_3   //PB3 --TIM1-CH2
#define LEDBPWM_GPIO_Port 					GPIOB


#define LEDB1_Pin 							GPIO_PIN_11  //PA11 -White LED
#define LEDB1_GPIO_Port 					GPIOA

#define LEDB2_Pin 							GPIO_PIN_12  //PA12 -> Cyan
#define LEDB2_GPIO_Port 					GPIOA

#define LEDB4_Pin 							GPIO_PIN_4  //PB4 ->Orange
#define LEDB4_GPIO_Port 					GPIOB

#define LEDB7_Pin 							GPIO_PIN_8   //PB8->Red
#define LEDB7_GPIO_Port 					GPIOB


#define LEDB8_Pin   						GPIO_PIN_14 //PC14  ->IR1->IR730
#define LEDB8_GPIO_Port 					GPIOC

/************************************************************************/

//The second group GPIO define
#define LEDACUT_Pin 			   			GPIO_PIN_0   //PA0-->COM2 
#define LEDACUT_GPIO_Port 		  			GPIOA
//PWM TIM2 PWM OUT PA1
#define LEDAPWM_Pin 						GPIO_PIN_1   //PA1 -TIM2_CH2
#define LEDAPWM_GPIO_Port 					GPIOA

#define LEDA8_Pin 							GPIO_PIN_1  //PB1 ->UV365
#define LEDA8_GPIO_Port 					GPIOB

#define LEDA7_Pin 							GPIO_PIN_0  //PB0 ->Violet
#define LEDA7_GPIO_Port 					GPIOB

#define LEDA1_Pin 							GPIO_PIN_2  //PA2 ->Blue
#define LEDA1_GPIO_Port 					GPIOA

#define LEDA4_Pin 							GPIO_PIN_5  //PA5 ->Green
#define LEDA4_GPIO_Port 					GPIOA


#define LEDA2_Pin 							GPIO_PIN_3    //PA3->IR2->IR850
#define LEDA2_GPIO_Port 					GPIOA
/************************************************************************************/
//Fan define 
#define FAN_Pin 						GPIO_PIN_8  //PA8
#define FAN_GPIO_Port 					GPIOA
/* USER CODE BEGIN Private defines */

void mainMX_GPIO_Init(void);



#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
