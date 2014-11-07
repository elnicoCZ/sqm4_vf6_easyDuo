/** ****************************************************************************
 *
 *  @file       esl_appctrl.h
 *  @brief      ESL application control module
 *
 *  Entry point of the ESL library. Consists of the tskAppCtrl task, which is
 *  basically a simple control process supposed to start/stop/check other
 *  application tasks.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    1.2 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.1 2013-12-13: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Appctrl modularized and integrated into ESL.
 *
 *  @version    1.0 2013-01-09: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Initial revision - generic application
 *                              initialization integrated.
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

#ifndef ESL_APPCTRL_H_09238576701983203758762345
#define ESL_APPCTRL_H_09238576701983203758762345
//******************************************************************************

#include "esl_appctrl_config.h"
#include "esl_log.h"
#include "esl_sd.h"
#include "esl_usbhmsd.h"

//******************************************************************************
// Message queue
//******************************************************************************

/** Task queue gatekeeper message */
typedef struct {
  uint_32 u32Id;     //!< Message ID
  uint_32 u32Data;   //!< Message data
} ESL_APPCTRL_TTaskMsg;

//******************************************************************************
// Task initialization structure
//******************************************************************************

/** Additional data to the MQX Task Template. */
typedef struct {
  _task_id              sysID;                              //!< Task system ID (return value of _task_create)
} ESL_APPCTRL_TTaskData;

//******************************************************************************
// Messaging definitions
//******************************************************************************

// General task initial data masks
#define ESL_APPCTRL_TASKINIT_MASK       0x0F00                                  //!< Mask for task init constants.
#define ESL_APPCTRL_MSGID_MASK          0x00FF                                  //!< Mask for message IDs, that should be sent back to the main task.

// Task init constants
#define ESL_APPCTRL_HANDLETASK          0x0100                                  //!< Flag, that task is to be handled (started and controlled) by ESL. Otherwise ESL ignores the task.
#define ESL_APPCTRL_BLOCKONREADY        0x0200                                  //!< Flag, that task should block itself when it's ready (initialized).
#define ESL_APPCTRL_SENDMSGONREADY      0x0400                                  //!< Flag, that task should send a message when it's ready (initialized).
#define ESL_APPCTRL_QUITAPPONFAILURE    0x0800                                  //!< Flag, that application (!) should quit when the task initialization fails.

//******************************************************************************
// ESL module inclusion templates
//******************************************************************************

// APPCTRL ---------------------------------------------------------------------
#if ESL_APPCTRL_MODULE_ENABLE
# define ESL_APPCTRL_TASKID_ADD_APPCTRL() ESL_APPCTRL_TASKID_ADD(ESL_TASKID_APPCTRL)
# define ESL_APPCTRL_TEMPLATE_ADD_APPCTRL_RAW(taskid,pri,attrs) \
            ESL_APPCTRL_TEMPLATE_ADD_STD(taskid, \
                                         esl_appctrl_task, \
                                         ESL_APPCTRL_TASK_STACK, \
                                         pri, \
                                         ESL_APPCTRL_TASK_STR, \
                                         attrs)

/** @def ESL_APPCTRL_TEMPLATE_ADD_APPCTRL(pri, attrs)
 * @brief Declares the eslAppCtrl task to the TASK_TEMPLATE_STRUCT structure.
 * @param[in] pri       Task priority. Default 20.
 * @param[in] attrs     Task attributes. Use MQX_AUTO_START_TASK to start
 *                       the task automatically by MQX. Use 0 if you want to
 *                       start the task manually. */
# define ESL_APPCTRL_TEMPLATE_ADD_APPCTRL(pri,attrs) \
            ESL_APPCTRL_TEMPLATE_ADD_APPCTRL_RAW(ESL_TASKID_APPCTRL, pri, attrs)

#else // ESL_APPCTRL_MODULE_ENABLE //
# define ESL_APPCTRL_TASKID_ADD_APPCTRL()                   // do not add
#endif // ESL_APPCTRL_MODULE_ENABLE //

