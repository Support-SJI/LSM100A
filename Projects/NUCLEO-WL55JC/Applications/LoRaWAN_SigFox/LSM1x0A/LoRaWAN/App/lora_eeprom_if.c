/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sgfx_eeprom_if.c
  * @author  MCD Application Team
  * @brief   eeprom interface to the sigfox component
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
#include <stdint.h>
#include "lora_eeprom_if.h"
#include "lora_ee.h"
#include "sys_conf.h"
#include "utilities_conf.h"
#include "radio_board_if.h"
#include "utilities.h"


/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
enum
{
  EE_BANK_0 = 0,
  EE_BANK_1 = 1
};

enum
{
  EE_CLEAN_MODE_POLLING = 0,
  EE_CLEAN_MODE_IT = 1
};

enum
{
  NO_FORMAT =         0,
  FORMAT =            1
};

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
/**
  * @brief        Read Sigfox Configuration from eeprom
  * @param addr   variable virtual address
  * @param data   pointer to a 32-bit word (allocated by the caller) containing the
  *               variable value in case of success.
  */
void E2P_LORA_Read(e_EE_LORA_ID addr, uint32_t *data);

/**
  * @brief        Write Sigfox Configuration to eeprom
  * @param addr   variable virtual address
  * @param data   32-bit data word to be written
  */
void E2P_LORA_Write(e_EE_LORA_ID addr, uint32_t data);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/
void E2P_LORA_Init(void)
{
  /* USER CODE BEGIN E2P_Init_1 */

  /* USER CODE END E2P_Init_1 */
  HAL_FLASH_Unlock();

  if (EE_LoRa_Init(NO_FORMAT, EE_LORA_BASE_ADRESS) != EE_OK)
  {
    if (EE_LoRa_Init(FORMAT, EE_LORA_BASE_ADRESS) == EE_OK)
    {
      E2P_LORA_RestoreFs();
    }
    else
    {
      Error_Handler();
    }
  }
  HAL_FLASH_Lock();
}

void E2P_LORA_RestoreFs(void)
{
  HAL_FLASH_Unlock();
  E2P_LORA_Write(EE_LORA_TYPE_ID, 2);							// 0: NONE 		1:ABP		2: OTAA 
  E2P_LORA_Write(EE_LORA_CLASS_ID, 0);							// 0: CLASS_A 	1:CLASS_B	2: CLASS_C 
//-------------------------------------------------------------------------------------------
  E2P_LORA_Write(EE_LORA_WORD0_APPKEY_ID, LORA_APPKEY_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD1_APPKEY_ID, LORA_APPKEY_WORD_1);
  E2P_LORA_Write(EE_LORA_WORD2_APPKEY_ID, LORA_APPKEY_WORD_2);
  E2P_LORA_Write(EE_LORA_WORD3_APPKEY_ID, LORA_APPKEY_WORD_3);

  E2P_LORA_Write(EE_LORA_WORD0_NWKKEY_ID, LORA_NWKKEY_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD1_NWKKEY_ID, LORA_NWKKEY_WORD_1);
  E2P_LORA_Write(EE_LORA_WORD2_NWKKEY_ID, LORA_NWKKEY_WORD_2);
  E2P_LORA_Write(EE_LORA_WORD3_NWKKEY_ID, LORA_NWKKEY_WORD_3);

  E2P_LORA_Write(EE_LORA_WORD0_APPSKEY_ID, LORA_APPSKEY_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD1_APPSKEY_ID, LORA_APPSKEY_WORD_1);
  E2P_LORA_Write(EE_LORA_WORD2_APPSKEY_ID, LORA_APPSKEY_WORD_2);
  E2P_LORA_Write(EE_LORA_WORD3_APPSKEY_ID, LORA_APPSKEY_WORD_3);

  E2P_LORA_Write(EE_LORA_WORD0_NWKSKEY_ID, LORA_NWKSKEY_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD1_NWKSKEY_ID, LORA_NWKSKEY_WORD_1);
  E2P_LORA_Write(EE_LORA_WORD2_NWKSKEY_ID, LORA_NWKSKEY_WORD_2);
  E2P_LORA_Write(EE_LORA_WORD3_NWKSKEY_ID, LORA_NWKSKEY_WORD_3);

  E2P_LORA_Write(EE_LORA_WORD0_APPEUI_ID, LORA_APPEUI_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD1_APPEUI_ID, LORA_APPEUI_WORD_1);

//-------------------------------------------------------------------------------------------  
  E2P_LORA_Write(EE_LORA_MODE_ID, 1);					  		//  0: Disable	  	1: enable
  E2P_LORA_Write(EE_LORA_FW_MODE_ID, 0);			  	//  0: HIGH/LOW		1: LOW		  2: HIGH
  E2P_LORA_Write(EE_LORA_DEVNONCE_ID, 0);
  E2P_LORA_Write(EE_LORA_CONFIRMNBTRANS_ID, 1);
  E2P_LORA_Write(EE_LORA_UNCONFIRMNBTRANS_ID, 1);
  E2P_LORA_Write(EE_LORA_ABP_FCNT_ID, 0);
  E2P_LORA_Write(EE_LORA_ABP_HIGH16BIT_FCNT_ID, 0);
  HAL_FLASH_Lock();
	
	uint32_t UDN = LL_FLASH_GetUDN();
	E2P_LORA_Write_DevAddr((uint8_t*)&UDN);
	
  /* USER CODE BEGIN E2P_RestoreFs_2 */

  /* USER CODE END E2P_RestoreFs_2 */
}

