/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sgfx_eeprom_if.h
  * @author  MCD Application Team
  * @brief   eeprom interface to the upper module.
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
#ifndef __LORA_EEPROM_IF_H__
#define __LORA_EEPROM_IF_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "se-identity.h"



/* Exported types ------------------------------------------------------------*/
typedef enum
{
#if defined(__CC_ARM) /* when changing tool chain the EEPROM shall be re-initialized */
  E2P_LORA_SET = (uint32_t)0xAA,   /* Set by Keil */
#elif defined(__ICCARM__)
  E2P_LORA_SET = (uint32_t) 0xBB,   /* Set by IAR */
#else  /* __GNUC__ */
  E2P_LORA_SET = (uint32_t) 0xCC,   /* Set by GCC */
#endif /* __CC_ARM | __ICCARM__ | __GNUC__ */
  E2P_LORA_RST = (uint32_t)  0     /* EEPROM has not yet been set or has been erased */
} E2P_LORA_flagStatus_t;

typedef enum
{
  E2P_LORA_OK = (uint32_t)1,   /* Set by Keil */
  E2P_LORA_KO = (uint32_t)0     /* EEPROM has not yet been set or has been erased */
} E2P_LORA_ErrorStatus_t;

/* External variables --------------------------------------------------------*/
typedef enum
{
  EE_LORA_INIT_ID = 0,
  EE_LORA_TYPE_ID,					// 0: NONE 1:ABP	2: OTAA 
  EE_LORA_CLASS_ID,					// 0: CLASS_A 1:CLASS_B	2: CLASS_C 
  EE_LORA_NETWORK_TYPE_ID,
  EE_LORA_WORD0_APPKEY_ID,
  EE_LORA_WORD1_APPKEY_ID,
  EE_LORA_WORD2_APPKEY_ID,
  EE_LORA_WORD3_APPKEY_ID, 
  EE_LORA_WORD0_NWKKEY_ID,
  EE_LORA_WORD1_NWKKEY_ID,
  EE_LORA_WORD2_NWKKEY_ID,
  EE_LORA_WORD3_NWKKEY_ID,
  EE_LORA_WORD0_APPSKEY_ID,
  EE_LORA_WORD1_APPSKEY_ID,
  EE_LORA_WORD2_APPSKEY_ID,
  EE_LORA_WORD3_APPSKEY_ID,
  EE_LORA_WORD0_NWKSKEY_ID,
  EE_LORA_WORD1_NWKSKEY_ID,
  EE_LORA_WORD2_NWKSKEY_ID,
  EE_LORA_WORD3_NWKSKEY_ID,
  EE_LORA_WORD0_APPEUI_ID,
  EE_LORA_WORD1_APPEUI_ID,

  EE_LORA_MODE_ID,
  EE_LORA_FW_MODE_ID,
  EE_LORA_DEVNONCE_ID,
  EE_LORA_CONFIRMNBTRANS_ID,
  EE_LORA_UNCONFIRMNBTRANS_ID,
  EE_LORA_ABP_FCNT_ID,
  
  EE_LORA_ID_COUNT,
	EE_LORA_WORD0_DEVADDR,
	EE_LORA_ABP_HIGH16BIT_FCNT_ID,
} e_EE_LORA_ID;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

/*!
 * @brief Initializes the Eeprom
 * @note  DEFAULT_FACTORY_SETTINGS are written E2pData
 */
void E2P_LORA_Init(void);

/*!
 * @brief Initializes the Eeprom
 * @note  DEFAULT_FACTORY_SETTINGS are written E2pData
 */
void E2P_LORA_RestoreFs(void);
   
int16_t E2P_LORA_Read_Type(void);

void E2P_LORA_Write_Type(int16_t Type);

uint8_t E2P_LORA_Read_Class(void);

void E2P_LORA_Write_Class(uint8_t Class);


uint8_t E2P_LORA_FW_Read_Mode(void);
void E2P_LORA_FW_Write_Mode(uint8_t LoRaMode);


uint8_t E2P_LORA_Read_Mode(void);
void E2P_LORA_Write_Mode(uint8_t LoRaMode);

uint16_t E2P_LORA_Read_DevNonce(void);
void E2P_LORA_Write_DevNonce(uint16_t DevNonce);

uint32_t E2P_LORA_Read_ABP_Fcnt(void);
void E2P_LORA_Write_ABP_Fcnt(uint32_t Fcnt);

uint32_t E2P_LORA_Read_ABP_High16bit_DL_Fcnt(void);
void E2P_LORA_Write_ABP_High16bit_DL_Fcnt(uint32_t Fcnt);

uint8_t E2P_LORA_Read_Network_Type(void);
void E2P_LORA_Write_Network_Type(uint8_t NetworkType);

uint8_t E2P_LORA_Read_Confirmed_Retrans(void);
void E2P_LORA_Write_Confirmed_Retrans(uint8_t UnconNbTrans);

uint8_t E2P_LORA_Read_Unconfirmed_Retrans(void);
void E2P_LORA_Write_Unconfirmed_Retrans(uint8_t UnconNbTrans);

void E2P_LORA_Read_DevAddr(uint8_t *pRDevAddr);
void E2P_LORA_Write_DevAddr(uint8_t *pWDevAddr);

void E2P_LORA_Read_Appeui(uint8_t *pRappEui);
void E2P_LORA_Write_Appeui(uint8_t *pWappEui);

void E2P_LORA_Read_Appkey(uint8_t *pRappKey);
void E2P_LORA_Write_Appkey(uint8_t *pWappKey);

void E2P_LORA_Read_Nwkkey(uint8_t *pRnwkKey);
void E2P_LORA_Write_Nwkkey(uint8_t *pWnwkKey);

void E2P_LORA_Read_App_S_key(uint8_t *pRappSKey);
void E2P_LORA_Write_App_S_key(uint8_t *pWappSKey);

void E2P_LORA_Read_Nwk_S_key(uint8_t *pRnwkSKey);
void E2P_LORA_Write_Nwk_S_key(uint8_t *pWnwkSKey);




#endif /* __LORA_EEPROM_IF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
