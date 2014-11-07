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

#include "easyDuo.h"
#include "i2cs.h"

#include "esl_appctrl.h"
#include "esl_i2c_MMA845xQ.h"

#include <mqx.h>
#include <bsp.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************

void tskAccel (uint_32 initialData)
{
  ESL_I2C_MMA845XQ_TDevice  hAccelDevice;
  ESL_I2C_MMA845XQ_TConfig  oAccelConfig;
  int_16                    ai16Data[3];
  float                     afData[3];
  uint_8                    u8DeviceId;
  uint_8                    ret;

  // get default accelerometer configuration
  ret = esl_i2c_MMA845xQ_getDefaultConfig (&oAccelConfig);
  if (ESL_I2C_OK != ret) {
    LOGE_FORMATTED("esl_i2c_MMA845xQ_getDefaultConfig failed: %d", ret);
    ESL_APPCTRL_INITDONE(initialData, ret);
  }

  // change the configuration: set Output Data Rate to 6.25 Hz
  oAccelConfig.u8CtrlReg1 &= ~ESL_I2C_MMA845XQ_CTRL_REG1_DR_MASK;
  oAccelConfig.u8CtrlReg1 |=  ESL_I2C_MMA845XQ_CTRL_REG1_DR_VAL_6_25;
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
    ESL_APPCTRL_INITDONE(initialData, ret);
  }

  // activate the device
  ret = esl_i2c_MMA845xQ_activate (&hAccelDevice);
  if (ESL_I2C_OK != ret) {
    LOGE_FORMATTED("esl_i2c_MMA845xQ_activate failed: %d", ret);
    ESL_APPCTRL_INITDONE(initialData, ret);
  }

  ESL_APPCTRL_INITDONE(initialData, MQX_OK);
  // ------------------ END OF INIT ------------------ //

  // print device type
  ret = esl_i2c_MMA845xQ_getDeviceId (&u8DeviceId, &hAccelDevice);
  if (ESL_I2C_OK != ret) {
    LOGW_FORMATTED("esl_i2c_MMA845xQ_getDeviceId failed: %d", ret);
  } else {
    switch (u8DeviceId) {
    case ESL_I2C_MMA8451Q_DEVICE_ID: LOGI_STR("Detected type: MMA8451Q"); break;
    case ESL_I2C_MMA8452Q_DEVICE_ID: LOGI_STR("Detected type: MMA8452Q"); break;
    case ESL_I2C_MMA8453Q_DEVICE_ID: LOGI_STR("Detected type: MMA8453Q"); break;
    default:
      LOGW_FORMATTED("Unrecognized type: %d", u8DeviceId);
      break;
    }
  }

  while (1) {
    // We must poll here, as R59 is not placed on EasyBoard by default,
    // disallowing to use the interrupt from the accelerometer's INT1 signal.
    // The delay is set so that every second call to getRawData should fail.
    _time_delay(80);
    ret = esl_i2c_MMA845xQ_getRawData (ai16Data, &hAccelDevice);
    if (ESL_I2C_MMA845XQ_DATA_NOT_READY == ret) {
      //LOGI_STR("esl_i2c_MMA845xQ_getRawData: NO DATA");
      continue;
    } else if (ESL_I2C_OK != ret) {
      LOGW_FORMATTED("esl_i2c_MMA845xQ_getRawData failed: %d", ret);
    } else {
      LOGI_FORMATTED("RAW: % 5d, % 5d, % 5d",
                     ai16Data[0], ai16Data[1], ai16Data[2]);
      ret = esl_i2c_MMA845xQ_raw2g (afData, ai16Data, &hAccelDevice);
    }
    if (ESL_I2C_OK != ret) {
      LOGW_FORMATTED("esl_i2c_MMA845xQ_raw2g failed: %d", ret);
    } else {
      ret = esl_i2c_MMA845xQ_raw2int (ai16Data, ai16Data, &hAccelDevice);
    }
    if (ESL_I2C_OK != ret) {
      LOGW_FORMATTED("esl_i2c_MMA845xQ_raw2int failed: %d", ret);
    } else {
      LOGI_FORMATTED("x=% .4f, y=% .4f, z=% .4f (% 5d, % 5d, % 5d)",
                     afData[0], afData[1], afData[2],
                     ai16Data[0], ai16Data[1], ai16Data[2]);
    }
  }

#pragma diag_suppress=Pe111                                                     // Warning[Pe111]: statement is unreachable
  // this code should be never reached, but this is how the device can be closed
  ret = esl_i2c_MMA845xQ_close (&hAccelDevice);
  if (ESL_I2C_OK != ret) LOGW_FORMATTED("esl_i2c_MMA845xQ_close failed: %d", ret);
#pragma diag_default=Pe111
}

//******************************************************************************
