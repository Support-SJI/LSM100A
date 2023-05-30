/**
  ******************************************************************************
  * @file    se_nvm.c
  * @author  MCD Application Team
  * @brief   manages SE nvm datas
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

#include <stdint.h>
#include <string.h>
#include "sgfx_eeprom_if.h"
#include "st_sigfox_api.h"
#include "se_nvm.h"
#include "sgfx_credentials.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

sfx_u8 SE_NVM_get(sfx_u8 read_data[SFX_SE_NVMEM_BLOCK_SIZE])
{
  if (E2P_Read_SeNvm(read_data, SFX_SE_NVMEM_BLOCK_SIZE)!=E2P_OK)
 {
   return SE_ERR_API_SE_NVM;
 }

  return SFX_ERR_NONE;
}

sfx_u8 SE_NVM_set(sfx_u8 data_to_write[SFX_SE_NVMEM_BLOCK_SIZE])
{
 if (E2P_Write_SeNvm(data_to_write, SFX_SE_NVMEM_BLOCK_SIZE)!=E2P_OK)
 {
   return SE_ERR_API_SE_NVM;
 }

  return SFX_ERR_NONE;
}

sfx_key_type_t SE_NVM_get_key_type( void )
{
  return E2P_Read_KeyType();
}

void  SE_NVM_set_key_type( sfx_key_type_t keyType )
{
  E2P_Write_KeyType( keyType );
}

sfx_u8 SE_NVM_get_encrypt_flag( void )
{
  return E2P_Read_EncryptionFlag();
}

void  SE_NVM_set_encrypt_flag( sfx_u8 encryption_flag )
{
  E2P_Write_EncryptionFlag( encryption_flag );
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