uint8_t E2P_LORA_Read_Class(void)
{
  /* USER CODE BEGIN E2P_Read_Class_1 */

  /* USER CODE END E2P_Read_Class_1 */
  uint32_t Class = 0 ;
  E2P_LORA_Read(EE_LORA_CLASS_ID, &Class);
  return (uint8_t) Class;
  /* USER CODE BEGIN E2P_Read_Class_2 */

  /* USER CODE END E2P_Read_Class_2 */
}

void E2P_LORA_Write_Class(uint8_t Class)
{
  /* USER CODE BEGIN E2P_Write_Class_1 */

  /* USER CODE END E2P_Write_Class_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_CLASS_ID, (uint32_t)Class);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_Class_2 */

  /* USER CODE END E2P_Write_Class_2 */
}


int16_t E2P_LORA_Read_Type(void)
{
  /* USER CODE BEGIN E2P_Read_Type_1 */

  /* USER CODE END E2P_Read_Type_1 */
  uint32_t Type = 0 ;
  E2P_LORA_Read(EE_LORA_TYPE_ID, &Type);
  return (int16_t) Type;
  /* USER CODE BEGIN E2P_Read_Type_2 */

  /* USER CODE END E2P_Read_Type_2 */
}

void E2P_LORA_Write_Type(int16_t Type)
{
  /* USER CODE BEGIN E2P_Write_Type_1 */

  /* USER CODE END E2P_Write_Type_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_TYPE_ID, (uint32_t)Type);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_Type_2 */

  /* USER CODE END E2P_Write_Type_2 */
}


uint8_t E2P_LORA_Read_Mode(void)
{
  /* USER CODE BEGIN E2P_Read_Mode_1 */

  /* USER CODE END E2P_Read_Mode_1 */
  uint32_t LoRaMode = 1;
  E2P_LORA_Read(EE_LORA_MODE_ID, &LoRaMode);
  return (uint8_t) LoRaMode;
  /* USER CODE BEGIN E2P_Read_Mode_2 */

  /* USER CODE END E2P_Read_Mode_2 */
}

void E2P_LORA_Write_Mode(uint8_t LoRaMode)
{
  /* USER CODE BEGIN E2P_Write_Mode_1 */

  /* USER CODE END E2P_Write_Mode_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_MODE_ID, (uint32_t) LoRaMode);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_Mode_2 */

  /* USER CODE END E2P_Write_Mode_2 */
}

uint8_t E2P_LORA_FW_Read_Mode(void)

{
  /* USER CODE BEGIN E2P_Read_FW_Mode_1 */

  /* USER CODE END E2P_Read_FW_Mode_1 */
  uint32_t FWLoRaMode = 0;
  E2P_LORA_Read(EE_LORA_FW_MODE_ID, &FWLoRaMode);
  return (uint8_t) FWLoRaMode;
  /* USER CODE BEGIN E2P_Read_FW_Mode_2 */

  /* USER CODE END E2P_Read_FW_Mode_2 */
}
void E2P_LORA_FW_Write_Mode(uint8_t LoRaMode)

{
  /* USER CODE BEGIN E2P_Write_FW_Mode_1 */

  /* USER CODE END E2P_Write_FW_Mode_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_FW_MODE_ID, (uint32_t) LoRaMode);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_FW_Mode_2 */

  /* USER CODE END E2P_Write_FW_Mode_2 */
}

