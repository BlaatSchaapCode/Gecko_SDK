/*
 *  AES block cipher algorithms implementation using AES hw module
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
/*
 * This is an implementation of block cipher function using the AES hw
 * module for acceleration.
 *
 * The module implements following interfaces:
 *
 * AESDRV_CBCx()
 * AESDRV_CFBx()
 * AESDRV_CTRx()
 * AESDRV_DecryptKey128()
 * AESDRV_DecryptKey256()
 * AESDRV_ECBx()
 * AESDRV_OFBx()
 *
 * Functions are mostly wrappers of emlib AES (em_aes.h) since block cipher
 * functionality is provided by emlib.
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
#include "em_aes.h"
#include <string.h>

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/*
 *  Generate 128 bit decryption key from 128 bit encryption key. The decryption
 *  key is used for some cipher modes when decrypting.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_DecryptKey128(AESDRV_Context_t* pAesdrvContext,
                         uint8_t*          out,
                         const uint8_t*    in)
{
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  /* Try to open and return immediately if error */
  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;

  /* Generate decryption key */
  AES_DecryptKey128( out, in );
    
  ret = slcl_device_critical_exit( slcl_ctx );

 exit:
  
  status = slcl_device_close( slcl_ctx );
  
  return ret ? ret : status;
}

/*
 *  Generate 256 bit decryption key from 256 bit encryption key. The decryption
 *  key is used for some cipher modes when decrypting.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_DecryptKey256(AESDRV_Context_t* pAesdrvContext,
                         uint8_t*          out,
                         const uint8_t *   in)
{
#if defined( AES_CTRL_AES256 )
  
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;

  /* Generate decryption key */
  AES_DecryptKey256( out, in);
    
  ret = slcl_device_critical_exit( slcl_ctx );
    
 exit:
  
  status = slcl_device_close( slcl_ctx );

  return ret ? ret : status;
  
#else
  
  (void) pAesdrvContext;
  (void) out; (void) in;
  return MBEDTLS_ECODE_AESDRV_NOT_SUPPORTED;
  
#endif
}

/*
 * Cipher-block chaining (CBC) cipher mode encryption/decryption, 128 bit key.
 * Please refer to aesdrv.h for detailed description.
 */
int AESDRV_CBC128(AESDRV_Context_t* pAesdrvContext,
                  uint8_t*          out,
                  const uint8_t*    in,
                  unsigned int      len,
                  const uint8_t*    key,
                  uint8_t*          iv,
                  bool              encrypt
                  )
{
  uint8_t tmpIv[16];
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  if ( false == encrypt )
  {
    if ( len>=16 )
      memcpy( tmpIv, &in[len-16], 16 );
  }
  
  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;

  /* Execute AES-CBC operation */
  AES_CBC128( out, in, len, key, iv, encrypt );
    
  if ( len >= 16 )
  {
    if ( encrypt )
      memcpy( iv, &out[len-16], 16 );
    else
      memcpy( iv, tmpIv, 16 );
  }
  
  ret = slcl_device_critical_exit( slcl_ctx );
    
 exit:
  
  status = slcl_device_close( slcl_ctx );

  return ret ? ret : status;
}

 /*
  * Cipher-block chaining (CBC) cipher mode encryption/decryption, 256 bit key.
  * Please refer to aesdrv.h for detailed description.
  */
int AESDRV_CBC256(AESDRV_Context_t* pAesdrvContext,
                  uint8_t*          out,
                  const uint8_t*    in,
                  unsigned int      len,
                  const uint8_t*    key,
                  uint8_t*          iv,
                  bool              encrypt
                  )
{
#if defined( AES_CTRL_AES256 )
  
  uint8_t tmpIv[16];
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  if ( false == encrypt )
  {
    if ( len>=16 )
      memcpy( tmpIv, &in[len-16], 16 );
  }
  
  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;

  /* Execute AES-CBC operation */
  AES_CBC256( out, in, len, key, iv, encrypt );
    
  if ( len >= 16 )
  {
    if ( encrypt )
      memcpy( iv, &out[len-16], 16 );
    else
      memcpy( iv, tmpIv, 16 );
  }
  
  ret = slcl_device_critical_exit( slcl_ctx );
    
 exit:
  
  status = slcl_device_close( slcl_ctx );

  return ret ? ret : status;

#else

  (void) out; (void) in; (void) len; (void) key; (void) iv; (void) encrypt;
  return MBEDTLS_ECODE_AESDRV_NOT_SUPPORTED;
  
#endif
}

