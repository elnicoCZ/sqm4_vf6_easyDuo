/** ****************************************************************************
 *
 *  @file       esl_keyboard.h
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

#ifndef ESL_KEYBOARD_H_54423115487894321321547561
#define ESL_KEYBOARD_H_54423115487894321321547561

//******************************************************************************

#include "esl_keyboard_config.h"

//******************************************************************************

// Module specific log IDs
enum {
  ESL_KEYBOARD_OK = MQX_OK,
  ESL_KEYBOARD_LWGPIO_INIT,
  ESL_KEYBOARD_INVALID_ARGUMENT,
  ESL_KEYBOARD_MODULE_OFF
};

//******************************************************************************

// Callback event types
enum {
  ESL_KEYBOARD_EVENT_PRESS    = 1,
  ESL_KEYBOARD_EVENT_RELEASE  = 2,
  ESL_KEYBOARD_EVENT_HOLD     = 3
};

//******************************************************************************

/** Key structure. */
typedef struct {
  uint_32  u32Pin;                       //!< CPU pin, at which the button is connected.
  uint_32  u32Mux;                       //!< LWGPIO mux to set for the lwGpio.
  uint_32  u32Attr;                      //!< LWGPIO attributes to set for the lwGpio.
  void     (*pfCallback)(uint_8,uint_8); //!< Pointer to the key callback function with 2 parameters (event type, keyID).
  uint_8   u8KeyId;                      //!< Key Identifier (typically shall be unique).
} esl_keyboard_key;

//******************************************************************************

/** @var esl_keyboard_key esl_keyboard_aoKeys[ESL_KEYBOARD_KEYCNT]
 * @brief The array of keys is supposed to be defined by the application. Also -
 * the ESL_KEYBOARD_KEYCNT macro shall be adjusted accordingly with every
 * redefinition of this variable. */
extern esl_keyboard_key esl_keyboard_aoKeys[ESL_KEYBOARD_KEYCNT];

//******************************************************************************

/** Call this function to initialize the handling of keys specified in
 * esl_keyboard_aoKeys[].
 * @param [in]  u8TimeDomain  Index of the time domain (esl_td), in which the
 *                            keyboard handler shall operate. Typically the
 *                            10 msec time domain shall be used.
 * @param [out] err           Value adjusted in case of failure by commands
 *                            embedded in the function.
 * @return                    ESL_KEYBOARD_OK on success, other value on
 *                            failure. */
uint_8 esl_keyboard_init (uint_8 u8TimeDomain, _mqx_uint * err);

/** Call this function to deinitialize the handling of keys specified in
 * esl_keyboard_aoKeys[].
 * @param [out] err    Value adjusted in case of failure by commands embedded in
 *                     the function.
 * @return             ESL_KEYBOARD_OK on success, other value on failure. */
uint_8 esl_keyboard_deinit (_mqx_uint *err);

/** Retrieves current state of given key.
 * @param[out]  plwValue  ESL_KEYBOARD_BUTTON_PRESSED or ESL_KEYBOARD_BUTTON_RELEASED
 *                        is stored here.
 * @param[in]   u8KeyId   Key identifier.
 * @return                ESL_KEYBOARD_OK on success.
 *                        ESL_KEYBOARD_INVALID_ARGUMENT if NULL or invalid key
 *                        ID given. */
uint_8 esl_keyboard_getState (LWGPIO_VALUE * plwValue, uint_8 u8KeyId);

//******************************************************************************
#endif // ESL_KEYBOARD_H_54423115487894321321547561
