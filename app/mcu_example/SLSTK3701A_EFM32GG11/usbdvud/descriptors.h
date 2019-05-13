/***************************************************************************//**
 * @file descriptors.h
 * @brief USB descriptor prototypes for Vendor Unique Device example project.
 * @version 5.6.1
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef SILICON_LABS_DESCRIPTORS_H
#define SILICON_LABS_DESCRIPTORS_H

#include "em_usb.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const USB_DeviceDescriptor_TypeDef   USBDESC_deviceDesc;
extern const uint8_t                        USBDESC_configDesc[];
extern const void * const                   USBDESC_strings[4];
extern const uint8_t                        USBDESC_bufferingMultiplier[];

#ifdef __cplusplus
}
#endif

#endif /* SILICON_LABS_DESCRIPTORS_H */
