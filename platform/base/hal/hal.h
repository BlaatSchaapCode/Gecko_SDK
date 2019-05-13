/** @file hal/hal.h
 * @brief Generic set of HAL includes for all platforms.
 *
 * See also @ref hal for more documentation.
 *
 * Some HAL includes are not used or present in builds intended for the Host
 * processor connected to the Ember Network Coprocessor.
 *
 * <!-- Copyright 2008-2010 by Ember Corporation. All rights reserved.   *80*-->
 */

/** @addtogroup hal
 *  @if EM35x
 *    EM35x Microprocessors
 *  @endif
 *  @if STM32F103RET
 *    STM32F103RET Host Microcontroller
 *  @endif
 *  @if PC_Host
 *    PC Host
 *  @endif
 *
 * HAL function names have the following prefix conventions:
 *
 *  <b>halCommon:</b>   API that is used by the EmberZNet stack and can also be called
 *                 from an application. This API must be implemented. Custom
 *                 applications can change the implementation of the API but
 *                 its functionality must remain the same.
 *
 *  <b>hal:</b>    API that is used by sample applications. Custom
 *                 applications can remove this API or change its
 *                 implementation as they see fit.
 *
 *
 *  <b>halStack:</b>   API used only by the EmberZNet stack. This API must be implemented
 *                 and should not be directly called from any application.
 *                 Custom applications can change the implementation of the
 *                 API, but its functionality must remain the same.
 *
 *  <b>halInternal:</b>   API that is internal to the HAL. The EmberZNet stack
 *                and applications must never call this API directly.
 *                Custom applications can change this API as they see
 *                fit. However, be careful not to impact the functionalty of
 *                any halStack or halCommon APIs.
 * <br><br>
 *
 * See also hal.h.
 */

#ifndef __HAL_H__
#define __HAL_H__

#ifdef HAL_HOST

#include "host/button-common.h"
#include "host/crc.h"
#include "host/led-common.h"
#include "host/micro-common.h"
#include "host/serial.h"
#include "host/system-timer.h"
#include "host/bootloader-eeprom.h"
//Pull in the micro specific ADC, buzzer, and clocks headers.  The
//specific header is chosen by the build include path pointing at
//the appropriate directory.
#include "plugin/adc/adc-stm32f103ret.h"

#ifdef STM32F10X_HD
#include "plugin/buzzer/buzzer-stm32f103ret.h"
#else
#include "plugin/buzzer/buzzer.h"
#endif

#else //HAL_MICRO

// Keep micro and board first for specifics used by other headers
#include "micro/micro.h"
#if !defined(STACK)
#ifdef BOARD_HEADER
  #include BOARD_HEADER
#endif
#ifdef HAL_CONFIG
  #include HAL_CONFIG
// Support legacy BUTTONn parameter
  #ifdef BSP_BUTTON0_PIN
  #define BUTTON0 BSP_BUTTON0_PIN
  #endif
  #ifdef BSP_BUTTON1_PIN
  #define BUTTON1 BSP_BUTTON1_PIN
  #endif
  #ifdef BSP_BUTTON2_PIN
  #define BUTTON2 BSP_BUTTON2_PIN
  #endif
  #ifdef BSP_BUTTON3_PIN
  #define BUTTON3 BSP_BUTTON3_PIN
  #endif
  #ifdef BSP_BUTTON4_PIN
  #define BUTTON4 BSP_BUTTON4_PIN
  #endif
  #ifdef BSP_BUTTON5_PIN
  #define BUTTON5 BSP_BUTTON5_PIN
  #endif
  #ifdef BSP_BUTTON6_PIN
  #define BUTTON6 BSP_BUTTON6_PIN
  #endif
  #ifdef BSP_BUTTON7_PIN
  #define BUTTON7 BSP_BUTTON7_PIN
  #endif
  #ifdef HAL_SERIAL_APP_PORT
  #define APP_SERIAL HAL_SERIAL_APP_PORT
  #else // support alternatively APP_SERIAL or HAL_SERIAL_APP_PORT
  #ifdef APP_SERIAL
    #define HAL_SERIAL_APP_PORT APP_SERIAL
  #endif
  #endif
  #if defined(EMBER_ASSERT_SERIAL_PORT) && defined (HAL_SERIAL_ASSERT_PORT)
  #undef EMBER_ASSERT_SERIAL_PORT
  #endif
  #ifdef HAL_SERIAL_ASSERT_PORT
  #define EMBER_ASSERT_SERIAL_PORT HAL_SERIAL_ASSERT_PORT
  #endif
  #if HAL_ANTDIV_ENABLE
  #define ANTENNA_SELECT_GPIO   ((BSP_ANTDIV_SEL_PORT << 4) | BSP_ANTDIV_SEL_PIN)
  #define ANTENNA_nSELECT_GPIO  ((BSP_ANTDIV_NSEL_PORT << 4) | BSP_ANTDIV_NSEL_PIN)
  #endif
  #if HAL_PTA_ENABLE
  #define ENABLE_PTA 1
  #define PTA_REQ_GPIO      ((BSP_PTA_REQ_PORT << 4) | BSP_PTA_REQ_PIN)
  #define PTA_GNT_GPIO      ((BSP_PTA_GNT_PORT << 4) | BSP_PTA_GNT_PIN)
  #define PTA_PRI_GPIO      ((BSP_PTA_PRI_PORT << 4) | BSP_PTA_PRI_PIN)
  #define PTA_REQ_ASSERTED  BSP_PTA_REQ_ASSERT_LEVEL
  #define PTA_GNT_ASSERTED  BSP_PTA_GNT_ASSERT_LEVEL
  #define PTA_PRI_ASSERTED  BSP_PTA_PRI_ASSERT_LEVEL
  #if BSP_PTA_REQ_SHARED
    #define PTA_REQ_SHARED  1
  #endif
  #endif
  #if HAL_RHO_ENABLE
  #define RADIO_HOLDOFF 1
  #define RHO_GPIO      ((BSP_RHO_PORT << 4) | BSP_RHO_PIN)
  #define RHO_ASSERTED  BSP_RHO_ASSERT_LEVEL
  #endif
  #ifndef HAL_GPIO_MAX
  #define HAL_GPIO_MAX 0
  #endif
  #ifdef RF_USARTRF_CS_PORT
  #define BSP_EXTDEV_CS_PORT  RF_USARTRF_CS_PORT
  #define BSP_EXTDEV_CS_PIN   RF_USARTRF_CS_PIN
  #define BSP_EXTDEV_INT_PORT RF_INT_PORT
  #define BSP_EXTDEV_INT_PIN  RF_INT_PIN
  #define BSP_EXTDEV_SDN_PORT RF_SDN_PORT
  #define BSP_EXTDEV_SDN_PIN  RF_SDN_PIN
  #endif
