/** ****************************************************************************
 *
 *  @file       esl_appctrl_config.h
 *  @brief      ESL application control module config file
 *
 *  Default configuration of the APPCTRL module. The settings should not be
 *  changed here but can be overridden in a project specific esl_config.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.2 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.1 2013-12-13: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_appctrl v1.1.
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

#ifndef ESL_APPCTRL_CONFIG_H_14265041265710655410401232
#define ESL_APPCTRL_CONFIG_H_14265041265710655410401232
//******************************************************************************

#include "esl_config.h"

#include <mqx.h>

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_APPCTRL_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_APPCTRL_MODULE_ENABLE
# define ESL_APPCTRL_MODULE_ENABLE      (0)
#endif

//******************************************************************************
// Task eslAppctrl information
//******************************************************************************

/** @def ESL_APPCTRL_TASK_STACK
 * @brief eslAppctrl task stack size. */
#ifndef ESL_APPCTRL_TASK_STACK
# define ESL_APPCTRL_TASK_STACK         (2000)
#endif

/** @def ESL_APPCTRL_TASK_STR
 * @brief eslAppctrl task name - should be unique! */
#ifndef ESL_APPCTRL_TASK_STR
# define ESL_APPCTRL_TASK_STR           "eslAppCtrl"
#endif

/** @def ESL_APPCTRL_TASK_PRIO
 * @brief eslAppctrl task priority. */
#ifndef ESL_APPCTRL_TASK_PRIO
# define ESL_APPCTRL_TASK_PRIO          (20)
#endif

//******************************************************************************
// InitDone function declaration
//******************************************************************************

#ifndef ESL_APPCTRL_INITDONE
/** Function called by every task created by ESL when its initialization
 *  is complete. User has to implement function esl_appctrl_initDone() or define
 *  it otherwise in esl_config.h. The purpose of this function is to notify the
 *  main task about the initialization success of the task being created.
 * @param[in] u32InitialData    Task initial data.
 * @param[in] u32InitRetCode    Return code of the initialization.
 *                              MQX_OK for success, other values for failure. */
# define ESL_APPCTRL_INITDONE(u32InitialData, u32InitRetCode) \
                              esl_appctrl_initDone(u32InitialData, u32InitRetCode)
extern void esl_appctrl_initDone (uint_32 u32InitialData, uint_32 u32InitRetCode);
#endif // ESL_APPCTRL_INITDONE //

//******************************************************************************
// Message queue settings
//******************************************************************************

/** @def ESL_APPCTRL_MSGQ_SIZE
 * @brief Main message queue size (set 0 to unlimited). */
#ifndef ESL_APPCTRL_MSGQ_SIZE
# define ESL_APPCTRL_MSGQ_SIZE          (3)
#endif

/** @def ESL_APPCTRL_MSGQ_TIME2WAITLOOP
 * @brief Main message queue's time to wait at loop phase in MQX ticks.
 *        Set 0 to unlimited wait. */
#ifndef ESL_APPCTRL_MSGQ_TIME2WAITLOOP
# define ESL_APPCTRL_MSGQ_TIME2WAITLOOP (0)
#endif

/** @def ESL_APPCTRL_MSGQ_TIME2WAITINIT
 * @brief Main message queue's time to wait at init phase in MQX ticks.
 *        Set 0 to unlimited wait. */
#ifndef ESL_APPCTRL_MSGQ_TIME2WAITINIT
# define ESL_APPCTRL_MSGQ_TIME2WAITINIT (0)
#endif

//******************************************************************************
#endif /* ESL_APPCTRL_CONFIG_H_14265041265710655410401232 */
