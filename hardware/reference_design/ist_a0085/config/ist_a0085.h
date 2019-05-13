/***************************************************************************//**
 * @file reference_design/ist_a0051/config/ist_a0051.h
 * @brief EFR32 lighting reference design HAL configuration parameters
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
#ifndef IST_A0085_H
#define IST_A0085_H

#include "hal/micro/cortexm3/efm32/hal-config/hal-config-types.h"
// -----------------------------------------------------------------------------
/* BUTTON */
// No buttons
#define HAL_BUTTON_COUNT     0

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
// Built in flash
#define HAL_EXTFLASH_USART_BAUDRATE 6400000U
#define BSP_EXTFLASH_CS_LOC         _USART_ROUTELOC0_CSLOC_LOC8
#define BSP_EXTFLASH_CS_PIN         6
#define BSP_EXTFLASH_CS_PORT        gpioPortC
#define BSP_EXTFLASH_HOLD_PIN       8
#define BSP_EXTFLASH_HOLD_PORT      gpioPortC
#define BSP_EXTFLASH_MISO_LOC       _USART_ROUTELOC0_RXLOC_LOC11
#define BSP_EXTFLASH_MISO_PIN       7
#define BSP_EXTFLASH_MISO_PORT      gpioPortC
#define BSP_EXTFLASH_MOSI_LOC       _USART_ROUTELOC0_TXLOC_LOC30
#define BSP_EXTFLASH_MOSI_PIN       6
#define BSP_EXTFLASH_MOSI_PORT      gpioPortF
#define BSP_EXTFLASH_SCLK_LOC       _USART_ROUTELOC0_CLKLOC_LOC12
#define BSP_EXTFLASH_SCLK_PIN       9
#define BSP_EXTFLASH_SCLK_PORT      gpioPortC
#define BSP_EXTFLASH_WP_PIN         7
#define BSP_EXTFLASH_WP_PORT        gpioPortF
#define BSP_EXTFLASH_USART          USART1
#define BSP_EXTFLASH_USART_CLK      cmuClock_USART1

// -----------------------------------------------------------------------------
/* LED */
// No LEDs
#define HAL_LED_COUNT  0

// -----------------------------------------------------------------------------
/* PA */
#define HAL_PA_2P4_ENABLE      1
#define HAL_PA_2P4_VOLTMODE    PA_VOLTMODE_VBAT
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

// Define LED Bulb PWM locations
// The lighting board supports 6 channels of PWM:  3 for RGB, 2 for
// color temperature (one of which is used for the dimmable bulb), and
// one for status.
// Each channel needs 5 things defined:
// BULB_PWM_XXX:        Software PWM channel handle.  Must be unique uint8_t.
// BULB_PWM_XXX_PORT:   Port number of the GPIO to drive the PWM channel.
// BULB_PWM_XXX_PIN:    Pin number of the GPIO to drive the PWM channel.
// BULB_PWM_XXX_TIMER:  Timer used for the PWM channel
// BULB_PWM_XXX_CHANNEL:Timer channel for the PWM channel.

/** @name BULB PWM Definitions
 *
 * The following defines are used to specify the channel and pin output of
 * the PWM drivers for the bulb.
 */
//@{

/**
 * @brief Software handle for the white PWM.  Note:  this can be any 8-bit
 * integer so long as it is unique among the PWM handles.
 */
#define BULB_PWM_WHITE            1

/**
 * @brief GPIO port of the white PWM.
 */
#define BULB_PWM_WHITE_PORT       gpioPortB

/**
 * @brief GPIO pin of the white PWM.
 */
#define BULB_PWM_WHITE_PIN        15

/**
 * @brief Timer used by the white PWM.
 */
#define BULB_PWM_WHITE_TIMER      TIMER0

/**
 * @brief Timer channel of the white PWM.
 */
#define BULB_PWM_WHITE_CHANNEL    0

/**
 * @brief Software handle for the low temperature PWM.  Note:  this can be
 * any 8-bit integer so long as it is unique among the PWM handles.
 */
#define BULB_PWM_LOWTEMP          2

/**
 * @brief GPIO port of the low temperature PWM.
 */
#define BULB_PWM_LOWTEMP_PORT     gpioPortB

/**
 * @brief GPIO pin of the low temperature PWM.
 */
#define BULB_PWM_LOWTEMP_PIN      14

/**
 * @brief Timer used by the low temperature PWM.
 */
#define BULB_PWM_LOWTEMP_TIMER    TIMER0