/*
 *  Cipher feedback (CFB) cipher mode encryption/decryption, 128 bit key.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_CFB128(AESDRV_Context_t* pAesdrvContext,
                  uint8_t*          out,
                  const uint8_t*    in,
                  unsigned int      len,
                  const uint8_t*    key,
                  uint8_t*          iv,
                  bool              encrypt
                  )
{
  uint8_t tmpIv[16];
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  if ( false == encrypt )
  {
    if ( len>=16 )
      memcpy( tmpIv, &in[len-16], 16 );
  }
  
  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;

  /* Execute AES-CFB operation */
  AES_CFB128( out, in, len, key, iv, encrypt );
    
  if ( len >= 16 )
  {
    if ( encrypt )
      memcpy( iv, &out[len-16], 16 );
    else
      memcpy( iv, tmpIv, 16 );
  }
  
  ret = slcl_device_critical_exit( slcl_ctx );
    
 exit:
  
  status = slcl_device_close( slcl_ctx );

  return ret ? ret : status;
}

/*
 *  Cipher feedback (CFB) cipher mode encryption/decryption, 256 bit key.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_CFB256(AESDRV_Context_t* pAesdrvContext,
                  uint8_t*          out,
                  const uint8_t*    in,
                  unsigned int      len,
                  const uint8_t*    key,
                  uint8_t*          iv,
                  bool              encrypt
                  )
{
#if defined( AES_CTRL_AES256 )
  uint8_t tmpIv[16];
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  if ( false == encrypt )
  {
    if ( len>=16 )
      memcpy( tmpIv, &in[len-16], 16 );
  }
  
  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;

  /* Execute AES-CFB operation */
  AES_CFB256( out, in, len, key, iv, encrypt );
    
  if ( len >= 16 )
  {
    if ( encrypt )
      memcpy( iv, &out[len-16], 16 );
    else
      memcpy( iv, tmpIv, 16 );
  }
  
  ret = slcl_device_critical_exit( slcl_ctx );
    
 exit:
  
  status = slcl_device_close( slcl_ctx );

  return ret ? ret : status;
  
#else
  
  (void) out; (void) in; (void) len; (void) key; (void) iv; (void) encrypt;
  return MBEDTLS_ECODE_AESDRV_NOT_SUPPORTED;
  
#endif
}

/*
 *  Counter (CTR) cipher mode encryption/decryption, 128 bit key.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_CTR128(AESDRV_Context_t*    pAesdrvContext,
                  uint8_t*             out,
                  const uint8_t*       in,
                  unsigned int         len,
                  const uint8_t*       key,
                  uint8_t*             ctr,
                  AESDRV_CtrCallback_t ctrCallback
                  )
{
  AESDRV_CtrCallback_t pCtrFunc;
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  if (ctrCallback)
  {
    pCtrFunc = ctrCallback;
  }
  else
  {
    pCtrFunc = AES_CTRUpdate32Bit;
  }
  
  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;
  
  /* Execute AES-CTR operation */
  AES_CTR128( out, in, len, key, ctr, pCtrFunc );
    
  ret = slcl_device_critical_exit( slcl_ctx );
  
 exit:
  
  status = slcl_device_close( slcl_ctx );

  return ret ? ret : status;
}

/*
 *  Counter (CTR) cipher mode encryption/decryption, 256 bit key.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_CTR256(AESDRV_Context_t*    pAesdrvContext,
                  uint8_t*             out,
                  const uint8_t*       in,
                  unsigned int         len,
                  const uint8_t*       key,
                  uint8_t*             ctr,
                  AESDRV_CtrCallback_t ctrCallback
                  )
{
#if defined( AES_CTRL_AES256 )
  AESDRV_CtrCallback_t pCtrFunc;
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  if (ctrCallback)
  {
    pCtrFunc = ctrCallback;
  }
  else
  {
    pCtrFunc = AES_CTRUpdate32Bit;
  }

  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;
  
  /* Execute AES-CTR operation */
  AES_CTR256( out, in, len, key, ctr, pCtrFunc );
    
  ret = slcl_device_critical_exit( slcl_ctx );
  
 exit:
  
  status = slcl_device_close( slcl_ctx );

  return ret ? ret : status;
  
