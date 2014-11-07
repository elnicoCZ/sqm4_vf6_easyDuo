/** ****************************************************************************
 *
 *  @file       esl_i2c.h
 *  @brief      I2C peripheral control module.
 *
 *  I2C peripheral general definitions and control functions.
 *
 *  Please note the module has been (roughly) tested only for interrupt
 *  controlled I2C communication, for polled mode some modifications are needed
 *  with high probability. See the differences between eeprom_polled.c and
 *  eeprom_int.c in the i2c mqx demo.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    2.2 2014-11-07: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              core_mutex locking option added for VF6.
 *
 *  @version    2.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.0 2014-01-07: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Integrated into ESL (from birdhouse project).
 *
 *  @version    1.1 2013-10-23: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Device registers address width attribute
 *                              added to i2c_device_struct.
 *
 *  @version    1.0 2013-10-16: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision = integrated code from
 *                              led_max7314.h v1.1 and i2cs.h v1.0 cloned from
 *                              Elnico's NS150 project
 *                              (Credits to Jaromir Kubiznak <kubiznak@elnico.cz>,
 *                              Petr Kubiznak <kubiznak.petr@elnico.cz>).
 *
 ******************************************************************************/
/*
 *  THIS SOFTWARE IS PROVIDED BY ELNICO "AS IS" AND ANY EXPRESSED OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL ELNICO OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef ESL_I2C_H_87037141031231450581462107
#define ESL_I2C_H_87037141031231450581462107
//******************************************************************************

#include "esl_i2c_config.h"

#include <mqx.h>
#include <bsp.h>

//******************************************************************************
// I2C channel and device object structures
//******************************************************************************

/** I2C channel object structure. Meant to be used globally as one channel
 *  can be accessed from different modules. */
typedef struct esl_i2c_channel_struct {
  MQX_FILE_PTR    pChannelFile;                             //!< FIO handle.
  LWSEM_STRUCT    lwsem;                                    //!< Exclusive channel usage semaphore.
  uint_32         u32BaudRate;                              //!< Channel baud rate.
  char            asNames[2][ESL_I2C_CHANNELNAMEMAXLEN];    //!< Channel names (IRQ, POLLED).
  uint_8          u8Number;                                 //!< Channel number.
  uint_8          u8DriverMode;                             //!< Driver mode. Equals index of the used channel name.
  uint_8          u8Mode;                                   //!< Channel mode (I2C_MODE_MASTER / I2C_MODE_SLAVE).
  uint_8          u8Cnt;                                    //!< Number of devices open on that channel.
} ESL_I2C_TChannel;

/** I2C device object structure. Meant to be used locally in every module
 *  using I2C. */
typedef struct i2c_device_struct {
  ESL_I2C_TChannel      * poChannel;                        //!< Channel used by the device.
  uint_8                  u8Addr;                           //!< Device address (7 bits).
  uint_8                  u8RegAddrBytes;                   //!< Number of bytes for device registers addressing.
} ESL_I2C_TDevice;

//******************************************************************************
// Channel definitions
//******************************************************************************

#define ESL_I2C0_NO                     (0)
#define ESL_I2C1_NO                     (1)
#define ESL_I2C2_NO                     (2)
#define ESL_I2C3_NO                     (3)

#define ESL_I2C_DRIVERMODE_INT          (0)
#define ESL_I2C_DRIVERMODE_POLLED       (1)

//******************************************************************************
// Return values
//******************************************************************************
enum {
  ESL_I2C_OK = MQX_OK,
  ESL_I2C_CHANNEL_DISABLED,
  ESL_I2C_CHANNEL_OPEN,
  ESL_I2C_CHANNEL_CLOSE,
  ESL_I2C_CHANNEL_ATTR_FAILURE,
  ESL_I2C_CHANNEL_FOPEN_FAILURE,
  ESL_I2C_CHANNEL_SET_BAUD_FAILURE,
  ESL_I2C_CHANNEL_SET_MODE_FAILURE,
  ESL_I2C_DEVICE_CLOSED,
  ESL_I2C_CLOSE_FAILURE,
  ESL_I2C_NOT_INITIALIZED,
  ESL_I2C_LWSEM_CREATE_FAILURE,
  ESL_I2C_LWSEM_WAIT_FAILURE,
  ESL_I2C_START_FAILURE,
  ESL_I2C_STOP_FAILURE,
  ESL_I2C_RESTART_FAILURE,
  ESL_I2C_RX_REQUEST_FAILURE,
  ESL_I2C_FLUSH_FAILURE,
  ESL_I2C_ACK_FAILURE,
  ESL_I2C_INVALID_ARGUMENT,
  ESL_I2C_MODULE_OFF,
};

