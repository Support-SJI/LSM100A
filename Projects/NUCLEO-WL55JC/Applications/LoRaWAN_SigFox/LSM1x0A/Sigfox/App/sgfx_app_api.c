/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sgfx_app_api.c
  * @author  MCD Application Team
  * @brief   provides code for the application of the sigfox Middleware
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

#include "st_sigfox_api.h"
#include "sgfx_app_api.h"
#include "sgfx_app_version.h"
#include "stm32_seq.h"
#include "stm32_timer.h"
#include "radio.h"
#include "sys_conf.h"
#include "sys_app.h"
#include "stm32_lpm.h"
#include "stm32_seq.h"
#include "utilities_def.h"
#include "radio_board_if.h"
#include "sgfx_command.h"
#include "rf_api.h"
#include "mcu_api.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/*!
 * Defines the application data transmission duty cycle. 10s, value in [ms].
 */
#define APP_TX_DUTYCYCLE                            100000
#define APP_RX_DUTYCYCLE                            10000


#define SIGFOX_TX                1
#define SIGFOX_RX                2

//#define SIGFOX_MODE              SIGFOX_TX
#define SIGFOX_MODE              SIGFOX_RX

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */
extern int g_iRxTestInterrupt;

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

/**
  * @brief Timer to handle the application Tx
  */
static UTIL_TIMER_Object_t SigfoxTxTimer;
static UTIL_TIMER_Object_t SigfoxRxTimer;


/* USER CODE BEGIN PFP */
static void SendSigfox(void);
static void SendLocalSigfox(void);
static void ReceptionSigfox(void);

static void OnSigfoxAPITxTimerEvent(void *context);
static void OnSigfoxAPIRxTimerEvent(void *context);


/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/

void Sigfox_API_Init(void)
{
  int sigfox_mode = SIGFOX_MODE;
  if(sigfox_mode == SIGFOX_TX)
  {
    /* TX */
    UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_Pb), UTIL_SEQ_RFU, SendSigfox);

	// Only local test
    //UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_Pb), UTIL_SEQ_RFU, SendLocalSigfox);

    /* send every time timer elapses */
    UTIL_TIMER_Create(&SigfoxTxTimer,  0xFFFFFFFFU, UTIL_TIMER_ONESHOT, OnSigfoxAPITxTimerEvent, NULL);
    UTIL_TIMER_SetPeriod(&SigfoxTxTimer,  APP_TX_DUTYCYCLE);
    UTIL_TIMER_Start(&SigfoxTxTimer);
  }
  else if(sigfox_mode == SIGFOX_RX)
  {
    /* RX */
    UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_Pb), UTIL_SEQ_RFU, ReceptionSigfox);
	
    /* send every time timer elapses */
    UTIL_TIMER_Create(&SigfoxRxTimer,  0xFFFFFFFFU, UTIL_TIMER_ONESHOT, OnSigfoxAPIRxTimerEvent, NULL);
    UTIL_TIMER_SetPeriod(&SigfoxRxTimer,  APP_RX_DUTYCYCLE);
    UTIL_TIMER_Start(&SigfoxRxTimer);
  }

}

/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* USER CODE BEGIN PrFD */

/* TX */
static void SendSigfox(void)
{
  uint8_t ul_msg[12] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11};
  uint8_t dl_msg[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint32_t  ul_size = 0;
  int16_t temperature = SYS_GetTemperatureLevel() >> 8;
  uint16_t batteryLevel = SYS_GetBatteryLevel();
  uint32_t nbTxRepeatFlag = 1;


  APP_LOG(TS_ON, VLEVEL_L, "sending temperature=%d degC,  battery=%d mV", temperature, batteryLevel);

  ul_msg[ul_size++] = (uint8_t)((batteryLevel * 100) / 3300);
  ul_msg[ul_size++] = (temperature >> 8) & 0xFF;
  ul_msg[ul_size++] = temperature & 0xFF;

  SIGFOX_API_send_frame(ul_msg, ul_size, dl_msg, nbTxRepeatFlag, SFX_FALSE);

  APP_LOG(TS_OFF, VLEVEL_L, " done\n\r");
}

static void OnSigfoxAPITxTimerEvent(void *context)
{
  /* USER CODE BEGIN OnTxTimerEvent_1 */

  /* USER CODE END OnTxTimerEvent_1 */
  UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_Pb), CFG_SEQ_Prio_0);

  /*Wait for next tx slot*/
  UTIL_TIMER_Start(&SigfoxTxTimer);
  /* USER CODE BEGIN OnTxTimerEvent_2 */

  /* USER CODE END OnTxTimerEvent_2 */
}

static void SendLocalSigfox(void)
{
  uint8_t data_buffer[12] = {0x84, 0x32, 0x68, 0xC5, 0xBA, 0x53, 0xAE, 0x79, 0xE7, 0xF6, 0xDD, 0x9B};
  uint32_t freq = 869525000;
  uint32_t count = 10;
  uint32_t dataRate = 600;
  int j = 0;
  
  APP_LOG(TS_OFF, VLEVEL_L, "FREP[%u] dataRate[%u]\r\n", freq, dataRate);

  for(j=0;j<count;j++)
  {
    RF_Tx_Local_loop(freq, dataRate, data_buffer, sizeof(data_buffer));
  }

  APP_LOG(TS_OFF, VLEVEL_L, " done\n\r");
}


/* RX */
static void ReceptionSigfox(void)
{
  sfx_u8 frame[32];
  sfx_s16 rssi;
  sfx_s32 receivedCnt = 0;
  sfx_rx_state_enum_t state;
  uint32_t freq = 869525000;
  uint32_t timeout = 0;
  sfx_u8 result = 0;

  g_iRxTestInterrupt = 0;

  APP_LOG(TS_ON, VLEVEL_L, "\r\n==== ReceptionSigfox ====\r\n");

  RF_API_init(SFX_RF_MODE_RX);
  RF_API_change_frequency(freq);

  while(g_iRxTestInterrupt==0)
  {
	memset(frame,0,sizeof(frame));

	if(timeout > 0)
	{
		MCU_API_timer_start(timeout);
	}
	result = RF_API_wait_frame(frame,&rssi,&state);

	if(DL_PASSED == state)
	{
		receivedCnt++;
		APP_LOG(TS_ON, VLEVEL_L, "{#%d RSSI=%d TEST PASSED!}\r\n",receivedCnt,rssi);
	}
	else
	{
		APP_LOG(TS_ON, VLEVEL_L, "RF_API_wait_frame : result[%x] state[%d] - TIMEOUT!!\r\n\r\n", result, state);
		break;
	}
  }

  RF_API_stop();

  APP_LOG(TS_ON, VLEVEL_L, "\r\n==== ReceptionSigfox Finish ====\r\n");

  g_iRxTestInterrupt = -1;

}


static void OnSigfoxAPIRxTimerEvent(void *context)
{
  /* USER CODE BEGIN OnTxTimerEvent_1 */

  /* USER CODE END OnTxTimerEvent_1 */
  UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_Pb), CFG_SEQ_Prio_0);

  /*Wait for next tx slot*/
  UTIL_TIMER_Start(&SigfoxRxTimer);
  /* USER CODE BEGIN OnTxTimerEvent_2 */

  /* USER CODE END OnTxTimerEvent_2 */
}





/* USER CODE END PrFD */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
