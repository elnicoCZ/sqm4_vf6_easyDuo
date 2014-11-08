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

#ifndef GPIO_H_093762096020765648966451020
#define GPIO_H_093762096020765648966451020
//******************************************************************************
#include <mqx.h>
#include <bsp.h>
#if (MQX_VERSION >= 410)
# include "psptypes_legacy.h"
#endif

//******************************************************************************
// Task information

#define GPIO_TASKSTACK                  1500                                    //!< Task stack
#define GPIO_TASKNAME                   "gpio"                                  //!< Task Name - should be unique

// NOTE: Task start strategy and priority is application dependent and that's
//       why it shouldn't be defined here, but in an application configuration!

//******************************************************************************

/** GPIO (LED) control task.
 * @param [in] initialData Task initial data. */
void gpio_task (uint_32 u32InitialData);

/** This function is called as the keyboard callback from the esl_keyboard
 *  module.
 * @param [in] u8Event  Press/Release/Hold.
 * @param [in] u8KeyId  Key identifier. Specified in esl_keyboard_aoKeys[]. */
void gpio_buttonEvent (uint_8 u8Event, uint_8 u8KeyId);

//******************************************************************************
#endif // GPIO_H_093762096020765648966451020 //