#elif defined(BOARD_HEADER) //HAL_CONFIG
#define HAL_SERIAL_APP_PORT APP_SERIAL
#ifdef COM_RETARGET_SERIAL
  #define BSP_BUTTON0_PIN   BUTTON0
  #define BSP_BUTTON0_PORT  BUTTON0_PORT
  #define BSP_BUTTON1_PIN   BUTTON1
  #define BSP_BUTTON1_PORT  BUTTON1_PORT
  #include "retargetserialconfig.h"
  #ifdef _USART_ROUTELOC0_MASK
    #define BSP_USART0_TX_LOC RETARGET_TX_LOCATION
    #define BSP_USART0_RX_LOC RETARGET_RX_LOCATION
  #else
    #define BSP_USART0_ROUTE_LOC RETARGET_LOCATION
  #endif

  #define BSP_USART0_TX_PORT RETARGET_TXPORT
  #define BSP_USART0_TX_PIN  RETARGET_TXPIN
  #define BSP_USART0_RX_PORT RETARGET_RXPORT
  #define BSP_USART0_RX_PIN  RETARGET_RXPIN

  #define halConfigInit()
  #define halConfigPowerDownGpio()
  #define halConfigPowerUpGpio()
#endif /*COM_RETARGET_SERIAL*/
#endif
#endif
#include "micro/pta.h" // pta.h needs defines from the board header
#include "plugin/antenna/antenna.h"

#if (defined(EMBER_STACK_CONNECT))
  #if (defined(UNIX_HOST) && !defined(EMBER_TEST))
    #include "plugin/adc/adc.h"
    #include "micro/button.h"
    #include "plugin/buzzer/buzzer.h"
    #include "micro/crc.h"
    #include "micro/endian.h"
    #include "micro/led.h"
    #include "micro/random.h"
    #include "micro/serial.h"
    #include "micro/spi.h"
    #include "micro/system-timer.h"
  #else
// TODO: here we include only the functionalities that we will have on mustang
    #if (defined(CORTEXM3))
      #include "plugin/adc/adc.h"
      #include "micro/bootloader-eeprom.h"
      #if ((defined _EFR_DEVICE) || (defined CORTEXM3_EMBER_MICRO))
      #include "micro/bootloader-interface.h"
      #endif
      #include "micro/button.h"
      #include "micro/led.h"
      #include "plugin/buzzer/buzzer.h"
      #include "micro/crc.h"
      #include "micro/diagnostic.h"
      #include "micro/endian.h"
    #endif //CORTEXM3
    #include "plugin/sim-eeprom/sim-eeprom.h"
    #include "micro/system-timer.h"
    #include "micro/symbol-timer.h"
    #include "micro/spi.h"
    #if (defined(CORTEXM3) || defined(EMBER_TEST))
      #include "micro/serial.h"
    #else
      #include "micro/serial-minimal.h"
    #endif
    #include "micro/random.h"
    #include "micro/token.h"
    #ifdef EMBER_TEST
      #include "plugin/adc/adc.h"
      #include "micro/bootloader-interface.h"
      #include "micro/button.h"
      #include "micro/led.h"
    #endif
  #endif // UNIX_HOST && !EMBER_TEST
