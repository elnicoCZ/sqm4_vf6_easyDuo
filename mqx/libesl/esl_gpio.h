/** ****************************************************************************
 *
 *  @file       esl_gpio.h
 *  @brief      GPIO module
 *
 *  Vybrid's interrupt vector table can store only one service routine pointer
 *  per each GPIO port. To allow for correct function of independently registred
 *  interrupts from different modules, a kind of ISR demultiplexer (translation
 *  table) is needed. It is provided by this module.
 *
 *  Only Vybrid VF6 is supported.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    2.1 2014-02-14: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Unhandled interrupts masking out fixed (#96).
 *                              ISR argument passing added.
 *
 *  @version    2.0 2014-02-13: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Integrated into ESL from the gpioIsrDemux module
 *                              (project birdhouse).
 *
 *  @version    1.0 2013-10-12: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision.
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

#ifndef ESL_GPIO_H_59347581890437698725023587
#define ESL_GPIO_H_59347581890437698725023587
//******************************************************************************

#include "esl_gpio_config.h"

#include <mqx.h>
#include <bsp.h>
#include <lwgpio.h>

//******************************************************************************
// Platform check - available for VF6 only
//******************************************************************************

#if ESL_GPIO_MODULE_ENABLE && (MQX_CPU != PSP_CPU_VF65GS10_M4)
# if !ESL_GPIO_WIGNORE_MODULE_DISABLED
#   warning "GPIO module is only available for Vybrid VF6 CPU core M4"
# endif // !ESL_GPIO_IGNORE_MODULE_DISABLED_WARNING //
# undef ESL_GPIO_MODULE_ENABLE
# define ESL_GPIO_MODULE_ENABLE         (0)
#endif // ESL_MCFS_MODULE_ENABLE && !VF6 //

//******************************************************************************
// Module return values
//******************************************************************************

enum {
  ESL_GPIO_OK = MQX_OK,
  ESL_GPIO_NULL_PTR,
  ESL_GPIO_INVALID_PORT_NUMBER,
  ESL_GPIO_MEMORY_FULL,
  ESL_GPIO_ISR_INSTALL_FAILURE,
  ESL_GPIO_BSP_INT_INIT_FAILURE,
};

//******************************************************************************
// Public functions
//******************************************************************************

/** Registers an interrupt service routine to be called when a GPIO interrupt occurs.
 * @param[in] pHandle   GPIO to register its ISR.
 * @param[in] isr       Interrupt service routine callback function.
 * @param[in] arg       Callback function argument.
 * @return              ESL_GPIO_OK on success.
 *                      ESL_GPIO_NULL_PTR if pHandle is NULL.
 *                      ESL_GPIO_INVALID_PORT_NUMBER if pHandle refers to invalid port number.
 *                      ESL_GPIO_MEMORY_FULL if the translation table for particular port is full.
 *                        Enlarge its size by modifying corresponding GPIO_PORTx_ISR_SIZE value.
 *                      ESL_GPIO_ISR_INSTALL_FAILURE if registration of hidden ISR function
 *                        by _int_install_isr() fails. */
uint_8 esl_gpio_isrRegister (LWGPIO_STRUCT  * pHandle,
                             void          (* isr) (void *),
                             void           * arg);

//******************************************************************************
#endif // GPIO_ISR_DEMUX_H_59347581890437698725023587 //
