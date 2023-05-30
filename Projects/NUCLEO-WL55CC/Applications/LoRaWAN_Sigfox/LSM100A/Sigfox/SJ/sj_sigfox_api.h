/**
  ******************************************************************************
  * @file    sj_credentials.h
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 Seong Ji Industial Co., Ltd.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SJ_CREDENTIALS_H__
#define __SJ_CREDENTIALS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "app_sigfox.h"
#include "sigfox_types.h"
#include "sgfx_app.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

#ifdef FEATURE_SECURE_MODE
/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief      get the cmac library version
  * @return     string containing the library version
  */
const char *CREDENTIALS_get_version(void);

/**
  * @brief      get the loaded dev_id
  * @param[out] dev_id return the dev_id in the pointer
  */
void CREDENTIALS_get_dev_id(uint8_t *dev_id);

/**
  * @brief      get the loaded pac
  * @param[out] pac return the pac in the pointer
  */
void CREDENTIALS_get_initial_pac(uint8_t *pac);

/**
  * @brief      encrypts the data_to_encrypt with aes secrete Key
  * @param[out] encrypted_data the encrypted data
  * @param[in]  data_to_encrypt
  * @param[in]  block_len the number of aes blocks
  * @return     sfx_error_t status
  */
sfx_error_t CREDENTIALS_aes_128_cbc_encrypt(uint8_t *encrypted_data, uint8_t *data_to_encrypt, uint8_t block_len);

/**
  * @brief      encrypts the data_to_encrypt with aes session Key
  * @param[out] encrypted_data the encrypted data
  * @param[in]  data_to_encrypt
  * @param[in]  block_len the number of aes blocks
  * @return     sfx_error_t status
  */
sfx_error_t CREDENTIALS_aes_128_cbc_encrypt_with_session_key(uint8_t *encrypted_data, uint8_t *data_to_encrypt,
                                                             uint8_t block_len);

/**
  * @brief      wraps the session Key
  * @param[in]  data the arguments used to generate the session Key
  * @param[in]  blocks the number of aes blocks
  * @return     sfx_error_t status
  */
sfx_error_t CREDENTIALS_wrap_session_key(uint8_t *data, uint8_t blocks);



sfx_error_t Get_encrypted_sf_data(sfx_u8 *encrypted_data, sfx_u8 *data_to_encrypt, sfx_u8 data_len);

#endif /* FEATURE_SECURE_MODE */




#ifdef __cplusplus
}
#endif

#endif /* __SJ_CREDENTIALS_H__ */