/**
 * @brief Timer channel of teh low temperature PWM.
 */
#define BULB_PWM_LOWTEMP_CHANNEL  1

/**
 * @brief Software handle for the status PWM.  Note:  this can be any 8-bit
 * integer so long as it is unique among the PWM handles.
 */
#define BULB_PWM_STATUS           3

/**
 * @brief GPIO port of the status PWM.
 */
#define BULB_PWM_STATUS_PORT      gpioPortB

/**
 * @brief GPIO pin of the status PWM.
 */
#define BULB_PWM_STATUS_PIN       11

/**
 * @brief Timer used by the status PWM.
 */
#define BULB_PWM_STATUS_TIMER     TIMER0

/**
 * @brief Timer channel of the status PWM.
 */
#define BULB_PWM_STATUS_CHANNEL   2

/**
 * @brief Software handle for the red PWM.  Note:  this can be any 8-bit
 * integer so long as it is unique among the PWM handles.
 */
#define BULB_PWM_RED              4

/**
 * @brief GPIO port of the red PWM.
 */
#define BULB_PWM_RED_PORT         gpioPortC

/**
 * @brief GPIO pin of the red PWM.
 */
#define BULB_PWM_RED_PIN          10

/**
 * @brief Timer used by the red PWM.
 */
#define BULB_PWM_RED_TIMER        TIMER1

/**
 * @brief Timer channel of the red PWM.
 */
#define BULB_PWM_RED_CHANNEL      0

/**
 * @brief Software handle for the green PWM.  Note:  this can be any 8-bit
 * integer so long as it is unique among the PWM handles.
 */
#define BULB_PWM_GREEN            5

/**
 * @brief GPIO port of the green PWM.
 */
#define BULB_PWM_GREEN_PORT       gpioPortD

/**
 * @brief GPIO pin of the green PWM.
 */
#define BULB_PWM_GREEN_PIN        15

/**
 * @brief Timer used by the green PWM.
 */
#define BULB_PWM_GREEN_TIMER      TIMER1

/**
 * @brief Timer channel of the green PWM.
 */
#define BULB_PWM_GREEN_CHANNEL    1

/**
 * @brief Software handle for the blue PWM.  Note:  this can be any 8-bit
 * integer so long as it is unique among the PWM handles.
 */
#define BULB_PWM_BLUE             6

/**
 * @brief GPIO port of the blue PWM.
 */
#define BULB_PWM_BLUE_PORT        gpioPortC

/**
 * @brief GPIO pin of the blue PWM.
 */
#define BULB_PWM_BLUE_PIN         11

/**
 * @brief Timer used by the blue PWM.
 */
#define BULB_PWM_BLUE_TIMER       TIMER1

/**
 * @brief Timer channel of the blue PWM.
 */
#define BULB_PWM_BLUE_CHANNEL     2

/**
 * @brief Specifies that we are using TIMER 0 for the PWMs.
 */
#define BULB_PWM_USING_TIMER0

/**
 * @brief Direct timer 0 channel 0 to PB 14
 */
#define TIMER0_CHANNEL0_LOC       TIMER_ROUTELOC0_CC0LOC_LOC9 // PB 14

/**
 * @brief Direct timer 0 channel 1 to PD 15
 */
#define TIMER0_CHANNEL1_LOC       TIMER_ROUTELOC0_CC1LOC_LOC9 // PD 15

/**
 * @brief Direct timer 0 channel 2 to PB 11
 */
#define TIMER0_CHANNEL2_LOC       TIMER_ROUTELOC0_CC2LOC_LOC4 // PB 11

/**
 * @brief Specifies that we are using TIMER 1 for the PWMs.
 */
#define BULB_PWM_USING_TIMER1

/**
 * @brief Direct timer 1 channel 0 to PC 10
 */
#define TIMER1_CHANNEL0_LOC       TIMER_ROUTELOC0_CC0LOC_LOC15 // PC 10

/**
 * @brief Direct timer 1 channel 1 to PD 15
 */
#define TIMER1_CHANNEL1_LOC       TIMER_ROUTELOC0_CC1LOC_LOC22 // PD 15

/**
 * @brief Direct timer 1 channel 2 to PC 11
 */
#define TIMER1_CHANNEL2_LOC       TIMER_ROUTELOC0_CC2LOC_LOC14 // PC 11

// default frequency of the PWM
#define PWM_DEFAULT_FREQUENCY     1000
#endif //IST_A0085_H
