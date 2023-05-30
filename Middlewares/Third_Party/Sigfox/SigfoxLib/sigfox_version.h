/**
  ******************************************************************************
  * @file    sigfox_version.h
  * @author  MCD Application Team
  * @brief   Identifies the version of Sigfox
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

#ifndef __SIGFOX_VERSION_H__
#define __SIGFOX_VERSION_H__

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

#define __SIGFOX_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __SIGFOX_VERSION_SUB1   (0x07U) /*!< [23:16] sub1 version */
#define __SIGFOX_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define __SIGFOX_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */ 
#define __SIGFOX_VERSION       ((__SIGFOX_VERSION_MAIN <<24)\
                                |(__SIGFOX_VERSION_SUB1 << 16)\
                                |(__SIGFOX_VERSION_SUB2 << 8 )\
                                |(__SIGFOX_VERSION_RC))   
   
/* Exported types ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

#ifdef __cplusplus
}
#endif

#endif /*__SIGFOX_VERSION_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