//******************************************************************************
// Public functions
//******************************************************************************

/** Opens the I2C device and the I2C channel if not open yet. Prepares
 *  the channel and device handles but does not actually try the connection.
 * @param[out]    poDevice        Structure to be filled by a device information.
 * @param[in]     u8ChannelNo     Channel number - ESL_I2C0_NO to ESL_I2C3_NO.
 * @param[in]     u8DriverMode    Required driver mode - ESL_I2C_DRIVERMODE_INT
 *                                 or ESL_I2C_DRIVERMODE_POLLED.
 * @param[in]     u8ChannelMode   Required channel mode - I2C_MODE_MASTER
 *                                 or I2C_MODE_SLAVE.
 * @param[in]     u32BaudRate     Required channel baud rate.
 * @param[in]     u8DeviceAddr    7-bit I2C address of the device.
 * @param[in]     u8RegAddrBytes  Number of bytes for registers addressing.
 *                                 Value from 0 to 4.
 * @param[in]     u32WaitTicks    Maximum number of ticks to wait before failure.
 *                                 Use 0 for infinite wait.
 * @return        ESL_I2C_OK if channel openning succeeds or the channel is already open and has the same attributes as required.
 *                ESL_I2C_CHANNEL_DISABLED if the channel is disabled - see module configuration and BSP.
 *                ESL_I2C_CHANNEL_ATTR_FAILURE if the channel is already open but has different attrs.
 *                ESL_I2C_CHANNEL_FOPEN_FAILURE if the channel was closed but FIO openning failed.
 *                ESL_I2C_CHANNEL_SET_BAUD_FAILURE if channel baud rate setting failed.
 *                ESL_I2C_CHANNEL_SET_MODE_FAILURE if this device mode setting failed.
 *                ESL_I2C_LWSEM_CREATE_FAILURE if exclusive access semaphore creation failed.
 *                ESL_I2C_LWSEM_WAIT_FAILURE if waiting for access to the channel failed.
 *                ESL_I2C_INVALID_ARGUMENT if some argument has invalid value.
 *                ESL_I2C_MODULE_OFF if the I2C module is disabled. */
int esl_i2c_open(ESL_I2C_TDevice      * poDevice,
                 uint_8                 u8ChannelNo,
                 uint_8                 u8DriverMode,
                 uint_8                 u8ChannelMode,
                 uint_32                u32BaudRate,
                 uint_8                 u8DeviceAddr,
                 uint_8                 u8RegAddrBytes,
                 uint_32                u32WaitTicks);

/** Closes the I2C device and the I2C channel if not used anymore.
 * @param[in,out] poDevice        Device to be closed.
 * @param[in]     u32WaitTicks    Maximum number of ticks to wait before failure.
 *                                Use 0 for infinite wait.
 * @return        ESL_I2C_OK if the device was successfully closed.
 *                ESL_I2C_DEVICE_CLOSED if the device is already closed.
 *                ESL_I2C_CLOSE_FAILURE if channel closing failed.
 *                ESL_I2C_LWSEM_WAIT_FAILURE if waiting for access to the channel failed.
 *                ESL_I2C_INVALID_ARGUMENT if hDevice is NULL.
 *                ESL_I2C_MODULE_OFF if the I2C module is disabled. */
int esl_i2c_close(ESL_I2C_TDevice   * poDevice,
                  uint_32             u32WaitTicks);