uint16_t E2P_LORA_Read_DevNonce(void)
{
  /* USER CODE BEGIN E2P_Read_DevNonce_1 */

  /* USER CODE END E2P_Read_DevNonce_1 */
  uint32_t DevNonce = 0;
  E2P_LORA_Read(EE_LORA_DEVNONCE_ID, &DevNonce);
  return (uint16_t) DevNonce;
  /* USER CODE BEGIN E2P_Read_DevNonce_2 */

  /* USER CODE END E2P_Read_DevNonce_2 */
}

void E2P_LORA_Write_DevNonce(uint16_t DevNonce)
{
  /* USER CODE BEGIN E2P_Write_DevNonce_1 */

  /* USER CODE END E2P_Write_DevNonce_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_DEVNONCE_ID, (uint32_t)DevNonce);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_DevNonce_2 */

  /* USER CODE END E2P_Write_DevNonce_2 */
}

uint32_t E2P_LORA_Read_ABP_Fcnt(void)
{
  /* USER CODE BEGIN E2P_Read_ABP_Fcnt_1 */

  /* USER CODE END E2P_Read_ABP_Fcnt_1 */
  uint32_t Fcnt = 0;
  E2P_LORA_Read(EE_LORA_ABP_FCNT_ID, &Fcnt);
  return Fcnt;
  /* USER CODE BEGIN E2P_Read_ABP_Fcnt_2 */

  /* USER CODE END E2P_Read_ABP_Fcnt_2 */
}

void E2P_LORA_Write_ABP_Fcnt(uint32_t Fcnt)
{
  /* USER CODE BEGIN E2P_Write_ABP_Fcnt_1 */

  /* USER CODE END E2P_Write_ABP_Fcnt_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_ABP_FCNT_ID, Fcnt);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_ABP_Fcnt_2 */

  /* USER CODE END E2P_Write_ABP_Fcnt_2 */
}

uint32_t E2P_LORA_Read_ABP_High16bit_DL_Fcnt(void)
{
  /* USER CODE BEGIN E2P_Read_ABP_Fcnt_1 */

  /* USER CODE END E2P_Read_ABP_Fcnt_1 */
  uint32_t Fcnt = 0;
  E2P_LORA_Read(EE_LORA_ABP_HIGH16BIT_FCNT_ID, &Fcnt);
  return Fcnt;
  /* USER CODE BEGIN E2P_Read_ABP_Fcnt_2 */

  /* USER CODE END E2P_Read_ABP_Fcnt_2 */
}

void E2P_LORA_Write_ABP_High16bit_DL_Fcnt(uint32_t Fcnt)
{
  /* USER CODE BEGIN E2P_Write_ABP_Fcnt_1 */

  /* USER CODE END E2P_Write_ABP_Fcnt_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_ABP_HIGH16BIT_FCNT_ID, Fcnt);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_ABP_Fcnt_2 */

  /* USER CODE END E2P_Write_ABP_Fcnt_2 */
}


uint8_t E2P_LORA_Read_Network_Type(void)
{
  /* USER CODE BEGIN E2P_Read_Network_Type_1 */

  /* USER CODE END E2P_Read_Network_Type_1 */
  uint32_t NetworkType;
  E2P_LORA_Read(EE_LORA_NETWORK_TYPE_ID, &NetworkType);
  
  return (uint8_t) NetworkType;
  /* USER CODE BEGIN E2P_Read_Network_Type_2 */

  /* USER CODE END E2P_Read_Network_Type_2 */
}

void E2P_LORA_Write_Network_Type(uint8_t NetworkType)
{
  /* USER CODE BEGIN E2P_Write_Network_Type_1 */

  /* USER CODE END E2P_Write_Network_Type_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_NETWORK_TYPE_ID, (uint32_t) NetworkType);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_Network_Type_2 */

  /* USER CODE END E2P_Write_Network_Type_2 */
}

uint8_t E2P_LORA_Read_Confirmed_Retrans(void)
{
  /* USER CODE BEGIN E2P_Read_Confirmed_Retrans_1 */

  /* USER CODE END E2P_Read_Confirmed_Retrans_1 */
  uint32_t NbTrans;
  E2P_LORA_Read(EE_LORA_CONFIRMNBTRANS_ID, &NbTrans);
  
  return (uint8_t) NbTrans;
  /* USER CODE BEGIN E2P_Read_Confirmed_Retrans_2 */

  /* USER CODE END E2P_Read_Confirmed_Retrans_2 */
}

