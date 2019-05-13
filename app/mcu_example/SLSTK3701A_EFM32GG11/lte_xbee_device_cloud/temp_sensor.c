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

#include "temp_sensor.h"
#include "em_acmp.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_i2c.h"

#include "i2cspm.h"
#include "si7013.h"

I2CSPM_Init_TypeDef i2cInit = I2CSPM_INIT_DEFAULT;

void initTempSensor(void)
{
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(gpioPortB, 3, gpioModePushPull, 1);
  I2CSPM_Init(&i2cInit);
}

int tempSensorReadHumTemp(uint32_t *rhData, int32_t *tempData)
{
  return Si7013_MeasureRHAndTemp(i2cInit.port, SI7021_ADDR, rhData, tempData);
}
