/** ****************************************************************************
 *
 *  @file       esl_td_config.h
 *  @brief      Application time domains.
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

#ifndef ESL_TD_CONFIG_H_54584543218794561357987651
#define ESL_TD_CONFIG_H_54584543218794561357987651

//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_TD_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_TD_MODULE_ENABLE
# define ESL_TD_MODULE_ENABLE           (0)
#endif

/** @def ESL_TD_DOMAINCNT
 * @brief Count of registered time domains. This value shall be adapted in case
 * the esl_td_aoTimeDomain variable is redefined. */
#ifndef ESL_TD_DOMAINCNT
# define ESL_TD_DOMAINCNT               (1)
#endif

//******************************************************************************

#endif // ESL_TD_CONFIG_H_54584543218794561357987651
