/** ****************************************************************************
 *
 *  @file       esl_gpio_config.h
 *  @brief      GPIO module config file
 *
 *  Default configuration of the gpio module. The settings should not be changed
 *  here but can be overridden in a project specific esl_config.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    2.1 2014-02-14: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Port 5 configuration removed.
 *
 *  @version    2.0 2014-02-13: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_gpio v2.0.
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

#ifndef ESL_GPIO_CONFIG_H_77926020520747604247400233
#define ESL_GPIO_CONFIG_H_77926020520747604247400233
//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_GPIO_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_GPIO_MODULE_ENABLE
# define ESL_GPIO_MODULE_ENABLE         (0)
#endif

//******************************************************************************
// Port A configuration
//******************************************************************************

/** @def ESL_GPIO_PORT0_ISR_SIZE
 * @brief Maximum number of ISRs to be registred for PORT A. */
#ifndef ESL_GPIO_PORT0_ISR_SIZE
# define ESL_GPIO_PORT0_ISR_SIZE        (0)
#endif

/** @def ESL_GPIO_PORT0_IRQ_PRIO
 * @brief PORT A interrupt priority (1-7; the lower number, the higher priority). */
#ifndef ESL_GPIO_PORT0_IRQ_PRIO
# define ESL_GPIO_PORT0_IRQ_PRIO        (7)
#endif

//******************************************************************************
// Port B configuration
//******************************************************************************

/** @def ESL_GPIO_PORT1_ISR_SIZE
 * @brief Maximum number of ISRs to be registred for PORT B. */
#ifndef ESL_GPIO_PORT1_ISR_SIZE
# define ESL_GPIO_PORT1_ISR_SIZE        (0)
#endif

/** @def ESL_GPIO_PORT1_IRQ_PRIO
 * @brief PORT B interrupt priority (1-7; the lower number, the higher priority). */
#ifndef ESL_GPIO_PORT1_IRQ_PRIO
# define ESL_GPIO_PORT1_IRQ_PRIO        (7)
#endif

//******************************************************************************
// Port C configuration
//******************************************************************************

/** @def ESL_GPIO_PORT2_ISR_SIZE
 * @brief Maximum number of ISRs to be registred for PORT C. */
#ifndef ESL_GPIO_PORT2_ISR_SIZE
# define ESL_GPIO_PORT2_ISR_SIZE        (0)
#endif

/** @def ESL_GPIO_PORT2_IRQ_PRIO
 * @brief PORT C interrupt priority (1-7; the lower number, the higher priority). */
#ifndef ESL_GPIO_PORT2_IRQ_PRIO
# define ESL_GPIO_PORT2_IRQ_PRIO        (7)
#endif

//******************************************************************************
// Port D configuration
//******************************************************************************

/** @def ESL_GPIO_PORT3_ISR_SIZE
 * @brief Maximum number of ISRs to be registred for PORT D. */
#ifndef ESL_GPIO_PORT3_ISR_SIZE
# define ESL_GPIO_PORT3_ISR_SIZE        (0)
#endif

/** @def ESL_GPIO_PORT3_IRQ_PRIO
 * @brief PORT D interrupt priority (1-7; the lower number, the higher priority). */
#ifndef ESL_GPIO_PORT3_IRQ_PRIO
# define ESL_GPIO_PORT3_IRQ_PRIO        (7)
#endif

//******************************************************************************
// Port E configuration
//******************************************************************************

/** @def ESL_GPIO_PORT4_ISR_SIZE
 * @brief Maximum number of ISRs to be registred for PORT E. */
#ifndef ESL_GPIO_PORT4_ISR_SIZE
# define ESL_GPIO_PORT4_ISR_SIZE        (0)
#endif

/** @def ESL_GPIO_PORT4_IRQ_PRIO
 * @brief PORT E interrupt priority (1-7; the lower number, the higher priority). */
#ifndef ESL_GPIO_PORT4_IRQ_PRIO
# define ESL_GPIO_PORT4_IRQ_PRIO        (7)
#endif

//******************************************************************************
#endif /* ESL_GPIO_CONFIG_H_77926020520747604247400233 */
