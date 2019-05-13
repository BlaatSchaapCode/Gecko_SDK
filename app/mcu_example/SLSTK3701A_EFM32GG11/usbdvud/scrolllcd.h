/***************************************************************************//**
 * @file scrolllcd.h
 * @brief Scroll functions for LCD display.
 * @version 5.6.1
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef SILICON_LABS_SCROLLLCD_H
#define SILICON_LABS_SCROLLLCD_H

#include "display.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  scrollOff,
  scrollUp,
  scrollDown,
  scrollLeft
} scrollDirection_t;

void scrollLcd(DISPLAY_Device_t *displayDevice,
               scrollDirection_t direction,
               const char *pOldImg,
               const char *pNewImg);

#ifdef __cplusplus
}
#endif

#endif /* SILICON_LABS_SCROLLLCD_H */
