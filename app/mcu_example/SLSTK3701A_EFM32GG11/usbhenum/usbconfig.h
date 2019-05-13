/***************************************************************************//**
 * @file usbconfig.h
 * @brief USB protocol stack library, application supplied configuration options.
 * @version 5.6.1
 *******************************************************************************
 * # License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef USBCONFIG_H
#define USBCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define USB_HOST                // Compile stack for host mode.

#define USB_CLKSRC_HFRCODPLL    // Use HFRCO and DPLL as USB clock

// Use DPLL with 50 MHz HFXO as reference clock:
#define USB_DPLL_FREQUENCY      48000000UL
#define USB_DPLL_M              349U
#define USB_DPLL_N              335U
#define USB_DPLL_SRC            USB_DPLL_SRC_HFXO

/****************************************************************************
**                                                                         **
** Specify number of host channels used (in addition to EP0).              **
**                                                                         **
*****************************************************************************/
#define NUM_HC_USED 0       // Not counting default control ep which
//                             is assigned to host channels 0 and 1

/****************************************************************************
**                                                                         **
** Configure serial port debug output.                                     **
**                                                                         **
*****************************************************************************/
// Define a function for transmitting a single char on the serial port.
extern int RETARGET_WriteChar(char c);
#define USER_PUTCHAR  RETARGET_WriteChar

// Debug USB API functions (illegal input parameters etc.)
#define DEBUG_USB_API

//
// Some utility functions in the API needs printf. These
// functions have "print" in their name. This macro enables
// these functions.
//
#define USB_USE_PRINTF

#ifdef __cplusplus
}
#endif

#endif // USBCONFIG_H
