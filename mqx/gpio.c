/** ****************************************************************************
 *
 *  @file       gpio.h
 *  @brief      GPIO control task.
 *
 *  Control task for EasyBoard GPIO.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-11-07: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#include "gpio.h"
#include "startup.h"

#include "esl_appctrl.h"
#include "esl_keyboard.h"
#include "esl_td.h"

#include <mqx.h>
#include <bsp.h>
#include <lwgpio.h>
#include <lwevent.h>


//******************************************************************************
// Lwevent communication interface
//******************************************************************************

#define EVENT_Gpio_maxWait              (0)                                     //!< Maximal time in ticks to wait for the incoming events. Use 0 for infinity.

#define EVENT_Gpio_LedSlow              (1 << 0)                                //!< Event to set the slow LED mode.
#define EVENT_Gpio_LedFast              (1 << 1)                                //!< Event to set the fast LED mode.

#define EVENT_Gpio_All                  (EVENT_Gpio_LedSlow           | \
                                         EVENT_Gpio_LedFast           | \
                                         0)                                     //!< Mask of all events.
#define EVENT_Gpio_Mask                 (EVENT_Gpio_All)                        //!< Mask of all events.

//******************************************************************************
// Function prototypes
//******************************************************************************

static void gpio_ledToggle (void * param);

//******************************************************************************
// Globals
//******************************************************************************

static LWEVENT_STRUCT g_lwEvent;

//******************************************************************************
//******************************************************************************
//******************************************************************************

void gpio_task (uint_32 u32InitialData)
{
  LWTIMER_STRUCT      oLwtimer;
  _mqx_uint           uSignalled = 0;
  _mqx_uint           err;
  uint_8              ret;

  // Lwevent initialization ----------------------------------------------------
  ret = _lwevent_create(&g_lwEvent, 0);
  if (MQX_OK != ret) {
    LOGE_FORMATTED ("gpio_task _lwevent_create failed: %d", ret);
    ESL_APPCTRL_INITDONE(u32InitialData, 1);
  }

  // Time-domain registration --------------------------------------------------
  ret = esl_td_registerRoutine (TIMEDOMAIN_250MS, &oLwtimer, gpio_ledToggle, NULL, &err);
  if (MQX_OK != ret) {
    LOGE_FORMATTED ("gpio_task esl_td_registerRoutine failed: %d, %d", ret, err);
    ESL_APPCTRL_INITDONE(u32InitialData, 2);
  }

  ESL_APPCTRL_INITDONE (u32InitialData, ret);

  // Infinite event loop -------------------------------------------------------
  while (1) {
    // Wait for an event
    ret = _lwevent_wait_ticks(&g_lwEvent,
                              EVENT_Gpio_All,
                              FALSE,
                              EVENT_Gpio_maxWait);
    if (MQX_OK != ret) {
      LOGW_FORMATTED ("gpio_task _lwevent_wait_ticks failed: %d", ret);

    } else {
      uSignalled = _lwevent_get_signalled();
      _lwevent_clear(&g_lwEvent, uSignalled);
      LOGD_FORMATTED ("gpio_task event received: %x", uSignalled);

      if (uSignalled & EVENT_Gpio_LedSlow) {
        ret = esl_td_unregisterRoutine (&oLwtimer, &err);
        if (MQX_OK != ret) LOGW_FORMATTED ("gpio_task esl_td_unregisterRoutine failed: %d, %d", ret, err);
        ret = esl_td_registerRoutine (TIMEDOMAIN_250MS, &oLwtimer, gpio_ledToggle, NULL, &err);
        if (MQX_OK != ret) LOGE_FORMATTED ("gpio_task esl_td_registerRoutine failed: %d, %d", ret, err);

      } else if (uSignalled & EVENT_Gpio_LedFast) {
        ret = esl_td_unregisterRoutine (&oLwtimer, &err);
        if (MQX_OK != ret) LOGW_FORMATTED ("gpio_task esl_td_unregisterRoutine failed: %d, %d", ret, err);
        ret = esl_td_registerRoutine (TIMEDOMAIN_100MS, &oLwtimer, gpio_ledToggle, NULL, &err);
        if (MQX_OK != ret) LOGE_FORMATTED ("gpio_task esl_td_registerRoutine failed: %d, %d", ret, err);

      } else {
        LOGW_FORMATTED ("gpio_task unrecognized event");
      }
    }
  }
}

//******************************************************************************

void gpio_buttonEvent (uint_8 u8Event, uint_8 u8KeyId)
{
  LOGD_FORMATTED ("gpio_buttonEvent %d, %d", u8Event, u8KeyId);

  if (KEYID_EASYBUTTON == u8KeyId) {
    switch (u8Event) {
    case ESL_KEYBOARD_EVENT_PRESS   : _lwevent_set(&g_lwEvent, EVENT_Gpio_LedFast); break;
    case ESL_KEYBOARD_EVENT_RELEASE : _lwevent_set(&g_lwEvent, EVENT_Gpio_LedSlow); break;
    default                         : break;
    }
  }
}

//******************************************************************************

static void gpio_ledToggle (void * param)
{
  (void)param;
  lwgpio_toggle_value(&g_lwLED);
}

//******************************************************************************
