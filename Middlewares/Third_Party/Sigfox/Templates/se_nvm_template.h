/**
  ******************************************************************************
  * @file    se_nvm.h
  * @author  MCD Application Team
  * @brief   header to emulated SE nvm datas
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
#ifndef __SE_NVM_H__
#define __SE_NVM_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
   
typedef enum
{ 
  CREDENTIALS_KEY_PRIVATE= 0,    /* private key */ 
  CREDENTIALS_KEY_PUBLIC = 1,    /* public key  <i> 0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF</i>.*/ 
}sfx_key_type_t;

typedef enum
{
    SE_NVMEM_SEQNUM         = 0,                 /*!< Index of nv memory for PN */
    SE_NVMEM_RCSYNC_PERIOD  = 2,                 /*!< Index of nv memory for dedicated FH information */
    SE_NVMEM_ROLLOVER       = 4,
} se_nvmem_t;

/* Exported constants --------------------------------------------------------*/
#define SFX_SE_NVMEM_BLOCK_SIZE  5
#define SE_ERR_API_SE_NVM                 (sfx_u8)(0x4A) 
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/**
 * @brief This function reads data pointed by read_data to non
 * volatile memory
 *
 * @param [IN] sfx_u8 read_data[SFX_SE_NVMEM_BLOCK_SIZE] Pointer to the data bloc to write with the data stored in memory
 * @retval SFX_ERR_NONE:                      No error
 * @retval SE_ERR_API_SE_NVM:                 SE nvmem error
 */
sfx_u8 SE_NVM_get(sfx_u8 read_data[SFX_SE_NVMEM_BLOCK_SIZE]);

/**
 * @brief This function write data pointed by data_to_write to non
 * volatile memory
 *
 * @param [IN] sfx_u8 data_to_write[SFX_SE_NVMEM_BLOCK_SIZE] Pointer to the data bloc to write with the data stored in memory
 * @retval SFX_ERR_NONE:                      No error
 * @retval SE_ERR_API_SE_NVM:                 SE nvmem error
 */
sfx_u8 SE_NVM_set(sfx_u8 data_to_write[SFX_SE_NVMEM_BLOCK_SIZE]);

/**
 * @brief Get the active encryption payload flag
 * @retval encryption_flag 0:Off, 1:On
 */
sfx_u8 SE_NVM_get_encrypt_flag( void );

/**
 * @brief Set the active encryption payload flag
 * @param [IN]  encryption_flag 0:Off, 1:On
 */
void  SE_NVM_set_encrypt_flag( sfx_u8 encryption_flag );

/**
 * @brief Get the active encryption key
 * @retval  sfx_key_type_t key: public or private
 */
sfx_key_type_t SE_NVM_get_key_type( void );

/**
 * @brief Set the active encryption key
 * @param [IN]  sfx_key_type_t key: public or private
 */
void  SE_NVM_set_key_type( sfx_key_type_t keyType );
  
#ifdef __cplusplus
}
#endif

#endif /* __SE_NVM_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

