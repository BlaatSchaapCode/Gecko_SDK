/***************************************************************************//**
 * @file app_rtcc.c
 * @brief Helper functions for timekeeping using the RTCC
 * @version 5.6.1
 *******************************************************************************
 * # License
 * <b>Copyright 2017 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include <stdint.h>

#include "em_rtcc.h"
#include "em_cmu.h"

#include "app_rtcc.h"

/**************************************************************************//**
 * @brief  Sets up the RTCC
 *****************************************************************************/
void setupRTCC(uint32_t resetVal)
{
  // RTCC configuration constant table.
  static RTCC_Init_TypeDef initRTCC = RTCC_INIT_DEFAULT;

  // Turn on RTCC clock so we can access its registers
  CMU_ClockEnable(cmuClock_RTCC, true);

  // Make sure the RTCC is disabled
  RTCC_Enable(false);

  // Keep the RTCC running in backup mode
  initRTCC.enaBackupModeSet = true;
  // Set the RTCC frequency to 1024 Hz
  initRTCC.presc = rtccCntPresc_32;
  // Do not start at init
  initRTCC.enable = false;
  // Initialize RTCC
  RTCC_Init(&initRTCC);

  // Clear status to enable storing backup mode entering timestamp
  RTCC->CMD = RTCC_CMD_CLRSTATUS;

  /* Set RTCC to the value it had at wakeup, which ensures continuity if recovering
   * from a backup event */
  RTCC_CounterSet(resetVal);

  // Finally enable RTCC
  RTCC_Enable(true);

  // Wait while sync is busy
  while (RTCC->SYNCBUSY) ;
}

/**************************************************************************//**
 * @brief Return the current system run time in milliseconds.
 *****************************************************************************/
uint32_t millis(void)
{
  return (RTCC_CounterGet() * 1000) / 1024;
}
