/***************************************************************************//**
 * @file app_sensor.h
 * @brief Helper functions for using LESENSE and I2C sensors
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

#ifndef APP_SENSOR_H
#define APP_SENSOR_H

/* DAC */
#define DAC_FREQ                500000
#define DAC_CHANNEL             0
#define DAC_DATA                800

/* LESENSE */
#define LCSENSE_CH              3
#define LCSENSE_SCAN_FREQ       20
#define LESENSE_MAX_CHANNELS    16
#define BUFFER_INDEX_LAST       15
#define LCSENSE_CH_PORT         gpioPortC
#define LCSENSE_CH_PIN          3

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "em_lesense.h"
#include "em_vdac.h"

// Function prototypes
void sensorSetup(void);
void sensorReadHumTemp(uint32_t *RhData, int32_t *TempData);
void sensorReadHallEffect(int16_t * HallField);

void setupVDAC(void);
void writeDataDAC(VDAC_TypeDef *dac, unsigned int value, unsigned int ch);

void setupACMP(void);

void setupLESENSE(void);
void lesenseCalibrateLC(uint8_t chIdx);

void setupTRNG(void);
void randomNumber(uint32_t *rngResult);
uint32_t littleToBigEndian(uint32_t input);

#endif /* APP_SENSOR_H */
