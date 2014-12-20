/** ****************************************************************************
 *
 *  @file       accelerometer.c
 *  @brief      Accelerometer control task.
 *
 *  Control task for the MMA8451Q accelerometer.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-09-18: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision
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

#include "accelerometer.h"
#include "i2cs.h"

#include "esl_appctrl.h"
#include "esl_i2c.h"
#include "esl_i2c_MMA845xQ.h"
#include "esl_log.h"
#include "esl_rtc.h"
#include "esl_utils.h"

#include <mqx.h>
#include <bsp.h>
#include <lwevent.h>

//******************************************************************************
// General Definitions
//******************************************************************************

#define ACCEL_PERIODIC_INTERVAL         (25)                                    //!< Readout period in milliseconds.
#define ACCEL_INFINITE_INTERVAL         (0)                                     //!< Infinite wait period.
#define ACCEL_MAX_MISSED_CNT            ((int)(10 * 40))                        //!< Number of missed readouts before switching to standby mode (10 seconds, 40 Hz, see ACCEL_PERIODIC_INTERVAL).
#define ACCEL_LWSEM_WAIT                (10)                                    //!< Maximum number of milliseconds to wait for the semaphore.

//******************************************************************************
// Lwevent communication interface
//******************************************************************************

#define EVENT_Accel_Wakeup                  (1 << 0)                            //!< Event to wakeup from standby.
#define EVENT_Accel_Mask                    (EVENT_Accel_Wakeup)                //!< Mask of all events.

//******************************************************************************
// Globals
//******************************************************************************

static LWEVENT_STRUCT g_lwevent;                                                //!< Controls the periodic readouts.
static LWSEM_STRUCT   g_lwsem;                                                  //!< Guards exclusive access to g_oAccelData and g_u32MissedCnt.
static TAccelData     g_oAccelData;                                             //!< Accelerometer data.
static uint32_t       g_u32MissedCnt;                                           //!< Missed readouts count.

//******************************************************************************
// Functions declarations
//******************************************************************************

/** Saves the last measured accelerometer data, guarded by a semaphore.
 * @param[in]   poSrc         Source data to store to the global variable.
 * @param[in]   u32WaitTicks  Semaphore wait timeout ticks. Use 0 for infinity.
 * @return      ACCEL_OK on success.
 *              ACCEL_LWSEM_FAILURE if waiting for semaphore fails.
 *              ACCEL_OUTDATED if too many readouts have been missed by
 *              consumer(s) (see ACCEL_MAX_MISSED_CNT). The module should switch
 *              to the standby mode. */
static uint_8 accel_setLastData (const TAccelData   * poSrc,
                                 uint_32              u32WaitTicks);

//******************************************************************************
//******************************************************************************
//******************************************************************************