#elif (defined(EMBER_STACK_OWL_RX))
// TODO: here we include only the functionalities that we will have on OWL-RX
  #include "micro/button.h"
  #include "micro/flash.h"
  #include "micro/led.h"
  #include "micro/dog_glcd.h"
  #include "micro/system-timer.h"
  #include "micro/symbol-timer.h"
  #include "micro/spi.h"
  #include "micro/serial-minimal.h"
  #include "micro/endian.h"
//  #include "micro/random.h"
//  #include "micro/token.h"
//  #ifdef EMBER_TEST
//    #include "plugin/adc/adc.h"
//    #include "micro/bootloader-interface.h"
//    #include "micro/button.h"
//    #include "micro/led.h"
//  #endif
#elif (defined(EMBER_STACK_OWL_TX))
// TODO: here we include only the functionalities that we will have on OWL-TX
//  #include "micro/button.h"
//  #include "micro/flash.h"
//  #include "micro/led.h"
//  #include "micro/dog_glcd.h"
//  #include "micro/system-timer.h"
//  #include "micro/symbol-timer.h"
//  #include "micro/spi.h"
//  #include "micro/serial-minimal.h"
//  #include "micro/random.h"
//  #include "micro/token.h"
//  #ifdef EMBER_TEST
//    #include "plugin/adc/adc.h"
//    #include "micro/bootloader-interface.h"
//    #include "micro/button.h"
//    #include "micro/led.h"
//  #endif
#elif (defined(EMBER_STACK_WASP))
// TODO: here we include only the functionalities that we will have on mustang
  #if (defined(CORTEXM3))
//    #include "plugin/adc/adc.h"
//    #include "micro/bootloader-eeprom.h"
    #include "micro/button.h"
    #include "plugin/buzzer/buzzer.h"
    #include "micro/led.h"
    #include "micro/diagnostic.h"
  #endif //CORTEXM3
  #include "micro/flash.h"
  #include "micro/system-timer.h"
  #include "micro/symbol-timer.h"
  #include "micro/spi.h"
  #if (defined(CORTEXM3))
    #include "micro/serial.h"
  #else
    #include "micro/serial-minimal.h"
  #endif
  #include "micro/random.h"
  #include "micro/token.h"
  #ifdef EMBER_TEST
    #include "plugin/adc/adc.h"
    #include "micro/bootloader-interface.h"
    #include "micro/button.h"
    #include "micro/led.h"
  #endif
#elif (!defined(EMBER_STACK_IP))
// Pro Stack
  #include "plugin/adc/adc.h"
  #include "micro/button.h"
  #include "plugin/buzzer/buzzer.h"
  #include "micro/crc.h"
  #include "micro/endian.h"
  #include "micro/led.h"
  #include "micro/random.h"
  #include "micro/serial.h"
  #include "micro/spi.h"
  #include "micro/system-timer.h"
  #include "micro/bootloader-eeprom.h"

//Host processors sometimes use the token module.
  #if !defined(EZSP_HOST) || defined(EMBER_AF_API_TOKEN)
    #include "micro/token.h"
  #endif

//Host processors do not use the following modules, therefore the header
//files should be ignored.
  #ifndef EZSP_HOST
    #include "micro/bootloader-interface.h"
    #include "micro/diagnostic.h"
//No public HAL code in release 4.0 uses the symbol timer,
//therefore it should not be in doxygen.
    #ifndef DOXYGEN_SHOULD_SKIP_THIS
      #include "micro/symbol-timer.h"
    #endif // DOXYGEN_SHOULD_SKIP_THIS
  #endif //EZSP_HOST

#else
// IP Stack
  #include "plugin/adc/adc.h"
  #include "micro/button.h"
  #include "plugin/buzzer/buzzer.h"
  #include "micro/crc.h"
  #include "micro/endian.h"
  #include "micro/led.h"
  #include "micro/random.h"
  #include "micro/serial.h"
  #include "micro/spi.h"
  #include "micro/system-timer.h"

//Host processors sometimes use the token module.
  #if !defined(UNIX_HOST) || defined(EMBER_AF_API_TOKEN)
    #include "micro/token.h"
  #endif

//Host processors do not use the following modules, therefore the header
//files should be ignored.
  #ifndef UNIX_HOST
    #include "micro/bootloader-interface.h"
    #include "micro/diagnostic.h"
//No public HAL code in release 4.0 uses the symbol timer,
//therefore it should not be in doxygen.
    #ifndef DOXYGEN_SHOULD_SKIP_THIS
      #include "micro/symbol-timer.h"
    #endif // DOXYGEN_SHOULD_SKIP_THIS
  #endif //UNIX_HOST

#endif // !EMBER_STACK_IP

#endif // !HAL_HOST

#if ((defined(RTOS) && !defined(IP_MODEM_LIBRARY)) \
  || (defined(UNIX_HOST)                           \
  || defined(UNIX_HOST_SIM)))
  #define EMBER_HOST
  #define emAmHost() true
#else
  #define emAmHost() false
#endif

#endif //__HAL_H__
