/**************************************************************************//**
 * @file network.h
 * @brief Initializes the network
 * @version 5.6.1
 ******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef  NETWORK_H
#define  NETWORK_H

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Global Function Prototypes

void Network_Init(void);
void Network_Start(void);

#ifdef __cplusplus
}
#endif

#endif /* NETWORK_H */
