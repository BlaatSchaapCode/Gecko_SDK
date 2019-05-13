/**************************************************************************//**
 * @file webserver.h
 * @brief http server without filesystem
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

#include <cpu/include/cpu.h>

#ifndef WEBSERVER_H
#define WEBSERVER_H

extern CPU_CHAR Ex_HTTPs_Name[];

// -----------------------------------------------------------------------------
// Global Function Prototypes

void Webserver_Init  (void);
void Webserver_Start (void);

#endif
