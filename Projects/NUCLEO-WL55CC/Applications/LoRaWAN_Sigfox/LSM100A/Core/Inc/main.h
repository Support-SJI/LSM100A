/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include "sys_app.h"


#define ACTIVE_APP_SIGFOX               0
#define ACTIVE_APP_LORAWAN              1

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RTC_N_PREDIV_S 10
#define RTC_PREDIV_S ((1<<RTC_N_PREDIV_S)-1)
#define RTC_PREDIV_A ((1<<(15-RTC_N_PREDIV_S))-1)

#define RF_CTRL1_Pin GPIO_PIN_12
#define RF_CTRL1_GPIO_Port GPIOB
#define RF_CTRL2_Pin GPIO_PIN_13
#define RF_CTRL2_GPIO_Port GPIOC

#define RF_CTRL1_GPIO_CLK_ENABLE()			 __HAL_RCC_GPIOB_CLK_ENABLE()
#define RF_CTRL1_GPIO_CLK_DISABLE()			 __HAL_RCC_GPIOB_CLK_DISABLE()
#define RF_CTRL2_GPIO_CLK_ENABLE()			 __HAL_RCC_GPIOC_CLK_ENABLE()
#define RF_CTRL2_GPIO_CLK_DISABLE()			 __HAL_RCC_GPIOC_CLK_DISABLE()


#define USARTx_RX_Pin GPIO_PIN_3
#define USARTx_RX_GPIO_Port GPIOA
#define USARTx_TX_Pin GPIO_PIN_2
#define USARTx_TX_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