#else
  
  (void) out; (void) in; (void) len; (void) key; (void) ctr; (void) ctrCallback;
  return MBEDTLS_ECODE_AESDRV_NOT_SUPPORTED;
  
#endif
}

/*
 *  Electronic Codebook (ECB) cipher mode encryption/decryption, 128 bit key.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_ECB128(AESDRV_Context_t* pAesdrvContext,
                  uint8_t*          out,
                  const uint8_t*    in,
                  unsigned int      len,
                  const uint8_t*    key,
                  bool              encrypt
                  )
{
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;
  int ret, status;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;
  
  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;
  
  /* Execute AES-ECB operation */
  AES_ECB128( out, in, len, key, encrypt );
  
  ret = slcl_device_critical_exit( slcl_ctx );
  
 exit:
  
  status = slcl_device_close( slcl_ctx );
  
  return ret ? ret : status;
}

/*
 *  Electronic Codebook (ECB) cipher mode encryption/decryption, 256 bit key.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_ECB256(AESDRV_Context_t* pAesdrvContext,
                  uint8_t*          out,
                  const uint8_t*    in,
                  unsigned int      len,
                  const uint8_t*    key,
                  bool              encrypt)
{
#if defined( AES_CTRL_AES256 )
  
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;
  
  /* Execute AES-ECB operation */
  AES_ECB256( out, in, len, key, encrypt);
    
  ret = slcl_device_critical_exit( slcl_ctx );
  
 exit:
  
  status = slcl_device_close( slcl_ctx );

  return ret ? ret : status;
  
#else
  
  (void) out; (void) in; (void) len; (void) key; (void) encrypt;
  return MBEDTLS_ECODE_AESDRV_NOT_SUPPORTED;
  
#endif
}

/*
 *  Output feedback (OFB) cipher mode encryption/decryption, 128 bit key.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_OFB128(AESDRV_Context_t* pAesdrvContext,
                  uint8_t*          out,
                  const uint8_t*    in,
                  unsigned int      len,
                  const uint8_t*    key,
                  uint8_t*          iv)
{
  int ret, status;
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;
  
  /* Execute AES-OFB operation */
  AES_OFB128( out, in, len, key, iv);
    
  ret = slcl_device_critical_exit( slcl_ctx );
  
 exit:
  
  status = slcl_device_close( slcl_ctx );
  
  return ret ? ret : status;
}

/*
 *  Output feedback (OFB) cipher mode encryption/decryption, 256 bit key.
 *  Please refer to aesdrv.h for detailed description.
 */
int AESDRV_OFB256(AESDRV_Context_t* pAesdrvContext,
                  uint8_t*          out,
                  const uint8_t*    in,
                  unsigned int      len,
                  const uint8_t*    key,
                  uint8_t*          iv)
{
#if defined( AES_CTRL_AES256 )
  
  slcl_context *slcl_ctx = &pAesdrvContext->slcl_ctx;
  int ret, status;

  ret = slcl_device_open( slcl_ctx );
  if (ret) return ret;

  ret = slcl_device_critical_enter( slcl_ctx );
  if (ret) goto exit;
  
  /* Execute AES-OFB operation */
  AES_OFB256( out, in, len, key, iv);
  
  ret = slcl_device_critical_exit( slcl_ctx );
  
 exit:
  
  status = slcl_device_close( slcl_ctx );

  return ret ? ret : status;
  
#else
  
  (void) pAesdrvContext; 
  (void) out; (void) in; (void) len; (void) key; (void) iv;
  return MBEDTLS_ECODE_AESDRV_NOT_SUPPORTED;
  
#endif
}

#endif /* #if defined(AES_COUNT) && (AES_COUNT > 0) */
