/**************************************************************************//**
 * @file cmd_declarations.h
 * @brief Prototypes of all functions for shell demo.
 * @version 5.6.1
 ******************************************************************************
 * # License
 * <b>Copyright 2017 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/
#ifndef CMD_DECLARATIONS_H
#define CMD_DECLARATIONS_H

#include <string.h>

#include <common/include/rtos_err.h>
#include <common/include/rtos_utils.h>
#include <common/include/shell.h>
#include <cpu/include/cpu.h>

// -----------------------------------------------------------------------------
// Function prototypes

CPU_INT16S ShellDefaultShellout (CPU_CHAR *pbuf,
                                 CPU_INT16U buf_len,
                                 void *popt);

CPU_INT16S helpCmd              (CPU_INT16U argc,
                                 CPU_CHAR *argv[],
                                 SHELL_OUT_FNCT outFunc,
                                 SHELL_CMD_PARAM *cmdParam);

CPU_INT16S initCmd              (CPU_INT16U argc,
                                 CPU_CHAR *argv[],
                                 SHELL_OUT_FNCT outFunc,
                                 SHELL_CMD_PARAM *cmdParam);

CPU_INT16S selftestCmd          (CPU_INT16U argc,
                                 CPU_CHAR *argv[],
                                 SHELL_OUT_FNCT outFunc,
                                 SHELL_CMD_PARAM *cmdParam);

CPU_INT16S sleepCmd             (CPU_INT16U argc,
                                 CPU_CHAR *argv[],
                                 SHELL_OUT_FNCT outFunc,
                                 SHELL_CMD_PARAM *cmdParam);

// -----------------------------------------------------------------------------
// Global variables

extern SHELL_CMD commandTable[]; // Table of shell commands

#endif // CMD_DECLARATIONS_H
