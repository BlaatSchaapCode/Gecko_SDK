/***************************************************************************//**
 * @file reference_design/ist_a0051/config/ist_a0051.h
 * @brief EFR32 Smart Outlet Reference Design HAL configuration parameters
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/
#ifndef IST_A0051_H
#define IST_A0051_H

#include "hal/micro/cortexm3/efm32/hal-config/hal-config-types.h"
// -----------------------------------------------------------------------------
/* led-blink configuration */
//Inform the led-blink plugin that this board only has two LED
#define MAX_LED_NUMBER        2
//Inform the led-blink plugin that LEDs are active high
#define LED_ACTIVE_HIGH
// Define status and power LEDs
#define STATUS_LED 0
#define POWER_LED 1

// -----------------------------------------------------------------------------
/* smart outlet configuration
 * The following are used to abstract gpio contol of power replay and
 * reset pin of the power sensor, it is specific for smart outlet project
 */
//GPIO pin for relay on control
#define P_RELAY_ON_PIN       (15)
#define P_RELAY_ON_PORT      (gpioPortB)
//GPIO pin for relay off control
#define P_RELAY_OFF_PIN      (14)
#define P_RELAY_OFF_PORT     (gpioPortB)
//GPIO pin to reset the power sensor
#define PWR_SEN_RESET_PIN    (5)
#define PWR_SEN_RESET_PORT   (gpioPortA)

// -----------------------------------------------------------------------------
/* BUTTON */
// Enable one button, 0
#define HAL_BUTTON_COUNT     1
#define HAL_BUTTON_ENABLE    { 0 }
// Board has one buttons
#define BSP_BUTTON_COUNT     1
#define BSP_BUTTON_INIT                    \
  {                                        \
    { BSP_BUTTON0_PORT, BSP_BUTTON0_PIN }, \
  }
// Initialize button GPIO DOUT to 0
#define BSP_BUTTON_GPIO_DOUT HAL_GPIO_DOUT_LOW
// Initialize button GPIO mode as input
#define BSP_BUTTON_GPIO_MODE HAL_GPIO_MODE_INPUT
// Define individual button GPIO port/pin
#define BSP_BUTTON0_PORT     gpioPortA
#define BSP_BUTTON0_PIN      3

// -----------------------------------------------------------------------------
/* CLK */
// Set up HFCLK source as HFXO
#define HAL_CLK_HFCLK_SOURCE HAL_CLK_HFCLK_SOURCE_HFXO
// Setup LFCLK source as LFRCO
#define HAL_CLK_LFCLK_SOURCE HAL_CLK_LFCLK_SOURCE_LFRCO
// Set HFXO frequency as 38.4MHz
#define BSP_CLK_HFXO_FREQ 38400000UL
// HFXO initialization settings
#define BSP_CLK_HFXO_INIT                                                  \
  {                                                                        \
    false,      /* Low-noise mode for EFR32 */                             \
    false,      /* Disable auto-start on EM0/1 entry */                    \
    false,      /* Disable auto-select on EM0/1 entry */                   \
    false,      /* Disable auto-start and select on RAC wakeup */          \
    _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,                                    \
    0x142,      /* Steady-state CTUNE for WSTK boards without load caps */ \
    _CMU_HFXOSTEADYSTATECTRL_REGISH_DEFAULT,                               \
    0x20,       /* Matching errata fix in CHIP_Init() */                   \
    0x7,        /* Recommended steady-state osc core bias current */       \
    0x6,        /* Recommended peak detection threshold */                 \
    _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_DEFAULT,                          \
    0xA,        /* Recommended peak detection timeout  */                  \
    0x4,        /* Recommended steady timeout */                           \
    _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,                           \
    cmuOscMode_Crystal,                                                    \
  }
// Board has HFXO
#define BSP_CLK_HFXO_PRESENT 1
// Set LFXO frequency as 32.768kHz
#define BSP_CLK_LFXO_FREQ 32768UL
// Board has LFXO
#define BSP_CLK_LFXO_PRESENT 1

// -----------------------------------------------------------------------------
/* DCDC */
// MCU is wired for DCDC mode
#define BSP_DCDC_PRESENT 1
// Use emlib default DCDC initialization
#define BSP_DCDC_INIT    EMU_DCDCINIT_DEFAULT
// Do not enable bypass mode
#define HAL_DCDC_BYPASS  0