void E2P_LORA_Write_Confirmed_Retrans(uint8_t NbTrans)
{
  /* USER CODE BEGIN E2P_Write_Confirmed_Retrans_1 */

  /* USER CODE END E2P_Write_Confirmed_Retrans_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_CONFIRMNBTRANS_ID, (uint32_t) NbTrans);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_Confirmed_Retrans_2 */

  /* USER CODE END E2P_Write_Confirmed_Retrans_2 */
}

uint8_t E2P_LORA_Read_Unconfirmed_Retrans(void)
{
  /* USER CODE BEGIN E2P_Read_Unconfirmed_Retrans_1 */

  /* USER CODE END E2P_Read_Unconfirmed_Retrans_1 */
  uint32_t NbTrans;
  E2P_LORA_Read(EE_LORA_UNCONFIRMNBTRANS_ID, &NbTrans);
  
  return (uint8_t) NbTrans;
  /* USER CODE BEGIN E2P_Read_Unconfirmed_Retrans_2 */

  /* USER CODE END E2P_Read_Unconfirmed_Retrans_2 */
}

void E2P_LORA_Write_Unconfirmed_Retrans(uint8_t NbTrans)
{
  /* USER CODE BEGIN E2P_Write_Unconfirmed_Retrans_1 */

  /* USER CODE END E2P_Write_Unconfirmed_Retrans_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_UNCONFIRMNBTRANS_ID, (uint32_t) NbTrans);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_Unconfirmed_Retrans_2 */

  /* USER CODE END E2P_Write_Unconfirmed_Retrans_2 */
}


void E2P_LORA_Read_DevAddr(uint8_t *pRDevAddr)
{
	 /* USER CODE BEGIN E2P_Read_Appeui_1 */
  lora_u32 config_words;
  uint8_t RDevAddr[4];

  memset1(RDevAddr, 0, sizeof(RDevAddr));
  /* USER CODE END E2P_Read_Appeui_1 */

  E2P_LORA_Read(EE_LORA_WORD0_DEVADDR, (uint32_t *) &config_words);

  /* USER CODE BEGIN E2P_Read_Appeui_2 */

  	RDevAddr[0] = (uint8_t) (config_words >> 24);
  	RDevAddr[1] = (uint8_t) (config_words >> 16);
  	RDevAddr[2] = (uint8_t) (config_words >> 8);
  	RDevAddr[3] = (uint8_t) (config_words);


  memcpy1(pRDevAddr, RDevAddr, sizeof(RDevAddr));
  /* USER CODE END E2P_Read_Appeui_2 */
}

void E2P_LORA_Write_DevAddr(uint8_t *pWDevAddr)
{
	/* USER CODE BEGIN E2P_Write_Appeui_1 */
  lora_u32 config_words;
  uint8_t WDevAddr[4];

  memset1(WDevAddr, 0, sizeof(WDevAddr));
  memcpy1(WDevAddr, pWDevAddr, sizeof(WDevAddr));


  	config_words = (lora_u32) (WDevAddr[3] + (WDevAddr[2] << 8) + (WDevAddr[1] << 16) + (WDevAddr[0] << 24));
  /* USER CODE END E2P_Write_Appeui_1 */

  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_DEVADDR, config_words);

  HAL_FLASH_Lock();

  /* USER CODE BEGIN E2P_Write_Appeui_2 */

  /* USER CODE END E2P_Write_Appeui_2 */
}
void E2P_LORA_Read_Appeui(uint8_t *pRappEui)
{
  /* USER CODE BEGIN E2P_Read_Appeui_1 */
  lora_u32 config_words[2];
  uint8_t RappEui[8];
  
  memset1(RappEui, 0, sizeof(RappEui));
  /* USER CODE END E2P_Read_Appeui_1 */

  E2P_LORA_Read(EE_LORA_WORD0_APPEUI_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_APPEUI_ID, (uint32_t *) &config_words[1]);
  
  /* USER CODE BEGIN E2P_Read_Appeui_2 */	
  for(int i = 0; i < 2; i++)
  {
  	RappEui[i*4+0] = (uint8_t) (config_words[i] >> 24);
  	RappEui[i*4+1] = (uint8_t) (config_words[i] >> 16);
  	RappEui[i*4+2] = (uint8_t) (config_words[i] >> 8);
  	RappEui[i*4+3] = (uint8_t) (config_words[i]);
  }

  memcpy1(pRappEui, RappEui, sizeof(RappEui));
  /* USER CODE END E2P_Read_Appeui_2 */

}

