/** ****************************************************************************
 *
 *  @file       startup.c
 *  @brief      Startup Task.
 *
 *  This task initializes application modules and goes to the BLOCK state.
 *  It's intended to be created at the application start before all other
 *  modules.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    1.0 2014-06-15: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Initial version.
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

#include "startup.h"
#include "gpio.h"

#include "esl_appctrl.h"
#include "esl_td.h"
#include "esl_keyboard.h"
#include "esl_log.h"

#include <mqx.h>
#include <bsp.h>

//******************************************************************************
// LED
//******************************************************************************

#define LED_PIN                         (BSP_LED1)                              //!< LED pin assignment
#define LED_MUX_GPIO                    (BSP_LED1_MUX_GPIO)                     //!< LED gpio multiplexor functionality

/** @var LWGPIO_STRUCT g_lwLED
 * @brief Lightweight GPIO object for LED. */
LWGPIO_STRUCT g_lwLED;

//******************************************************************************
// Time Domains
//******************************************************************************
/** @var esl_td_timeDomain esl_td_aoTimeDomain[ESL_TD_DOMAINCNT]
 * @brief Definition of time domains. The variable is used by the esl_td
 * module. */
esl_td_timeDomain esl_td_aoTimeDomain[ESL_TD_DOMAINCNT] = {
  {.uiPeriod=10, .uiStartupDelay=100},
  {.uiPeriod=100, .uiStartupDelay=100},
  {.uiPeriod=250, .uiStartupDelay=100},
};

//******************************************************************************
// Keyboard
//******************************************************************************

/** @var esl_keyboard_key esl_keyboard_aoKeys[ESL_KEYBOARD_KEYCNT]
 * @brief Definition of keyboard. The variable is used by the esl_keyboard
 * module. */
esl_keyboard_key esl_keyboard_aoKeys[ESL_KEYBOARD_KEYCNT] = {
  {BSP_SW1, BSP_SW1_MUX_GPIO, LWGPIO_ATTR_PULL_UP, gpio_buttonEvent, KEYID_EASYBUTTON},
};

//******************************************************************************
// Startup Task
//******************************************************************************

void startup_task (uint32_t u32InitialData)
{
  uint_8      ret;
  _mqx_uint   err;

  // Initialize the LED output and set it to OFF at start
  if (!lwgpio_init (&g_lwLED, LED_PIN, LWGPIO_DIR_OUTPUT, LED_OFF)) {
    LOGW_STR ("startup lwgpio_init failed");
  }
  lwgpio_set_functionality (&g_lwLED, LED_MUX_GPIO);

  // Create time domains
  ret = esl_td_init (0, ARRAY_SIZE(esl_td_aoTimeDomain)-1, &err);
  if (ret != ESL_TD_OK) {
    LOGE_FORMATTED ("startup esl_td_init failed: %d, %d", ret, err);
  }

  // Initialize keyboard, which is based on time domain TIMEDOMAIN_10MS
  ret = esl_keyboard_init (TIMEDOMAIN_10MS, &err);
  if (ret != ESL_KEYBOARD_OK)
  {
    LOGE_FORMATTED ("esl_keyboard_init failed: %d, %d", ret, err);
  }

  // To signalize that startup process is complete
  ESL_APPCTRL_INITDONE (u32InitialData, MQX_OK);

  _task_destroy(MQX_NULL_TASK_ID);
}

//******************************************************************************
#undef ESL_LOG_FILEID