/** Tries the I2C connection to the device.
 * @param[in]   poDevice        Initialized I2C device.
 * @param[in]   u32WaitTicks    Maximum number of ticks to wait before failure.
 *                              Use 0 for infinite wait.
 * @return      ESL_I2C_OK if the communication works correctly.
 *              ESL_I2C_START_FAILURE if the communication fails to start.
 *              ESL_I2C_WRITE_FAILURE if writing to the bus fails.
 *              ESL_I2C_FLUSH_FAILURE if data flushing fails.
 *              ESL_I2C_ACK_FAILURE if no ACK is received.
 *              ESL_I2C_STOP_FAILURE if the communication fails to stop
 *               (may overwrite some previous error code).
 *              ESL_I2C_NOT_INITIALIZED if the I2C device given as argument is not open.
 *              ESL_I2C_LWSEM_WAIT_FAILURE if waiting for access to the channel failed.
 *              ESL_I2C_INVALID_ARGUMENT if some argument has invalid value.
 *              ESL_I2C_MODULE_OFF if the I2C module is disabled. */
int esl_i2c_ping(const ESL_I2C_TDevice  * poDevice,
                 uint_32                  u32WaitTicks);

/** Writes data to the device on the I2C bus.
 * @param[in]   poDevice      Initialized I2C device to send the data to.
 * @param[in]   u32Addr       Register address of the device to write to.
 * @param[in]   au8Data       Pointer to data to be written.
 * @param[in]   u8Len         Length of the data to be written (number of bytes).
 * @param[in]   u32WaitTicks  Maximum number of ticks to wait before failure.
 *                            Use 0 for infinite wait.
 * @return      ESL_I2C_OK if write operation succeeds.
 *              ESL_I2C_START_FAILURE if the communication fails to start.
 *              ESL_I2C_WRITE_FAILURE if writing to the bus fails.
 *              ESL_I2C_FLUSH_FAILURE if data flushing fails.
 *              ESL_I2C_ACK_FAILURE if no ACK is received.
 *              ESL_I2C_STOP_FAILURE if the communication fails to stop
 *               (may overwrite some previous error code).
 *              ESL_I2C_NOT_INITIALIZED if the I2C device given as argument is not open.
 *              ESL_I2C_LWSEM_WAIT_FAILURE if waiting for access to the channel failed.
 *              ESL_I2C_INVALID_ARGUMENT if some argument has invalid value.
 *              ESL_I2C_MODULE_OFF if the I2C module is disabled. */
int esl_i2c_write(const ESL_I2C_TDevice   * poDevice,
                  uint_32                   u32Addr,
                  const uint_8            * au8Data,
                  uint_8                    u8Len,
                  uint_32                   u32WaitTicks);

/** Reads data from the device on the I2C bus.
 * @param[in]   poDevice      Initialized I2C device to read the data from.
 * @param[in]   u32Addr       Register address of the device to read from.
 * @param[out]  au8Data       Allocated memory to store the read data to.
 * @param[in]   u8Len         Length of the data to be read (number of bytes).
 * @param[in]   u32WaitTicks  Maximum number of ticks to wait before failure.
 *                            Use 0 for infinite wait.
 * @return      ESL_I2C_OK if read operation succeeds.
 *              I2C_START_FAILURE if the communication fails to start.
 *              I2C_WRITE_FAILURE if address writing to the bus fails.
 *              I2C_FLUSH_FAILURE if address flushing fails.
 *              I2C_ACK_FAILURE if no ACK is received.
 *              I2C_RESTART_FAILURE if restarting I2C transfer for reading fails.
 *              I2C_RX_REQUEST_FAILURE sending RX request fails.
 *              I2C_STOP_FAILURE if the communication fails to stop.
 *               This problem may be unreported if another error occured before.
 *              I2C_NOT_INITIALIZED if the I2C device given as argument is not open.
 *              I2C_LWSEM_WAIT_FAILURE if waiting for access to the channel failed.
 *              I2C_INVALID_ARGUMENT if some argument has invalid value.
 *              ESL_I2C_MODULE_OFF if the I2C module is disabled. */
int esl_i2c_read(const ESL_I2C_TDevice  * hDevice,
                 uint_32                  u32Addr,
                 uint_8                 * au8Data,
                 uint_8                   u8Len,
                 uint_32                  u32WaitTicks);

//******************************************************************************
#endif /* ESL_I2C_H_87037141031231450581462107 */