void E2P_LORA_Write_Appeui(uint8_t *pWappEui)
{
  /* USER CODE BEGIN E2P_Write_Appeui_1 */
  lora_u32 config_words[2];
  uint8_t WappEui[8];

  memset1(WappEui, 0, sizeof(WappEui));
  memcpy1(WappEui, pWappEui, sizeof(WappEui));
  
  for(int i = 0; i < 2; i++)
  	config_words[i] = (lora_u32) (WappEui[i*4+3] + (WappEui[i*4+2] << 8) + (WappEui[i*4+1] << 16) + (WappEui[i*4+0] << 24));
  /* USER CODE END E2P_Write_Appeui_1 */
  
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_APPEUI_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_APPEUI_ID, config_words[1]);

  HAL_FLASH_Lock();
  
  /* USER CODE BEGIN E2P_Write_Appeui_2 */

  /* USER CODE END E2P_Write_Appeui_2 */
}

void E2P_LORA_Read_Appkey(uint8_t *pRappKey)
{
  /* USER CODE BEGIN E2P_Read_Appkey_1 */
  lora_u32 config_words[4];
  uint8_t RappKey[16];
  
  memset1(RappKey, 0, sizeof(RappKey));
  /* USER CODE END E2P_Read_Appkey_1 */

  E2P_LORA_Read(EE_LORA_WORD0_APPKEY_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_APPKEY_ID, (uint32_t *) &config_words[1]);
  E2P_LORA_Read(EE_LORA_WORD2_APPKEY_ID, (uint32_t *) &config_words[2]);
  E2P_LORA_Read(EE_LORA_WORD3_APPKEY_ID, (uint32_t *) &config_words[3]);
  
  /* USER CODE BEGIN E2P_Read_Appkey_2 */
  for(int i = 0; i < 4; i++)
  {
  	RappKey[i*4+0] = (uint8_t) (config_words[i] >> 24);
  	RappKey[i*4+1] = (uint8_t) (config_words[i] >> 16);
  	RappKey[i*4+2] = (uint8_t) (config_words[i] >> 8);
  	RappKey[i*4+3] = (uint8_t) (config_words[i]);
  }
	
  memcpy1(pRappKey, RappKey, sizeof(RappKey));	
  /* USER CODE END E2P_Read_Appkey_2 */

}

void E2P_LORA_Write_Appkey(uint8_t *pWappKey)
{
  /* USER CODE BEGIN E2P_Write_Appkey_1 */
  lora_u32 config_words[4];
  uint8_t WappKey[16];

  memset1(WappKey, 0, sizeof(WappKey));
  memcpy1(WappKey, pWappKey, sizeof(WappKey));
  
  for(int i = 0; i < 4; i++)
  	config_words[i] = (lora_u32) (WappKey[i*4+3] + (WappKey[i*4+2] << 8) + (WappKey[i*4+1] << 16) + (WappKey[i*4+0] << 24));
  /* USER CODE END E2P_Write_Appkey_1 */
  
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_APPKEY_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_APPKEY_ID, config_words[1]);
  E2P_LORA_Write(EE_LORA_WORD2_APPKEY_ID, config_words[2]);
  E2P_LORA_Write(EE_LORA_WORD3_APPKEY_ID, config_words[3]);

  HAL_FLASH_Lock();
  
  /* USER CODE BEGIN E2P_Write_Appkey_2 */
  
  /* USER CODE END E2P_Write_Appkey_2 */
}


