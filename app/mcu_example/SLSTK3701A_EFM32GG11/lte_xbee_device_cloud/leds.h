/***************************************************************************//**
 * # License
 * <b>Copyright 2018 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

#define PWM_STEPS     255
#define RGB_LED_COUNT 1

#ifdef __cplusplus
extern "C" {
#endif

void setupRgbLed1(void);
void setLed1(uint32_t red, uint32_t green, uint32_t blue);

#ifdef __cplusplus
}
#endif

#endif /* LEDS_H */
