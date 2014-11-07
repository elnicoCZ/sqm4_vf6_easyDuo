/** ****************************************************************************
 *
 *  @file       esl_td.h
 *  @brief      Time domains.
 *
 *  This module provides an easy way to handle application specific time
 *  domains. To use the module the application must define the array of time
 *  domains in the following global variable: "esl_td_timeDomain
 *  esl_td_aoTimeDomain[]". The number of time domains is configured in
 *  ESL_TD_DOMAINCNT. The module is built on top of the MQX lwtimer API and
 *  provides practically the same functionality.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *
 *  @version    1.1 2014-03-03: Jan Kubiznak <kubiznak.jan@elnico.cz>
 *                              Module deinit, routine unregistration.
 *
 *  @version    1.0 2014-02-26: Jan Kubiznak <kubiznak.jan@elnico.cz>
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

#ifndef ESL_TD_H_48721321576513213547654129
#define ESL_TD_H_48721321576513213547654129

//******************************************************************************

#include <lwtimer.h>
#include "esl_td_config.h"

//******************************************************************************

// Module specific log IDs
enum {
  ESL_TD_OK = MQX_OK,
  ESL_TD_INVALID_ARG,
  ESL_TD_FAILURE,
  ESL_TD_MODULE_OFF
};

//******************************************************************************

/** Time domain structure. */
typedef struct {
	_mqx_uint   uiPeriod;         //!< Time domain period in msec.
	_mqx_uint   uiStartupDelay;   //!< Time domain startup delay in msec.
} esl_td_timeDomain;

//******************************************************************************

/** @var esl_td_timeDomain esl_td_aoTimeDomain[]
 * @brief The array of time domains is supposed to be defined by the
 * application. Also - the ESL_TD_DOMAINCNT macro shall be adjusted accordingly
 * with every redefinition of this variable.
 * Example of the definition of 2 time domains (10 msec and 1 sec):
 * esl_td_timeDomain esl_td_aoTimeDomain[] = {
 *   {.uiPeriod=10,   .uiStartupDelay=50},
 *   {.uiPeriod=1000, .uiStartupDelay=50}
 * };
 */
extern esl_td_timeDomain esl_td_aoTimeDomain[ESL_TD_DOMAINCNT];

//******************************************************************************

/** Call this function to initialize the time domains in esl_td_aoTimeDomain[]
 * in range between u8StartTd and u8EndTd.
 * @param [in]  u8StartTd  Index of the first time domain to initialize.
 * @param [in]  u8EndTd    Index of the last time domain to initialize.
 * @param [out] err        Value adjusted in case of failure by commands
 *                         embedded in the function.
 * @return                 ESL_TD_OK on success, other value on failure. */
uint_8 esl_td_init (uint_8 u8StartTd, uint_8 u8EndTd, _mqx_uint *err);

/** Call this function to deinitialize the time domains in esl_td_aoTimeDomain[]
 * in range between u8StartTd and u8EndTd.
 * @param [in]  u8StartTd  Index of the first time domain to deinitialize.
 * @param [in]  u8EndTd    Index of the last time domain to deinitialize.
 * @param [out] err        Value adjusted in case of failure by commands
 *                         embedded in the function.
 * @return                 ESL_TD_OK on success, other value on failure. */
uint_8 esl_td_deinit (uint_8 u8StartTd, uint_8 u8EndTd, _mqx_uint *err);

/** Call this function to register a new routine to be called from one of the
 * existing time domains.
 * @param [in]  u8Td       Index of the time domain in esl_td_aoTimeDomain[], to
 *                         which the routine shall be registered.
 * @param [out] pLwTimer   Pointer to an empty lightweight timer to be added to
 *                         the queue.
 * @param [in]  pfRoutine  Pointer to the routine to be called from the time
 *                         domain.
 * @param [in]  pvParam    Pointer to the parameter to be passed to the routine.
 * @param [out] err        Value adjusted in case of failure by commands
 *                         embedded in the function.
 * @return                 ESL_TD_OK on success, other value on failure. */
uint_8 esl_td_registerRoutine (uint_8                  u8Td,
                               LWTIMER_STRUCT        * pLwTimer,
                               LWTIMER_ISR_FPTR        pfRoutine,
                               void                  * pvParam,
                               _mqx_uint             * err);

/** Call this function to unregister an existing routine in the time domain.
 * @param [out] pLwTimer   Pointer to an empty lightweight timer to be added to
 *                         the queue.
 * @param [out] err        Value adjusted in case of failure by commands
 *                         embedded in the function.
 * @return                 ESL_TD_OK on success, other value on failure. */
uint_8 esl_td_unregisterRoutine (LWTIMER_STRUCT      * pLwTimer,
                                 _mqx_uint           * err);

//******************************************************************************
#endif // ESL_TD_H_48721321576513213547654129
