/** ****************************************************************************
 *
 *  @file       gpio.c
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

#define EVENT_Gpio_LedAuto              (1 << 1)                                //!< Event to set the slow LED mode.
#define EVENT_Gpio_LedOn                (1 << 2)                                //!< Event to set the LED on.
#define EVENT_Gpio_LedOff               (1 << 3)                                //!< Event to set the LED off.
#define EVENT_Gpio_LedSlow              (1 << 4)                                //!< Event to set the slow LED mode.
#define EVENT_Gpio_LedFast              (1 << 5)                                //!< Event to set the fast LED mode.

#define EVENT_Gpio_Mask_All             (EVENT_Gpio_LedAuto           | \
                                         EVENT_Gpio_LedOn             | \
                                         EVENT_Gpio_LedOff            | \
                                         EVENT_Gpio_LedSlow           | \
                                         EVENT_Gpio_LedFast           | \
                                         0)                                     //!< Mask of all events.
#define EVENT_Gpio_Mask_Mode            (EVENT_Gpio_LedOn | EVENT_Gpio_LedOff | EVENT_Gpio_LedAuto)
#define EVENT_Gpio_Mask_Speed           (EVENT_Gpio_LedSlow | EVENT_Gpio_LedFast)

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
  _mqx_uint           uSignalled  = 0;
  _mqx_uint           uState      = EVENT_Gpio_LedSlow;
  _mqx_uint           err;
  uint_8              ret;

  // Lwevent initialization ----------------------------------------------------
  ret = _lwevent_create(&g_lwEvent, 0);
  if (MQX_OK != ret) {
    LOGE_FORMATTED ("gpio_task _lwevent_create failed: %d", ret);
    ESL_APPCTRL_INITDONE(u32InitialData, GPIO_LWEVENT_CREATE_FAILURE);
  }

  _lwevent_set(&g_lwEvent, EVENT_Gpio_LedAuto);

  ESL_APPCTRL_INITDONE (u32InitialData, ret);

  // Infinite event loop -------------------------------------------------------
  while (1) {
    // Wait for an event
    ret = _lwevent_wait_ticks(&g_lwEvent,
                              EVENT_Gpio_Mask_All,
                              FALSE,
                              EVENT_Gpio_maxWait);
    if (MQX_OK != ret) {
      LOGW_FORMATTED ("gpio_task _lwevent_wait_ticks failed: %d", ret);

    } else {
      uSignalled = _lwevent_get_signalled();
      _lwevent_clear(&g_lwEvent, uSignalled);
      LOGD_FORMATTED ("gpio_task event received: %x", uSignalled);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define TD_REGISTER(domain)                                                                                 \
  ret = esl_td_registerRoutine (domain, &oLwtimer, gpio_ledToggle, NULL, &err);                             \
  if (MQX_OK != ret) LOGE_FORMATTED ("gpio_task esl_td_registerRoutine failed: %d, %d", ret, err);

#define TD_UNREGISTER()                                                                                     \
  if (uState & EVENT_Gpio_LedAuto) {                                                                        \
    ret = esl_td_unregisterRoutine (&oLwtimer, &err);                                                       \
    if (MQX_OK != ret) LOGW_FORMATTED ("gpio_task esl_td_unregisterRoutine failed: %d, %d", ret, err);      \
  }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      if (uSignalled & EVENT_Gpio_LedOn) {
        TD_UNREGISTER();
        lwgpio_set_value(&g_lwLED, LED_ON);
        uState = (uState & ~EVENT_Gpio_Mask_Mode) | EVENT_Gpio_LedOn;

      } else if (uSignalled & EVENT_Gpio_LedOff) {
        TD_UNREGISTER();
        lwgpio_set_value(&g_lwLED, LED_OFF);
        uState = (uState & ~EVENT_Gpio_Mask_Mode) | EVENT_Gpio_LedOff;

      } else if (uSignalled & EVENT_Gpio_LedAuto) {
        if (!(uState & EVENT_Gpio_LedAuto)) {
          TD_REGISTER(uState & EVENT_Gpio_LedFast ? TIMEDOMAIN_100MS : TIMEDOMAIN_250MS);
          uState = (uState & ~EVENT_Gpio_Mask_Mode) | EVENT_Gpio_LedAuto;
        }
      }

      if (uSignalled & EVENT_Gpio_LedSlow) {
        if (uState & EVENT_Gpio_LedAuto) {
          TD_UNREGISTER();
          TD_REGISTER(TIMEDOMAIN_250MS);
        }
        uState = (uState & ~EVENT_Gpio_Mask_Speed) | EVENT_Gpio_LedSlow;
      } else if (uSignalled & EVENT_Gpio_LedFast) {
        if (uState & EVENT_Gpio_LedAuto) {
          TD_UNREGISTER();
          TD_REGISTER(TIMEDOMAIN_100MS);
        }
        uState = (uState & ~EVENT_Gpio_Mask_Speed) | EVENT_Gpio_LedFast;
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

void gpio_setLedOn    (void)
{
  _lwevent_set(&g_lwEvent, EVENT_Gpio_LedOn);
}

//******************************************************************************

void gpio_setLedOff   (void)
{
  _lwevent_set(&g_lwEvent, EVENT_Gpio_LedOff);
}

//******************************************************************************

void gpio_setLedAuto  (void)
{
  _lwevent_set(&g_lwEvent, EVENT_Gpio_LedAuto);
}

//******************************************************************************