// LOG -------------------------------------------------------------------------
#if ESL_LOG_MODULE_ENABLE
# define ESL_APPCTRL_TASKID_ADD_LOG()  ESL_APPCTRL_TASKID_ADD(ESL_TASKID_LOG)
# define ESL_APPCTRL_MSGID_ADD_LOG()   ESL_APPCTRL_MSGID_ADD(ESL_MSGID_LOG_TASK_READY)
# define ESL_APPCTRL_TEMPLATE_ADD_LOG_RAW(taskid,pri,attrs) \
            ESL_APPCTRL_TEMPLATE_ADD_ESL(taskid, \
                                         esl_log_task, \
                                         ESL_LOG_TASK_STACK, \
                                         pri, \
                                         ESL_LOG_TASK_STR, \
                                         attrs)

/** @def ESL_APPCTRL_TEMPLATE_ADD_LOG(pri)
 * @brief Declares the eslLog task to the TASK_TEMPLATE_STRUCT structure.
 * @param[in] pri       Task priority. */
# define ESL_APPCTRL_TEMPLATE_ADD_LOG(pri) \
            ESL_APPCTRL_TEMPLATE_ADD_LOG_RAW(ESL_TASKID_LOG, \
                                             pri, \
                                             ESL_APPCTRL_SENDMSGONREADY | ESL_APPCTRL_QUITAPPONFAILURE | ESL_MSGID_LOG_TASK_READY)

#else // ESL_LOG_MODULE_ENABLE //
# define ESL_APPCTRL_TASKID_ADD_LOG()                       // do not add
# define ESL_APPCTRL_MSGID_ADD_LOG()                        // do not add
#endif // ESL_LOG_MODULE_ENABLE //

// SD --------------------------------------------------------------------------
#if ESL_SD_MODULE_ENABLE
# define ESL_APPCTRL_TASKID_ADD_SD()  ESL_APPCTRL_TASKID_ADD(ESL_TASKID_SD)
# define ESL_APPCTRL_MSGID_ADD_SD()   ESL_APPCTRL_MSGID_ADD(ESL_MSGID_SD_TASK_READY)
# define ESL_APPCTRL_TEMPLATE_ADD_SD_RAW(taskid,pri,attrs) \
            ESL_APPCTRL_TEMPLATE_ADD_ESL(taskid, \
                                         esl_sd_task, \
                                         ESL_SD_TASK_STACK, \
                                         pri, \
                                         ESL_SD_TASK_STR, \
                                         attrs)

/** @def ESL_APPCTRL_TEMPLATE_ADD_SD(pri)
 * @brief Declares the eslLog task to the TASK_TEMPLATE_STRUCT structure.
 * @param[in] pri       Task priority. */
# define ESL_APPCTRL_TEMPLATE_ADD_SD(pri) \
            ESL_APPCTRL_TEMPLATE_ADD_SD_RAW(ESL_TASKID_SD, \
                                            pri, \
                                            ESL_APPCTRL_SENDMSGONREADY | ESL_APPCTRL_QUITAPPONFAILURE | ESL_MSGID_SD_TASK_READY)

#else // ESL_SD_MODULE_ENABLE //
# define ESL_APPCTRL_TASKID_ADD_SD()                       // do not add
# define ESL_APPCTRL_MSGID_ADD_SD()                        // do not add
#endif // ESL_SD_MODULE_ENABLE //

// USBHMSD --------------------------------------------------------------------------
#if ((ESL_USBH_MODULE_ENABLE) && (ESL_USBH_CLASS_MSD))
# define ESL_APPCTRL_TASKID_ADD_USBHMSD()  ESL_APPCTRL_TASKID_ADD(ESL_TASKID_USBHMSD)
# define ESL_APPCTRL_MSGID_ADD_USBHMSD()   ESL_APPCTRL_MSGID_ADD(ESL_MSGID_USBHMSD_TASK_READY)
# define ESL_APPCTRL_TEMPLATE_ADD_USBHMSD_RAW(taskid,pri,attrs) \
            ESL_APPCTRL_TEMPLATE_ADD_ESL(taskid, \
                                         esl_usbhmsd_task, \
                                         ESL_USBH_MSD_TASK_STACK, \
                                         pri, \
                                         ESL_USBH_MSD_TASK_STR, \
                                         attrs)

/** @def ESL_APPCTRL_TEMPLATE_ADD_USBHMSD(pri)
 * @brief Declares the eslLog task to the TASK_TEMPLATE_STRUCT structure.
 * @param[in] pri       Task priority. */
