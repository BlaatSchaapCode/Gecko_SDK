/*
 *  Common functions for AES based algorithms for the AES hw module.
 *
 *  Copyright (C) 2016 Silicon Labs, http://www.silabs.com
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#include "em_device.h"

#if defined(AES_COUNT) && (AES_COUNT > 0)

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "aesdrv_internal.h"
#include "slcl_device_aes.h"
#include "slcl_device.h"
#include "sl_crypto.h"
#include "em_assert.h"
#include <string.h>

/*******************************************************************************
 ********************************   STATICS   **********************************
 ******************************************************************************/

#if !defined( MBEDTLS_DEVICE_INIT_INTERNAL_DISABLE )
/* Device structures for internal initialization in order for backwards
   compatibility. Use MBEDTLS_DEVICE_INIT_INTERNAL_DISABLE to disable
   the internal device initialization. Internal initialization consumes
   more RAM because the device structures are instantiated statically here,
   inside the mbedTLS library. */
static mbedtls_device_context _mbedtls_device_ctx[MBEDTLS_DEVICE_COUNT];
#endif

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/*
 *   Initializes an AESDRV context structure.
 *   Please refer to aesdrv.h for detailed description.
 */
int AESDRV_Init(AESDRV_Context_t* pAesdrvContext)
{
  /* Clear the driver context. */
  memset(pAesdrvContext, 0, sizeof(AESDRV_Context_t));
  
#if defined(MBEDTLS_CRYPTO_DEVICE_PREEMPTION)
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;
  SLDP_ContextInit( &slcl_ctx->sldp_ctx );
  SLDP_ContextDeviceSpecificSet( &slcl_ctx->sldp_ctx, &slcl_ctx->aes_ctx );
#endif
  
  return 0;
}

/*
 *   DeInitializes an AESDRV context structure.
 *   Please refer to aesdrv.h for detailed description.
 */
int AESDRV_DeInit(AESDRV_Context_t* pAesdrvContext)
{
  /* Clear the driver context. */
  memset(pAesdrvContext, 0, sizeof(AESDRV_Context_t));
  return 0;
}

/*
 *   Set the AES device instance.
 *   Please refer to aesdrv.h for detailed description.
 */
int AESDRV_SetDeviceInstance(AESDRV_Context_t*  pAesdrvContext,
                             unsigned int       devno)
{
  (void) pAesdrvContext;
  
  if (devno >= AES_COUNT)
  {
    return MBEDTLS_ECODE_AESDRV_INVALID_PARAM;
  }
  else
  {
#if !defined( MBEDTLS_DEVICE_INIT_INTERNAL_DISABLE )
    /* Initialize the mbedtls device structures internally for backwards
       compatibility. Use MBEDTLS_DEVICE_INIT_INTERNAL_DISABLE to disable
       the internal device initialization. Internal initialization consumes
       more RAM because the device structures are instantiated statically
       inside the mbedTLS library. */
    if (p_mbedtls_device_context[devno] == 0)
    {
      mbedtls_device_init(&_mbedtls_device_ctx[devno]);
      mbedtls_device_set_instance(&_mbedtls_device_ctx[devno], devno);
    }
#endif
    
    /* Check that the specified device is initialized. */
    if (p_mbedtls_device_context[devno] == 0)
        return( MBEDTLS_ERR_DEVICE_NOT_INITIALIZED );
    
#if defined(MBEDTLS_CRYPTO_DEVICE_PREEMPTION)
    slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;
    SLDP_ContextDeviceSet( &slcl_ctx->sldp_ctx,
                           &p_mbedtls_device_context[devno]->sldp_dev_ctx );
#endif
    
    return 0;
  }
}

/*
 *   Setup CRYPTO I/O mode.
 *   Please refer to aesdrv.h for detailed description.
 */
int AESDRV_SetIoMode
(
 AESDRV_Context_t*        pAesdrvContext,
 AESDRV_IoMode_t          ioMode,
 AESDRV_IoModeSpecific_t* ioModeSpecific
 )
{
  (void) pAesdrvContext;  /* Not supported for AES module. */
  (void) ioModeSpecific;  /* Not supported for AES module. */
  if (ioMode == aesdrvIoModeCore)
  {
    return 0;
  }
  else
  {
    return MBEDTLS_ECODE_AESDRV_NOT_SUPPORTED;
  }
}

#endif /* #if defined(AES_COUNT) && (AES_COUNT > 0) */