void E2P_LORA_Read_Nwkkey(uint8_t *pRnwkKey)
{
  /* USER CODE BEGIN E2P_Read_Nwkkey_1 */
  lora_u32 config_words[4];
  uint8_t RnwkKey[16];
  
  memset1(RnwkKey, 0, sizeof(RnwkKey));
  /* USER CODE END E2P_Read_Nwkkey_1 */
  
  E2P_LORA_Read(EE_LORA_WORD0_NWKKEY_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_NWKKEY_ID, (uint32_t *) &config_words[1]);
  E2P_LORA_Read(EE_LORA_WORD2_NWKKEY_ID, (uint32_t *) &config_words[2]);
  E2P_LORA_Read(EE_LORA_WORD3_NWKKEY_ID, (uint32_t *) &config_words[3]);

  
  /* USER CODE BEGIN E2P_Read_Nwkkey_2 */
  for(int i = 0; i < 4; i++)
  {
  	RnwkKey[i*4+0] = (uint8_t) (config_words[i] >> 24);
  	RnwkKey[i*4+1] = (uint8_t) (config_words[i] >> 16);
  	RnwkKey[i*4+2] = (uint8_t) (config_words[i] >> 8);
  	RnwkKey[i*4+3] = (uint8_t) (config_words[i]);
  }
  
  memcpy1(pRnwkKey, RnwkKey, sizeof(RnwkKey));
  /* USER CODE END E2P_Read_Nwkkey_2 */
}

void E2P_LORA_Write_Nwkkey(uint8_t *pWnwkKey)
{
  /* USER CODE BEGIN E2P_Write_Nwkkey_1 */
  lora_u32 config_words[4];
  uint8_t WnwkKey[16];

  memset1(WnwkKey, 0, sizeof(WnwkKey));
  memcpy1(WnwkKey, pWnwkKey, sizeof(WnwkKey));
  
  for(int i = 0; i < 4; i++)
  	config_words[i] = (lora_u32) (WnwkKey[i*4+3] + (WnwkKey[i*4+2] << 8) + (WnwkKey[i*4+1] << 16) + (WnwkKey[i*4+0] << 24));
  /* USER CODE END E2P_Write_Nwkkey_1 */
  
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_NWKKEY_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_NWKKEY_ID, config_words[1]);
  E2P_LORA_Write(EE_LORA_WORD2_NWKKEY_ID, config_words[2]);
  E2P_LORA_Write(EE_LORA_WORD3_NWKKEY_ID, config_words[3]);

  HAL_FLASH_Lock();
  
  /* USER CODE BEGIN E2P_Write_Nwkkey_2 */

  /* USER CODE END E2P_Write_Nwkkey_2 */
}

void E2P_LORA_Read_App_S_key(uint8_t *pRappSKey)
{
  /* USER CODE BEGIN E2P_Read_App_S_key_1 */
  lora_u32 config_words[4];
  uint8_t RappSKey[16];
  
  memset1(RappSKey, 0, sizeof(RappSKey));
  /* USER CODE END E2P_Read_App_S_key_1 */
  
  E2P_LORA_Read(EE_LORA_WORD0_APPSKEY_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_APPSKEY_ID, (uint32_t *) &config_words[1]);
  E2P_LORA_Read(EE_LORA_WORD2_APPSKEY_ID, (uint32_t *) &config_words[2]);
  E2P_LORA_Read(EE_LORA_WORD3_APPSKEY_ID, (uint32_t *) &config_words[3]);

  /* USER CODE BEGIN E2P_Read_App_S_key_2 */  
  for(int i = 0; i < 4; i++)
  {
  	RappSKey[i*4+0] = (uint8_t) (config_words[i] >> 24);
  	RappSKey[i*4+1] = (uint8_t) (config_words[i] >> 16);
  	RappSKey[i*4+2] = (uint8_t) (config_words[i] >> 8);
  	RappSKey[i*4+3] = (uint8_t) (config_words[i]);
  }
  
  memcpy1(pRappSKey, RappSKey, sizeof(RappSKey));
  /* USER CODE END E2P_Read_App_S_key_2 */
  
}

void E2P_LORA_Write_App_S_key(uint8_t *pWappSKey)
{
  /* USER CODE BEGIN E2P_Write_App_S_key_1 */
  lora_u32 config_words[4];
  uint8_t WappSKey[16];

  memset1(WappSKey, 0, sizeof(WappSKey));
  memcpy1(WappSKey, pWappSKey, sizeof(WappSKey));
  
  for(int i = 0; i < 4; i++)
  	config_words[i] = (lora_u32) (WappSKey[i*4+3] + (WappSKey[i*4+2] << 8) + (WappSKey[i*4+1] << 16) + (WappSKey[i*4+0] << 24));
  /* USER CODE END E2P_Write_App_S_key_1 */
  
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_APPSKEY_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_APPSKEY_ID, config_words[1]);
  E2P_LORA_Write(EE_LORA_WORD2_APPSKEY_ID, config_words[2]);
  E2P_LORA_Write(EE_LORA_WORD3_APPSKEY_ID, config_words[3]);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_App_S_key_2 */

  /* USER CODE END E2P_Write_App_S_key_2 */
}


