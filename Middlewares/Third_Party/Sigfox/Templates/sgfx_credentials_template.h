/**
  ******************************************************************************
  * @file    sgfx_credentials_template.h
  * @author  MCD Application Team
  * @brief   interface to key manager and encryption algorithm
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
#ifndef __CREDENTIALS_TEMPLATE_H__
#define __CREDENTIALS_TEMPLATE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define AES_KEY_LEN 16 /* bytes */
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#include <stdint.h>
#include "sigfox_types.h"

/**
  * @brief get the cmac library version
  * @retval return a string containing the library version
  */
const char *CREDENTIALS_get_version(void);

/**
  * @brief get the loaded dev_id
  * @param[out] return the dev_id in the pointer
  */
void CREDENTIALS_get_dev_id(uint8_t *dev_id);

/**
  * @brief get the loaded pac
  * @param[out] return the pac in the pointer
  */
void CREDENTIALS_get_initial_pac(uint8_t *pac);

/**
  * @brief get the payload_encryption_flag
  * @retval  the payload_encryption_flag
  */
sfx_bool CREDENTIALS_get_payload_encryption_flag(void);

/**
  * @brief set the payload_encryption_flag
  * @param[in] enable flag. 0: disable, 1: enable
  * @retval  none
  */
void CREDENTIALS_set_payload_encryption_flag(uint8_t enable);

/**
  * @brief encrypts the data_to_encrypt with aes secrete Key
  * @param[out] the encrypted data
  * @param[in] the data_to_encrypt
  * @param[in] the number of aes blocks
  */
sfx_error_t CREDENTIALS_aes_128_cbc_encrypt(uint8_t *encrypted_data, uint8_t *data_to_encrypt, uint8_t block_len);

/**
  * @brief encrypts the data_to_encrypt with aes session Key
  * @param[out] the encrypted data
  * @param[in] the data_to_encrypt
  * @param[in] the number of aes blocks
  */
sfx_error_t CREDENTIALS_aes_128_cbc_encrypt_with_session_key(uint8_t *encrypted_data, uint8_t *data_to_encrypt,
                                                             uint8_t block_len);

/**
  * @brief wraps the session Key
  * @param[in] the arguments used to generate the session Key
  * @param[in] the number of aes blocks
  */
sfx_error_t CREDENTIALS_wrap_session_key(uint8_t *data, uint8_t blocks);

#ifdef __cplusplus
}
#endif

#endif /* __SGFX_CREDENTIALS_TEMPLATE_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

