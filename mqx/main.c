/** ****************************************************************************
 *
 *  @file       main.c
 *  @brief      Accelerometer demo.
 *
 *  Demo entry point.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-09-18: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#include "startup.h"
#include "accelerometer.h"
#include "gpio.h"

#include "esl_appctrl.h"
#include "esl_log.h"

#include <mqx.h>
#include <bsp.h>

//******************************************************************************
// Tasks declarations
//******************************************************************************

// Declare all your task IDs here:
ESL_APPCTRL_TASKID_BEGIN()
  ESL_APPCTRL_TASKID_ADD(STARTUP_TASKID)
  ESL_APPCTRL_TASKID_ADD(ACCEL_TASKID)
  ESL_APPCTRL_TASKID_ADD(GPIO_TASKID)
ESL_APPCTRL_TASKID_END()

//******************************************************************************

// Declare all your message IDs here:
ESL_APPCTRL_MSGID_BEGIN()
  ESL_APPCTRL_MSGID_ADD(MSGID_STARTUP_READY)
  ESL_APPCTRL_MSGID_ADD(MSGID_ACCEL_READY)
  ESL_APPCTRL_MSGID_ADD(MSGID_GPIO_READY)
ESL_APPCTRL_MSGID_END()

//******************************************************************************

// Declare tasks to be handled manually here:
ESL_APPCTRL_TEMPLATE_BEGIN()
  ESL_APPCTRL_TEMPLATE_ADD_APPCTRL(                                                   15,                   MQX_AUTO_START_TASK )
  ESL_APPCTRL_TEMPLATE_ADD_LOG(                                                       13 )
  // ESL_APPCTRL_TEMPLATE_ADD_ESL(    Task ID,      function,             stack,    prio,     "string ID",     attributes.)
  ESL_APPCTRL_TEMPLATE_ADD_ESL(STARTUP_TASKID,  startup_task, STARTUP_TASKSTACK,      17,STARTUP_TASKNAME,  ESL_APPCTRL_SENDMSGONREADY | ESL_APPCTRL_QUITAPPONFAILURE | MSGID_STARTUP_READY )
//  ESL_APPCTRL_TEMPLATE_ADD_ESL(  ACCEL_TASKID,    accel_task,   ACCEL_TASKSTACK,      18,  ACCEL_TASKNAME,  ESL_APPCTRL_SENDMSGONREADY | ESL_APPCTRL_QUITAPPONFAILURE | MSGID_ACCEL_READY   )
  ESL_APPCTRL_TEMPLATE_ADD_ESL(   GPIO_TASKID,     gpio_task,    GPIO_TASKSTACK,      19,   GPIO_TASKNAME,  ESL_APPCTRL_SENDMSGONREADY |                                MSGID_GPIO_READY    )
ESL_APPCTRL_TEMPLATE_END()

//******************************************************************************
