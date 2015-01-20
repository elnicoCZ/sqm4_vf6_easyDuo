/** ****************************************************************************
 *
 *  @file       mcc.c
 *  @brief      Multicore communication task.
 *
 *  Realizes communication with the A5 core.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-11-09: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#include "mcc.h"
#include "easyduo_mcc_common.h"
#include "gpio.h"
#include "accelerometer.h"

#include "esl_appctrl.h"

#include "mcc_config.h"
#include "mcc_common.h"
#include "mcc_api.h"
#include "mcc_mqx.h"

#include <mqx.h>
#include <bsp.h>


//******************************************************************************
// Local functions
//******************************************************************************

/** Initializes MQX node of MCC.
 * @param[in] iNode   MQX node number.
 * @return    APPMGR_OK on success.
 *            APPMGR_MCC_INIT_FAILURE, APPMGR_MCC_INFO_FAILURE on failure. */
static uint_8 mcc_init (MCC_NODE iNode);

//******************************************************************************
// Globals
//******************************************************************************
static MCC_ENDPOINT g_mccEndpointLocal;                                         //!< Local EasyDuo MCC endpoint.
static MCC_ENDPOINT g_mccEndpointRemote = { MCC_ENDPOINT_A5_CORE,
                                            MCC_ENDPOINT_A5_NODE,
                                            MCC_ENDPOINT_A5_PORT };             //!< Remote EasyDuo MCC endpoint.

//******************************************************************************
//******************************************************************************
//******************************************************************************

void mcc_task (uint_32 u32InitialData)
{
  TMccMsg       * poMsg;
  TMccMsg         oMsg;
  MCC_MEM_SIZE    size;
  TAccelData      oAccelData;
  int             ret;

  ret = mcc_init (MCC_ENDPOINT_M4_NODE);
  if (MCC_OK != ret) {
    LOGE_FORMATTED ("mcc_init failed: %d", ret);
    ESL_APPCTRL_INITDONE (u32InitialData, ret);
  }

  ret = mcc_create_endpoint(&g_mccEndpointLocal, MCC_ENDPOINT_M4_PORT);
  if (MCC_SUCCESS != ret) {
    LOGE_FORMATTED("mcc_create_endpoint() failed: %d, node,port: %d, %d",
                   ret, MCC_ENDPOINT_M4_NODE, MCC_ENDPOINT_M4_PORT);
    ESL_APPCTRL_INITDONE (u32InitialData, MCC_ENDPOINT_FAILURE);
  }

  ESL_APPCTRL_INITDONE (u32InitialData, MQX_OK);

  // Infinite message loop -----------------------------------------------------
  while (1) {
    // Wait for a message
    ret = mcc_recv_nocopy(&g_mccEndpointLocal, (void**)&poMsg, &size, MCC_WAIT_INF);  // blocking call
    if (MCC_SUCCESS != ret) {
      LOGE_FORMATTED("mcc_task mcc_recv_nocopy failed: %d", ret);
      continue;
    }
    if (size != sizeof(TMccMsg)) {
      LOGE_FORMATTED("mcc_task invalid size received: %d", size);
      continue;
    }

    // Evaluate the message
    switch (poMsg->type) {

    case MCCMSG_LED_ON:
      gpio_setLedOn();
      break;

    case MCCMSG_LED_OFF:
      gpio_setLedOff();
      break;

    case MCCMSG_LED_AUTO:
      gpio_setLedAuto();
      break;

    case MCCMSG_ACCEL_DATA:
      ret = accel_getLastData (&oAccelData, MSECS_TO_MQX_TICKS(1));
      if (ACCEL_OK != ret) {
        LOGW_FORMATTED("mcc_task accel_getLastData failed: %d", ret);
        oMsg.iDataX = oMsg.iDataY = oMsg.iDataZ = 0;
      } else {
        oMsg.iDataX = oAccelData.aiData[0];
        oMsg.iDataY = oAccelData.aiData[1];
        oMsg.iDataZ = oAccelData.aiData[2];
      }
      ret = mcc_send(&g_mccEndpointRemote, &oMsg, sizeof(oMsg), 0);             // non-blocking call
      if (MCC_OK != ret) {
        LOGE_FORMATTED("mcc_task mcc_send failed: %d", ret);
      }
      break;

    default:
      LOGW_FORMATTED("mcc_task unrecognized message: %d", poMsg->type);
      break;
    }

    // Release the mcc buffer
    ret = mcc_free_buffer(poMsg);
    if (MCC_SUCCESS != ret) {
      LOGW_FORMATTED("mcc_task mcc_free_buffer failed: %d", ret);
      continue;
    }
  }
}

//******************************************************************************

static uint_8 mcc_init (MCC_NODE iNode)
{
  MCC_INFO_STRUCT   mccInfo;
  uint_32           ret;

  ret = mcc_initialize(iNode);
  if (MCC_SUCCESS != ret) {
    LOGE_FORMATTED("mcc_initialize failed: %d", ret);
    return MCC_INIT_FAILURE;
  }

  ret = mcc_get_info(iNode, &mccInfo);
  if (MCC_SUCCESS != ret) {
    LOGE_FORMATTED("mcc_get_info failed: %d", ret);
    mcc_destroy(iNode);
    return MCC_INFO_FAILURE;
  } else if (strncmp(mccInfo.version_string, MCC_VERSION_STRING, 3) != 0) {     // compare first 3 bytes (major number)
    LOGE_FORMATTED("MCC Library versions do not match ('%s' vs '%s')",
                   mccInfo.version_string, MCC_VERSION_STRING);
    mcc_destroy(iNode);
    return MCC_VERSION_FAILURE;
  } else {
    LOGI_FORMATTED("MCC version %s loaded", mccInfo.version_string);
  }

  return MCC_OK;
}

//******************************************************************************