# define ESL_APPCTRL_TEMPLATE_ADD_USBHMSD(pri) \
            ESL_APPCTRL_TEMPLATE_ADD_USBHMSD_RAW(ESL_TASKID_USBHMSD, \
                                                 pri, \
                                                 ESL_APPCTRL_SENDMSGONREADY | ESL_APPCTRL_QUITAPPONFAILURE | ESL_MSGID_USBHMSD_TASK_READY)

#else // ((ESL_USBHMSD_MODULE_ENABLE) && (ESL_USBH_CLASS_MSD)) //
# define ESL_APPCTRL_TASKID_ADD_USBHMSD()                       // do not add
# define ESL_APPCTRL_MSGID_ADD_USBHMSD()                        // do not add
#endif // ((ESL_USBHMSD_MODULE_ENABLE) && (ESL_USBH_CLASS_MSD)) //

// [ further ] -----------------------------------------------------------------
// TODO: Declare new task-based module macros here:

//******************************************************************************
// Task ID enum template
//******************************************************************************

/** @def ESL_APPCTRL_TASKID_BEGIN_RAW()
 * @brief Declares the beginning part of an unnamed enum, automatically counting
 *        the ESL task IDs, and leaves it empty.
 *        Preferably use ESL_APPCTRL_TASKID_BEGIN instead. */
#define ESL_APPCTRL_TASKID_BEGIN_RAW() \
  enum { \

/** @def ESL_APPCTRL_TASKID_BEGIN()
 * @brief Declares the beginning part of an unnamed enum, automatically counting
 *        the ESL task IDs, and fills in the ESL tasks of all enabled modules. */
#define ESL_APPCTRL_TASKID_BEGIN() \
  ESL_APPCTRL_TASKID_BEGIN_RAW() \
    ESL_APPCTRL_TASKID_RESERVED = ESL_TASKID_EMPTY, \
    ESL_APPCTRL_TASKID_ADD_APPCTRL() \
    ESL_APPCTRL_TASKID_ADD_LOG() \
    ESL_APPCTRL_TASKID_ADD_SD() \
    ESL_APPCTRL_TASKID_ADD_USBHMSD()

/** @def ESL_TASKID_EMPTY
 * @brief ID of the empty (reserved) message. */
#define ESL_TASKID_EMPTY                (0)

/** @def ESL_APPCTRL_TASKID_ADD(name)
 * @brief Declares one task ID name in the TASKID unnamed counting enum.
 * @param[in] name  Name of the ID - a unique C identifier. */
#define ESL_APPCTRL_TASKID_ADD(name) \
    name,

/** @def ESL_APPCTRL_TASKID_END()
 * @brief Declares the end part of the TASKID unnamed counting enum. */
#define ESL_APPCTRL_TASKID_END() \
    ESL_APPCTRL_TASKID_ADD(ESL_TASKID_TRIGGER) \
  };

/** @def ESL_TASKID_COUNT
 * @brief Expands to the number of declared TASKIDs. */
#define ESL_APPCTRL_TASKID_COUNT        ((ESL_TASKID_TRIGGER)-1)

//******************************************************************************
// MSGID enum template
//******************************************************************************

/** @def ESL_APPCTRL_MSGID_BEGIN_RAW()
 * @brief Declares the beginning part of an unnamed enum, automatically counting
 *        the ESL messages IDs, and leaves it empty.
 *        Preferably use ESL_APPCTRL_MSGID_BEGIN instead. */
#define ESL_APPCTRL_MSGID_BEGIN_RAW() \
  enum { \

/** @def ESL_APPCTRL_MSGID_BEGIN()
 * @brief Declares the beginning part of an unnamed enum, automatically counting
 *        the ESL messages IDs, and fills in the ESL tasks of all enabled
 *        modules. */
#define ESL_APPCTRL_MSGID_BEGIN() \
  ESL_APPCTRL_MSGID_BEGIN_RAW() \
    ESL_APPCTRL_MSGID_RESERVED = ESL_MSGID_EMPTY, \
    ESL_APPCTRL_MSGID_ADD_LOG() \
    ESL_APPCTRL_MSGID_ADD_SD() \
    ESL_APPCTRL_MSGID_ADD_USBHMSD()

/** @def ESL_MSGID_EMPTY
 * @brief ID of the empty (reserved) message. */
#define ESL_MSGID_EMPTY                 (0)

/** @def ESL_APPCTRL_MSGID_ADD(name)
 * @brief Declares one message ID name in the MSGID unnamed counting enum.
 * @param[in] name  Name of the ID - a unique C identifier. */
#define ESL_APPCTRL_MSGID_ADD(name) \
    name,

/** @def ESL_APPCTRL_MSGID_END()
 * @brief Declares the end part of the MSGID unnamed counting enum. */
#define ESL_APPCTRL_MSGID_END() \
    ESL_APPCTRL_MSGID_ADD(ESL_MSGID_TRIGGER) \
  };

