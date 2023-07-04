/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_sigfox.c
  * @author  MCD Application Team
  * @brief   Application of the Sigfox Middleware
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

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "app_sigfox.h"
#include "sgfx_app.h"
#include "sys_app.h"
#include "stm32_seq.h"
#ifdef FEATURE_SIGFOX_API_MODE
#include "sgfx_app_api.h"
#endif /* FEATURE_SIGFOX_API_MODE */
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/

void MX_Sigfox_Init(void)
{
  /* USER CODE BEGIN MX_Sigfox_Init_1 */

  /* USER CODE END MX_Sigfox_Init_1 */
  //SystemApp_Init(ACTIVE_APP_SIGFOX);
  Sigfox_Init();
#ifdef FEATURE_SIGFOX_API_MODE
  Sigfox_API_Init();
#endif /* FEATURE_SIGFOX_API_MODE */

  /* USER CODE BEGIN MX_Sigfox_Init_2 */

  /* USER CODE END MX_Sigfox_Init_2 */
}

void MX_Sigfox_Process(void)
{
  /* USER CODE BEGIN MX_Sigfox_Process_1 */

  /* USER CODE END MX_Sigfox_Process_1 */
  UTIL_SEQ_Run(UTIL_SEQ_DEFAULT);
  /* USER CODE BEGIN MX_Sigfox_Process_2 */

  /* USER CODE END MX_Sigfox_Process_2 */
}

/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Private Functions Definition -----------------------------------------------*/

/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