void E2P_LORA_Read_Nwk_S_key(uint8_t *pRnwkSKey)
{
  /* USER CODE BEGIN E2P_Read_Nwk_S_key_1 */
  lora_u32 config_words[4];
  uint8_t RnwkSKey[16];
  
  memset1(RnwkSKey, 0, sizeof(RnwkSKey));
  /* USER CODE END E2P_Read_Nwk_S_key_1 */
  
  E2P_LORA_Read(EE_LORA_WORD0_NWKSKEY_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_NWKSKEY_ID, (uint32_t *) &config_words[1]);
  E2P_LORA_Read(EE_LORA_WORD2_NWKSKEY_ID, (uint32_t *) &config_words[2]);
  E2P_LORA_Read(EE_LORA_WORD3_NWKSKEY_ID, (uint32_t *) &config_words[3]);

  
  /* USER CODE BEGIN E2P_Read_Nwk_S_key_2 */
  for(int i = 0; i < 4; i++)
  {
  	RnwkSKey[i*4+0] = (uint8_t) (config_words[i] >> 24);
  	RnwkSKey[i*4+1] = (uint8_t) (config_words[i] >> 16);
  	RnwkSKey[i*4+2] = (uint8_t) (config_words[i] >> 8);
  	RnwkSKey[i*4+3] = (uint8_t) (config_words[i]);
  }
  
  memcpy1(pRnwkSKey, RnwkSKey, sizeof(RnwkSKey));
  /* USER CODE END E2P_Read_Nwk_S_key_2 */
  
}

void E2P_LORA_Write_Nwk_S_key(uint8_t *pWnwkSKey)
{
  /* USER CODE BEGIN E2P_Write_Nwk_S_key_1 */
  lora_u32 config_words[4];
  uint8_t WnwkSKey[16];

  memset1(WnwkSKey, 0, sizeof(WnwkSKey));
  memcpy1(WnwkSKey, pWnwkSKey, sizeof(WnwkSKey));
  
  for(int i = 0; i < 4; i++)
  	config_words[i] = (lora_u32) (WnwkSKey[i*4+3] + (WnwkSKey[i*4+2] << 8) + (WnwkSKey[i*4+1] << 16) + (WnwkSKey[i*4+0] << 24));
  /* USER CODE END E2P_Write_Nwk_S_key_1 */
  
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_NWKSKEY_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_NWKSKEY_ID, config_words[1]);
  E2P_LORA_Write(EE_LORA_WORD2_NWKSKEY_ID, config_words[2]);
  E2P_LORA_Write(EE_LORA_WORD3_NWKSKEY_ID, config_words[3]);

  HAL_FLASH_Lock();
  
  /* USER CODE BEGIN E2P_Write_Nwk_S_key_2 */

  /* USER CODE END E2P_Write_Nwk_S_key_2 */
}


/* Private Functions Definition -----------------------------------------------*/
void E2P_LORA_Write(e_EE_LORA_ID addr, uint32_t data)
{
  /* USER CODE BEGIN E2P_Write_1 */

  /* USER CODE END E2P_Write_1 */
  if (EE_LoRa_Write(EE_BANK_0, (uint16_t) addr, data) == EE_CLEAN_NEEDED)
  {
    EE_LoRa_Clean(EE_BANK_0, EE_CLEAN_MODE_POLLING);
  }
  /* USER CODE BEGIN E2P_Write_2 */

  /* USER CODE END E2P_Write_2 */
}

void E2P_LORA_Read(e_EE_LORA_ID addr, uint32_t *data)
{
  /* USER CODE BEGIN E2P_Read_1 */

  /* USER CODE END E2P_Read_1 */
  EE_LoRa_Read(EE_BANK_0, (uint16_t) addr, data);
  /* USER CODE BEGIN E2P_Read_2 */

  /* USER CODE END E2P_Read_2 */
}

void E2P_LORA_BaudRate_Write(uint32_t baudrate)
{
	HAL_FLASH_Unlock();
	E2P_LORA_Write(EE_LORA_BAUDRATE,baudrate);
	HAL_FLASH_Lock();
}

void E2P_LORA_BaudRate_Read(uint32_t *baudrate)
{
	EE_LoRa_Read(EE_BANK_0,EE_LORA_BAUDRATE,baudrate);
}

/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
