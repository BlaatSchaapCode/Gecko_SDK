/***************************************************************************//**
 * @file
 * @brief Voltage Comparator (VCMP) peripheral API
 * @version 5.8.1
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef EM_VCMP_H
#define EM_VCMP_H

#include "em_device.h"
#if defined(VCMP_COUNT) && (VCMP_COUNT > 0)

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup emlib
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup VCMP
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Warm-up Time in High Frequency Peripheral Clock cycles. */
typedef enum {
  /** 4 cycles */
  vcmpWarmTime4Cycles   = _VCMP_CTRL_WARMTIME_4CYCLES,
  /** 8 cycles */
  vcmpWarmTime8Cycles   = _VCMP_CTRL_WARMTIME_8CYCLES,
  /** 16 cycles */
  vcmpWarmTime16Cycles  = _VCMP_CTRL_WARMTIME_16CYCLES,
  /** 32 cycles */
  vcmpWarmTime32Cycles  = _VCMP_CTRL_WARMTIME_32CYCLES,
  /** 64 cycles */
  vcmpWarmTime64Cycles  = _VCMP_CTRL_WARMTIME_64CYCLES,
  /** 128 cycles */
  vcmpWarmTime128Cycles = _VCMP_CTRL_WARMTIME_128CYCLES,
  /** 256 cycles */
  vcmpWarmTime256Cycles = _VCMP_CTRL_WARMTIME_256CYCLES,
  /** 512 cycles */
  vcmpWarmTime512Cycles = _VCMP_CTRL_WARMTIME_512CYCLES
} VCMP_WarmTime_TypeDef;

/** Hysteresis configuration. */
typedef enum {
  /** Normal operation, no hysteresis. */
  vcmpHystNone,
  /** Digital output will not toggle until positive edge is at least
   *  20 mV above or below negative input voltage. */
  vcmpHyst20mV
} VCMP_Hysteresis_TypeDef;

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** VCMP Initialization structure. */
typedef struct {
  /** If set to true, reduces the bias current by half.  */
  bool                    halfBias;
  /** BIAS current configuration, depends on Half Bias setting above,
   *  see reference manual for more information. */
  int                     biasProg;
  /** Enable interrupt for falling edge. */
  bool                    irqFalling;
  /** Enable interrupt for rising edge. */
  bool                    irqRising;
  /** Warm-up time in clock cycles. */
  VCMP_WarmTime_TypeDef   warmup;
  /** Hysteresis configuration */
  VCMP_Hysteresis_TypeDef hyst;
  /** Output value when comparator is inactive, should be 0 or 1. */
  int                     inactive;
  /** Enable low power mode for VDD and band gap reference. */
  bool                    lowPowerRef;
  /** Trigger level, according to formula:
   *  VDD Trigger Level = 1.667V + 0.034V x triggerLevel */
  int                     triggerLevel;
  /** Enable VCMP after configuration. */
  bool                    enable;
} VCMP_Init_TypeDef;

/** Default VCMP initialization structure. */
#define VCMP_INIT_DEFAULT                                                    \
  {                                                                          \
    true,              /** Half Bias enabled. */                             \
    0x7,               /** Bias current 0.7 uA when half bias is enabled. */ \
    false,             /** Falling edge sense not enabled. */                \
    false,             /** Rising edge sense not enabled. */                 \
    vcmpWarmTime4Cycles, /** 4 clock cycles warm-up time. */                 \
    vcmpHystNone,      /** No hysteresis. */                                 \
    0,                 /** 0 in digital ouput when inactive. */              \
    true,              /** Do not use low power reference. */                \
    39,                /** Trigger level just below 3V. */                   \
    true,              /** Enable after initialization. */                   \
  }

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void VCMP_Init(const VCMP_Init_TypeDef *vcmpInit);
void VCMP_LowPowerRefSet(bool enable);
void VCMP_TriggerSet(int level);

/***************************************************************************//**
 * @brief
 *   Enable Voltage Comparator.
 ******************************************************************************/
__STATIC_INLINE void VCMP_Enable(void)
{
  VCMP->CTRL |= VCMP_CTRL_EN;
}

/***************************************************************************//**
 * @brief
 *   Disable Voltage Comparator.
 ******************************************************************************/
__STATIC_INLINE void VCMP_Disable(void)
{
  VCMP->CTRL &= ~VCMP_CTRL_EN;
}

