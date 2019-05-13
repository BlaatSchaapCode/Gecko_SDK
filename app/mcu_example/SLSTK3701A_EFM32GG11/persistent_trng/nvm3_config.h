/***************************************************************************//**
 * @file nvm3_config.h
 * @brief NVM3 configuration file.
 * @version 5.6.1
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/
#ifndef NVM3_CONFIG_H
#define NVM3_CONFIG_H

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup NVM3
 * @{
 ******************************************************************************/

#include <stdbool.h>

/*** Driver instrumentation options */
#define NVM3_TRACE_PORT_NONE               0               // Nothing is printed
#define NVM3_TRACE_PORT_SYSVIEW            1               // Only supported on the target
#define NVM3_TRACE_PORT_PRINTF             2               // Supported on all

#define NVM3_TRACE_PORT                    NVM3_TRACE_PORT_NONE

/*** Event level
     0 Critical: Trace only critical events
     1 Warning : Trace warning events and above
     2 Info    : Trace info events and above
 */
#define NVM3_TRACE_LEVEL_ERROR             0
#define NVM3_TRACE_LEVEL_WARNING           1
#define NVM3_TRACE_LEVEL_INFO              2
#define NVM3_TRACE_LEVEL_LOW               3

#define NVM3_TRACE_LEVEL                   NVM3_TRACE_LEVEL_WARNING

#define NVM3_ASSERT_ON_ERROR               false

/** @} (end addtogroup NVM3) */
/** @} (end addtogroup emdrv) */

#endif /* NVM3_CONFIG_H */
