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

#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void initTempSensor(void);
int tempSensorReadHumTemp(uint32_t *rhData, int32_t *tempData);

#ifdef __cplusplus
}
#endif
#endif /* TEMPSENSOR_H */