// -----------------------------------------------------------------------------
/* EXTFLASH */
#define HAL_EXTFLASH_USART_BAUDRATE 6400000U
#define BSP_EXTFLASH_CS_LOC         _USART_ROUTELOC0_CSLOC_LOC1
#define BSP_EXTFLASH_CS_PIN         4
#define BSP_EXTFLASH_CS_PORT        gpioPortA
#define BSP_EXTFLASH_MISO_LOC       _USART_ROUTELOC0_RXLOC_LOC11
#define BSP_EXTFLASH_MISO_PIN       7
#define BSP_EXTFLASH_MISO_PORT      gpioPortC
#define BSP_EXTFLASH_MOSI_LOC       _USART_ROUTELOC0_TXLOC_LOC11
#define BSP_EXTFLASH_MOSI_PIN       6
#define BSP_EXTFLASH_MOSI_PORT      gpioPortC
#define BSP_EXTFLASH_SCLK_LOC       _USART_ROUTELOC0_CLKLOC_LOC11
#define BSP_EXTFLASH_SCLK_PIN       8
#define BSP_EXTFLASH_SCLK_PORT      gpioPortC
#define BSP_EXTFLASH_USART          USART1
#define BSP_EXTFLASH_USART_CLK      cmuClock_USART1

// -----------------------------------------------------------------------------
/* LED */
// Enable two LEDs, 0 and 1
#define HAL_LED_COUNT  2
#define HAL_LED_ENABLE { 0, 1 }
// Board has two LEDs
#define BSP_LED_COUNT  2
#define BSP_LED_INIT                 \
  {                                  \
    { BSP_LED0_PORT, BSP_LED0_PIN }, \
    { BSP_LED1_PORT, BSP_LED1_PIN }  \
  }
// Define individual LED GPIO port/pin
#define BSP_LED0_PIN  6
#define BSP_LED0_PORT gpioPortF
#define BSP_LED1_PIN  5
#define BSP_LED1_PORT gpioPortF

// -----------------------------------------------------------------------------
/* PA */
#define HAL_PA_2P4_ENABLE      1
#define HAL_PA_2P4_VOLTMODE    PA_VOLTMODE_DCDC
#define HAL_PA_2P4_POWER       100
#define HAL_PA_2P4_OFFSET      0
#define HAL_PA_2P4_RAMP        10

// -----------------------------------------------------------------------------
/* PTI */
#define HAL_PTI_ENABLE         1
#define HAL_PTI_BAUD_RATE      1600000
#define HAL_PTI_MODE           HAL_PTI_MODE_UART
#define BSP_PTI_PRESENT        1
#define BSP_PTI_DCLK_LOC       6
#define BSP_PTI_DCLK_PORT      gpioPortB
#define BSP_PTI_DCLK_PIN       11
#define BSP_PTI_DFRAME_LOC     6
#define BSP_PTI_DFRAME_PORT    gpioPortB
#define BSP_PTI_DFRAME_PIN     13
#define BSP_PTI_DOUT_LOC       6
#define BSP_PTI_DOUT_PORT      gpioPortB
#define BSP_PTI_DOUT_PIN       12

// -----------------------------------------------------------------------------
/* USART1 */
#define BSP_USART1_CLK_LOC               _USART_ROUTELOC0_CLKLOC_LOC11
#define BSP_USART1_CS_LOC                _USART_ROUTELOC0_CSLOC_LOC11
#define BSP_USART1_CS_PIN                7
#define BSP_USART1_CS_PORT               gpioPortF
#define BSP_USART1_MISO_LOC              _USART_ROUTELOC0_RXLOC_LOC11
#define BSP_USART1_MOSI_LOC              _USART_ROUTELOC0_TXLOC_LOC11

// -----------------------------------------------------------------------------
/* USART0 */
#define BSP_USART0_RX_LOC                _USART_ROUTELOC0_RXLOC_LOC0
#define BSP_USART0_RX_PIN                1
#define BSP_USART0_RX_PORT               gpioPortA
#define BSP_USART0_TX_LOC                _USART_ROUTELOC0_TXLOC_LOC0
#define BSP_USART0_TX_PIN                0
#define BSP_USART0_TX_PORT               gpioPortA

// -----------------------------------------------------------------------------
/* VCOM */
#define BSP_VCOM_PRESENT                 1
#define BSP_VCOM_ENABLE_PIN              5
#define BSP_VCOM_ENABLE_PORT             gpioPortA
#define BSP_VCOM_RX_LOC                  _USART_ROUTELOC0_RXLOC_LOC0
#define BSP_VCOM_RX_PIN                  1
#define BSP_VCOM_RX_PORT                 gpioPortA
#define BSP_VCOM_TX_LOC                  _USART_ROUTELOC0_TXLOC_LOC0
#define BSP_VCOM_TX_PIN                  0
#define BSP_VCOM_TX_PORT                 gpioPortA
#define BSP_VCOM_USART                   HAL_SERIAL_PORT_USART0
#endif //IST_A0051_H
