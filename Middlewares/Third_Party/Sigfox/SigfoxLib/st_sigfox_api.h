/**
  ******************************************************************************
  * @file    st_sigfox_api.h
  * @author  MCD Application Team
  * @brief   add-on above sigfox_api.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ST_SIGFOX_API_H__
#define __ST_SIGFOX_API_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "sigfox_types.h"
#include "sigfox_api.h"
#include "addon_sigfox_rf_protocol_api.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* payload sizes definition */
#define SGFX_MAX_UL_PAYLOAD_SIZE 12
#define SGFX_MAX_DL_PAYLOAD_SIZE  8

/* Exported function --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __ST_SIGFOX_API_H__ */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