/** @def ESL_APPCTRL_MSGID_COUNT
 * @brief Expands to the number of declared MSGIDs. */
#define ESL_APPCTRL_MSGID_COUNT         ((ESL_MSGID_TRIGGER)-1)

//******************************************************************************
// TASK_TEMPLATE_STRUCT declaration macros
//******************************************************************************

/** @def ESL_APPCTRL_TEMPLATE_BEGIN()
 * @brief Declares the beginning part of the TASK_TEMPLATE_STRUCT structure. */
#define ESL_APPCTRL_TEMPLATE_BEGIN() \
  TASK_TEMPLATE_STRUCT MQX_template_list[] = {

/** @def ESL_APPCTRL_TEMPLATE_ADD_STD(id, func, stack, pri, str, start)
 * @brief Declares one task to the TASK_TEMPLATE_STRUCT structure to be started
 *        by MQX or manually.
 * @param[in] id        Unique task ID.
 * @param[in] func      Task body function.
 * @param[in] stack     Task stack size (in bytes).
 * @param[in] pri       Task priority.
 * @param[in] str       Unique task name.
 * @param[in] start     Task start strategy. Use MQX_AUTO_START_TASK for *user*
 *                       tasks which should start automatically (not the case
 *                       of ESL tasks!). Use 0 if you want to start the tasks
 *                       manually. */
#define ESL_APPCTRL_TEMPLATE_ADD_STD(id, func, stack, pri, str, start) \
    ESL_APPCTRL_TEMPLATE_ADD_RAW(id, func, stack, pri, str, start, 0, 0)

/** @def ESL_APPCTRL_TEMPLATE_ADD_ESL(id, func, stack, pri, str, param)
 * @brief Declares one task to the TASK_TEMPLATE_STRUCT structure to be started
 *        and handled by ESL.
 * @param[in] id        Unique task ID.
 * @param[in] func      Task body function.
 * @param[in] stack     Task stack size (in bytes).
 * @param[in] pri       Task priority.
 * @param[in] str       Unique task name.
 * @param[in] param     ESL task parameters, @see ESL_APPCTRL_BLOCKONREADY,
 *                       @see ESL_APPCTRL_SENDMSGONREADY,
 *                       @see ESL_APPCTRL_QUITAPPONFAILURE. */
#define ESL_APPCTRL_TEMPLATE_ADD_ESL(id, func, stack, pri, str, param) \
    ESL_APPCTRL_TEMPLATE_ADD_RAW(id, func, stack, pri, str, 0, (param) | ESL_APPCTRL_HANDLETASK, 0)

/** @def ESL_APPCTRL_TEMPLATE_ADD_RAW(idx, func, stack, pri, name, attrs, param, slice)
 * @brief Simply fills one complete TASK_TEMPLATE_STRUCT field. */
#define ESL_APPCTRL_TEMPLATE_ADD_RAW(idx, func, stack, pri, name, attrs, param, slice) \
    { idx, func, stack, pri, name, attrs, param, slice },

/** @def ESL_APPCTRL_TEMPLATE_END()
 * @brief Declares the end part of the TASK_TEMPLATE_STRUCT structure and the
 *        g_aoEslAppctrlTaskList data array. */
#define ESL_APPCTRL_TEMPLATE_END() \
    ESL_APPCTRL_TEMPLATE_ADD_STD(0, 0, 0, 0, 0, 0) \
  }; \
  ESL_APPCTRL_TTaskData g_aoEslAppctrlTaskList[sizeof(MQX_template_list)/sizeof(*MQX_template_list)];

//******************************************************************************
// Functions declarations
//******************************************************************************

/** ESL main control task that should:
 * - start all child tasks,
 * - check their run afterwards.
 * @param[in] u32initialData  Task initial data. */
void esl_appctrl_task (uint_32 u32InitialData);

//******************************************************************************
#endif // ESL_APPCTRL_H_09238576701983203758762345 //
