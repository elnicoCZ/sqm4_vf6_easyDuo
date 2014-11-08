/** ****************************************************************************
 *
 *  @file       esl_config.h
 *  @brief      ESL global configuration file for the Accelerometer demo.
 *
 *  Main configuration file of the ESL (Elnico Support Library) library.
 *  Overrides default settings of all modules.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-09-18: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision.
 *
 ******************************************************************************/
#ifndef ESL_CONFIG_H
#define ESL_CONFIG_H

#include <mqx.h>
#include <bsp.h>

// Fix for MQX 4.1 (use proprietary MQX types).
#if (MQX_VERSION >= 410)
# include "psptypes_legacy.h"
#endif

#define ESL_APPCTRL_MODULE_ENABLE           (1)
#define ESL_I2C_MODULE_ENABLE               (1)
#define ESL_I2C_MMA845XQ_MODULE_ENABLE      (1)
#define ESL_KEYBOARD_MODULE_ENABLE          (1)
#define ESL_LOG_MODULE_ENABLE               (1)
#define ESL_RTC_MODULE_ENABLE               (1)
#define ESL_TD_MODULE_ENABLE                (1)

// Settings for esl_i2c
#define ESL_I2C_COREMUTEX_I2C_CHANNEL       (0)

// Settings for esl_keyboard
#define ESL_KEYBOARD_KEYCNT                 (1)
#define ESL_KEYBOARD_CALLBACK_ON_RELEASE    (1)

// Settings for esl_td
#define ESL_TD_DOMAINCNT                    (3)

#endif // ESL_CONFIG_H //
