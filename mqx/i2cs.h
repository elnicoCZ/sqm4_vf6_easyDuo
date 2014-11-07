/** ****************************************************************************
 *
 *  @file       i2cs.h
 *  @brief      I2C ports distribution to application.
 *
 *  This file contains a specification of which I2C channel and address
 *  is used by which application module.
 *
 *  @copyright  Petr Kubiznak. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-09-18: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision.
 *
 ******************************************************************************/

#ifndef I2CS_H_16520742101654054001145105
#define I2CS_H_16520742101654054001145105
//******************************************************************************

#include "esl_i2c.h"
#include "esl_i2c_MMA845xQ.h"

//******************************************************************************
// Application specific list of used I2C devices
//******************************************************************************
// I2C0 channel configuration
#define I2C0_NO                             ESL_I2C0_NO
#define I2C0_DRIVER_MODE                    ESL_I2C_DRIVERMODE_INT
#define I2C0_CHANNEL_MODE                   I2C_MODE_MASTER
#define I2C0_BAUDRATE                       400000

// MMA8451Q accelerometer
#define ACCEL_MMA8451Q_CHANNEL_NO           I2C0_NO
#define ACCEL_MMA8451Q_DRIVER_MODE          I2C0_DRIVER_MODE
#define ACCEL_MMA8451Q_CHANNEL_MODE         I2C0_CHANNEL_MODE
#define ACCEL_MMA8451Q_CHANNEL_BAUDRATE     I2C0_BAUDRATE
#define ACCEL_MMA8451Q_SA0                  (0)
#define ACCEL_MMA8451Q_DEVICE_ADDRESS       ESL_I2C_MMA845XQ_SLAVE_ADDRESS(ACCEL_MMA8451Q_SA0)
#define ACCEL_MMA8451Q_REG_ADDR_SIZE        ESL_I2C_MMA845XQ_REG_ADDR_SIZE

//******************************************************************************
#endif // I2CS_H_16520742101654054001145105 //