/***************************************************************************//**
 * @brief
 *   Calculate voltage to trigger level.
 *
 * @note
 *   Soft float support is needed for this function to work.
 *
 * @param[in] v
 *   Voltage Level for trigger.
 ******************************************************************************/
__STATIC_INLINE uint32_t VCMP_VoltageToLevel(float v)
{
  return (uint32_t)((v - (float)1.667) / (float)0.034);
}

/***************************************************************************//**
 * @brief
 *   Returns true if Voltage Comparator indicated VDD < trigger level, else
 *   returns false.
 ******************************************************************************/
__STATIC_INLINE bool VCMP_VDDLower(void)
{
  if (VCMP->STATUS & VCMP_STATUS_VCMPOUT) {
    return false;
  } else {
    return true;
  }
}

/***************************************************************************//**
 * @brief
 *   Returns true if Voltage Comparator indicated VDD > trigger level, else
 *   returns false.
 ******************************************************************************/
__STATIC_INLINE bool VCMP_VDDHigher(void)
{
  if (VCMP->STATUS & VCMP_STATUS_VCMPOUT) {
    return true;
  } else {
    return false;
  }
}

/***************************************************************************//**
 * @brief
 *    VCMP output is ready.
 ******************************************************************************/
__STATIC_INLINE bool VCMP_Ready(void)
{
  if (VCMP->STATUS & VCMP_STATUS_VCMPACT) {
    return true;
  } else {
    return false;
  }
}

/***************************************************************************//**
 * @brief
 *   Clear one or more pending VCMP interrupts.
 *
 * @param[in] flags
 *   VCMP interrupt sources to clear. Use a set of interrupt flags OR-ed
 *   together to clear multiple interrupt sources for the VCMP module
 *   (VCMP_IFS_nnn).
 ******************************************************************************/
__STATIC_INLINE void VCMP_IntClear(uint32_t flags)
{
  VCMP->IFC = flags;
}

/***************************************************************************//**
 * @brief
 *   Set one or more pending VCMP interrupts from SW.
 *
 * @param[in] flags
 *   VCMP interrupt sources to set to pending. Use a set of interrupt flags
 *   OR-ed together to set multiple interrupt sources for the VCMP module
 *   (VCMP_IFS_nnn).
 ******************************************************************************/
__STATIC_INLINE void VCMP_IntSet(uint32_t flags)
{
  VCMP->IFS = flags;
}

/***************************************************************************//**
 * @brief
 *   Disable one or more VCMP interrupts.
 *
 * @param[in] flags
 *   VCMP interrupt sources to enable. Use a set of interrupt flags OR-ed
 *   together to set multiple interrupt sources for the VCMP module
 *   (VCMP_IFS_nnn).
 ******************************************************************************/
__STATIC_INLINE void VCMP_IntDisable(uint32_t flags)
{
  VCMP->IEN &= ~flags;
}

/***************************************************************************//**
 * @brief
 *   Enable one or more VCMP interrupts.
 *
 * @param[in] flags
 *   VCMP interrupt sources to enable. Use a set of interrupt flags OR-ed
 *   together to set multiple interrupt sources for the VCMP module
 *   (VCMP_IFS_nnn).
 ******************************************************************************/
__STATIC_INLINE void VCMP_IntEnable(uint32_t flags)
{
  VCMP->IEN |= flags;
}

/***************************************************************************//**
 * @brief
 *   Get pending VCMP interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @return
 *   Pending VCMP interrupt sources. Returns a set of interrupt flags OR-ed
 *   together for multiple interrupt sources in the VCMP module (VCMP_IFS_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t VCMP_IntGet(void)
{
  return VCMP->IF;
}

/***************************************************************************//**
 * @brief
 *   Get enabled and pending VCMP interrupt flags.
 *
 * @details
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled VCMP interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in VCMP_IEN_nnn
 *   register (VCMP_IEN_nnn) and
 *   - the OR combination of valid interrupt flags of the VCMP module
 *   (VCMP_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t VCMP_IntGetEnabled(void)
{
  uint32_t tmp = 0U;

  /* Store VCMP->IEN in a temporary variable to define explicit order
   * of volatile accesses. */
  tmp = VCMP->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return VCMP->IF & tmp;
}

/** @} (end addtogroup VCMP) */
/** @} (end addtogroup emlib) */

#ifdef __cplusplus
}
#endif

#endif /* defined(VCMP_COUNT) && (VCMP_COUNT > 0) */
#endif /* EM_VCMP_H */
