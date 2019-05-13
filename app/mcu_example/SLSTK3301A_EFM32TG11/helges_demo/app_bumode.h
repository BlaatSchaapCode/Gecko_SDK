/***************************************************************************//**
 * @file app_bumode.h
 * @brief Helper functions for using the backup power mode
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

#ifndef APP_BUMODE_H
#define APP_BUMODE_H

#define RET_BODCOUNT    0
#define RET_BODTIME     1
#define RET_CURAPP      2

#include "em_adc.h"

// Function prototypes
void buSetup(uint32_t * rtccResetVal,
             uint32_t * rtccResetTs,
             uint32_t * bodCnt,
             uint32_t * buTime,
             uint32_t * bodTime,
             uint8_t * currentApp);
void buADCInputSel(ADC_PosSel_TypeDef input);
void buMeasVdd(uint16_t * buVddVoltage, uint16_t * aVddVoltage);
void buPwrSwitch(bool chargeEn, bool disCharge);
void buSetCurApp(uint8_t app);

#endif /* APP_BUMODE_H */
