/** ****************************************************************************
 *
 *  @file       esl_keyboard_config.h
 *  @brief      Configurable keyboard module.
 *
 *  This module provides a configurable keyboard to every application. To get it
 *  the client (application) must define its array of keys in the following
 *  global variable: esl_td_keyboard esl_keyboard_aoKeys[]. The number of keys
 *  must match to ESL_KEYBOARD_KEYCNT. If more/less keys are needed, then this
 *  macro shall be updated accordingly. This module is dependent on the esl_td
 *  module. Typically a 10 msec time domain is suitable for keyboard.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *
 *  @version    1.2 2014-09-16: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              getState function added.
 *
 *  @version    1.1 2014-03-04: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Press/Release/Hold extension.
 *
 *  @version    1.0 2014-03-02: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Integrated to ESL from the NS150 project.
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

#ifndef ESL_KEYBOARD_CONFIG_H_46543215786132165785642451
#define ESL_KEYBOARD_CONFIG_H_46543215786132165785642451

//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_KEYBOARD_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_KEYBOARD_MODULE_ENABLE
# define ESL_KEYBOARD_MODULE_ENABLE           (0)
#endif

/** @def ESL_KEYBOARD_KEYCNT
 * @brief Number of keys in the keyboard. This value shall be adapted whenever
 * the esl_keyboard_aoKeys array is redefined. */
#ifndef ESL_KEYBOARD_KEYCNT
# define ESL_KEYBOARD_KEYCNT                  (1)
#endif

/** @def ESL_KEYBOARD_CALLBACK_ON_PRESS
 * @brief If to generate a callback on a key press or not. */
#ifndef ESL_KEYBOARD_CALLBACK_ON_PRESS
# define ESL_KEYBOARD_CALLBACK_ON_PRESS       (1)
#endif

/** @def ESL_KEYBOARD_CALLBACK_ON_RELEASE
 * @brief If to generate a callback on a key release or not. */
#ifndef ESL_KEYBOARD_CALLBACK_ON_RELEASE
# define ESL_KEYBOARD_CALLBACK_ON_RELEASE     (0)
#endif

/** @def ESL_KEYBOARD_CALLBACK_ON_HOLD
 * @brief If to generate a callback on a key hold or not. */
#ifndef ESL_KEYBOARD_CALLBACK_ON_HOLD
# define ESL_KEYBOARD_CALLBACK_ON_HOLD        (0)
#endif

/** @def ESL_KEYBOARD_HOLD_TIME
 * @brief The time, after which the hold callback is generated, is determined by
 * ESL_KEYBOARD_HOLD_TIME * (time domain period). */
#ifndef ESL_KEYBOARD_HOLD_TIME
# define ESL_KEYBOARD_HOLD_TIME               (50)
#endif

/** @def ESL_KEYBOARD_BUTTON_PRESSED
 * @brief Mapping of the button pressed state to the LWGPIO pin level. */
#ifndef ESL_KEYBOARD_BUTTON_PRESSED
# define ESL_KEYBOARD_BUTTON_PRESSED          (LWGPIO_VALUE_LOW)
#endif

/** @def ESL_KEYBOARD_BUTTON_RELEASED
 * @brief Mapping of the button released state to the LWGPIO pin level. */
#ifndef ESL_KEYBOARD_BUTTON_RELEASED
# define ESL_KEYBOARD_BUTTON_RELEASED         (LWGPIO_VALUE_HIGH)
#endif

//******************************************************************************

#endif // ESL_KEYBOARD_CONFIG_H_46543215786132165785642451