void accel_task (uint32_t u32InitialData)
{
  ESL_I2C_MMA845XQ_TDevice  hAccelDevice;
  ESL_I2C_MMA845XQ_TConfig  oAccelConfig;
  int_16                    ai16Data[3];
  TAccelData                oAccelData;
  _mqx_uint                 uEventWaitTicks;
  uint_32                   ret;

  // Lwevent initialization ----------------------------------------------------
  ret = _lwevent_create(&g_lwevent, LWEVENT_AUTO_CLEAR);
  if (MQX_OK != ret) {
    LOGE_FORMATTED ("_lwevent_create failed: %d", ret);
    ESL_APPCTRL_INITDONE(u32InitialData, ACCEL_LWEVENT_FAILURE);
  }

  // Lwsem initialization ------------------------------------------------------
  ret = _lwsem_create(&g_lwsem, 1);
  if (MQX_OK != ret) {
    LOGE_FORMATTED ("_lwsem_create failed: %d", ret);
    ESL_APPCTRL_INITDONE(u32InitialData, ACCEL_LWSEM_FAILURE);
  }

  // Data storage initialization -----------------------------------------------
  oAccelData.aiData[0]    = 0;
  oAccelData.aiData[1]    = 0;
  oAccelData.aiData[2]    = 0;
  oAccelData.u32Timestamp = 0;
  ret = accel_setLastData (&oAccelData, 0);
  if (ACCEL_OK != ret) {
    LOGE_FORMATTED("accel_setLastData failed: %d", ret);
    ESL_APPCTRL_INITDONE(u32InitialData, ret);
  }

  // Accelerometer initialization ----------------------------------------------
  // get default accelerometer configuration
  ret = esl_i2c_MMA845xQ_getDefaultConfig (&oAccelConfig);
  if (ESL_I2C_OK != ret) {
    LOGE_FORMATTED("esl_i2c_MMA845xQ_getDefaultConfig failed: %d", ret);
    ESL_APPCTRL_INITDONE(u32InitialData, ret);
  }

  // change the configuration: set Output Data Rate to 50 Hz
  oAccelConfig.u8CtrlReg1 &= ~ESL_I2C_MMA845XQ_CTRL_REG1_DR_MASK;
  oAccelConfig.u8CtrlReg1 |=  ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_50;
  // change the configuration: reduce Noise (limits Dynamic Range to 4g!)
  oAccelConfig.u8CtrlReg1 |=  ESL_I2C_MMA845XQ_CTRL_REG1_LNOISE_MASK;
  // change the configuration: set High Resolution mode (high oversampling -> low noise)
  oAccelConfig.u8CtrlReg2 &= ~ESL_I2C_MMA845XQ_CTRL_REG2_MODS_MASK;
  oAccelConfig.u8CtrlReg2 |=  ESL_I2C_MMA845XQ_CTRL_REG2_MODS_VAL_HI_RES;

  // open the device (and apply the configuration)
  ret = esl_i2c_MMA845xQ_open (&hAccelDevice,
                               ACCEL_MMA8451Q_CHANNEL_NO,
                               ACCEL_MMA8451Q_DRIVER_MODE,
                               ACCEL_MMA8451Q_CHANNEL_BAUDRATE,
                               ACCEL_MMA8451Q_SA0,
                               &oAccelConfig);
  if (ESL_I2C_OK != ret) {
    LOGE_FORMATTED("esl_i2c_MMA845xQ_open failed: %d", ret);
    ESL_APPCTRL_INITDONE(u32InitialData, ret);
  }

  // activate the device
  ret = esl_i2c_MMA845xQ_activate (&hAccelDevice);
  if (ESL_I2C_OK != ret) {
    LOGE_FORMATTED("esl_i2c_MMA845xQ_activate failed: %d", ret);
    ESL_APPCTRL_INITDONE(u32InitialData, ret);
  }

  ESL_APPCTRL_INITDONE(u32InitialData, MQX_OK);

  // Infinite loop -------------------------------------------------------------
  uEventWaitTicks = MSECS_TO_MQX_TICKS(ACCEL_PERIODIC_INTERVAL);
  while (1) {
    // Wait for an event
    ret = _lwevent_wait_ticks(&g_lwevent,
                              EVENT_Accel_Wakeup,
                              FALSE,
                              uEventWaitTicks);
    if (MQX_OK == ret) {                                                        // WAKEUP event received
      uEventWaitTicks = MSECS_TO_MQX_TICKS(ACCEL_PERIODIC_INTERVAL);
      LOGI_FORMATTED("Accel: Switching to READY");
    } else if (LWEVENT_WAIT_TIMEOUT != ret) {                                   // error occured
      LOGW_FORMATTED("_lwevent_wait_ticks failed: %d", ret);
      continue;
    }

    // wait timeout occured or WAKEUP event received -> get new data

    ret = esl_i2c_MMA845xQ_getRawData (ai16Data, &hAccelDevice);
    if (ESL_I2C_OK == ret) {
      ret = esl_i2c_MMA845xQ_raw2int (oAccelData.aiData, ai16Data, &hAccelDevice);
      if (ESL_I2C_OK == ret) {
        ++oAccelData.u32Timestamp;
        ret = accel_setLastData (&oAccelData,
                                 MSECS_TO_MQX_TICKS(ACCEL_LWSEM_WAIT));
        if (ACCEL_OUTDATED == ret) {
          uEventWaitTicks = ACCEL_INFINITE_INTERVAL;
          LOGI_FORMATTED("Accel: Switching to STANDBY");
        } else if (ACCEL_OK != ret) {
          LOGW_FORMATTED("accel_setLastData failed: %d", ret);
        }
      } else {
        LOGW_FORMATTED("esl_i2c_MMA845xQ_raw2int failed: %d", ret);
      }

    } else if (ESL_I2C_MMA845XQ_DATA_NOT_READY != ret) {
      LOGW_FORMATTED("esl_i2c_MMA845xQ_getRawData failed: %d", ret);
    }
  }
}

//******************************************************************************

uint_8 accel_getLastData (TAccelData  * poDst,
                          uint_32       u32WaitTicks)
{
  int ret;
  assert(poDst);

  // Retrieve the semaphore
  ret = _lwsem_wait_ticks(&g_lwsem, u32WaitTicks);
  if (ret != MQX_OK) return ACCEL_LWSEM_FAILURE;

  // CRITICIAL SECTION START //

  *poDst = g_oAccelData;
  if (g_u32MissedCnt >= ACCEL_MAX_MISSED_CNT) {
    ret = ACCEL_OUTDATED;
    _lwevent_set(&g_lwevent, EVENT_Accel_Wakeup);
  } else {
    ret = ACCEL_OK;
  }
  g_u32MissedCnt = 0;

  _lwsem_post(&g_lwsem);

  // CRITICIAL SECTION END //

  return ret;
}

//******************************************************************************
// Private functions
//******************************************************************************

static uint_8 accel_setLastData (const TAccelData   * poSrc,
                                 uint_32              u32WaitTicks)
{
  int ret;
  assert(poSrc);

  // Retrieve the semaphore
  ret = _lwsem_wait_ticks(&g_lwsem, u32WaitTicks);
  if (ret != MQX_OK) return ACCEL_LWSEM_FAILURE;

  // CRITICIAL SECTION START //

  g_oAccelData = *poSrc;
  if (g_u32MissedCnt >= ACCEL_MAX_MISSED_CNT) {
    ret = ACCEL_OUTDATED;
  } else {
    ++g_u32MissedCnt;
    ret = ACCEL_OK;
  }

  _lwsem_post(&g_lwsem);

  // CRITICIAL SECTION END //

  return ret;
}
