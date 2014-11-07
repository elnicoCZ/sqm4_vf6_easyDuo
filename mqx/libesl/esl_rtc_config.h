/** ****************************************************************************
 *
 *  @file       esl_rtc_config.h
 *  @brief      RTC module config file
 *
 *  Default configuration of the RTC module. The settings should not be changed
 *  here but can be overridden in a project specific esl_config.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    2.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    2.0 2013-11-15: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_rtc v2.0.
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

#ifndef ESL_RTC_CONFIG_H_95732607443246123106013210
#define ESL_RTC_CONFIG_H_95732607443246123106013210
//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_RTC_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_RTC_MODULE_ENABLE
# define ESL_RTC_MODULE_ENABLE          (0)
#endif

/** @def ESL_RTC_SYNCHRONIZER_PERIOD
 * @brief Period of RTC and MQX times synchronization in minutes. */
#ifndef ESL_RTC_SYNCHRONIZER_PERIOD
# define ESL_RTC_SYNCHRONIZER_PERIOD    (30)
#endif

//******************************************************************************
#endif /* ESL_RTC_CONFIG_H_95732607443246123106013210 */
