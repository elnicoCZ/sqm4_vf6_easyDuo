/** ****************************************************************************
 *
 *  @file       esl_spimem_config.h
 *  @brief      Module spimem configuration.
 *
 *  Default configuration of the esl_spimem module.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Jan Kubiznak <kubiznak.jan@elnico.cz>
 *
 *  @version    1.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.0 2014-01-06: Jan Kubiznak <kubiznak.jan@elnico.cz>
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

#ifndef ESL_SPIMEM_CONFIG_H_90349085902938498604012049
#define ESL_SPIMEM_CONFIG_H_90349085902938498604012049

//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_SPIMEM_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_SPIMEM_MODULE_ENABLE
# define ESL_SPIMEM_MODULE_ENABLE           (0)
#endif

//******************************************************************************
// Conditional include based on the selected chip
//******************************************************************************

/** @def ESL_SPIMEM_ADDRLEN
 * @brief Very important macro, although partly redundant with the u8AddrLen
 * member of the ESL_SPIMEM_TChipCfg structure. The value here should be set
 * to u8AddrLen of the chip, which has the biggest address length. For the
 * communication still u8AddrLen is used. But the I/O buffer in functions is
 * allocated in dependence of ESL_SPIMEM_ADDRLEN. In case of an invalid setup
 * of this macro the function will return ESL_SPIMEM_INVALID_ADDRLEN. */
#ifndef ESL_SPIMEM_ADDRLEN
# define ESL_SPIMEM_ADDRLEN                 (3)
#endif

/** @def ESL_SPIMEM_MULTITASK
 * @brief Use 1 if the esl_spimem_* interface functions are called from more
 * then 1 MQX task or ISR (generally if it could happen that 1 already running
 * esl_spimem_* function is interrupted by another 1). If all esl_spimem_*
 * function calls are for sure done just from one task, then keep this value
 * as 0.
 * Hint: If esl_log is configured to log to EEPROM, then it actually also uses
 *       the esl_spimem_* interface. Therefore if there is then one more task
 *       using esl_spimem_* in the application, this macro shall be set to 1. */
#ifndef ESL_SPIMEM_MULTITASK
# define ESL_SPIMEM_MULTITASK               (0)
#endif

/** @def ESL_SPIMEM_MAXWAIT
 * @brief Maximal wait time in msec to wait for the access in case of
 * ESL_SPIMEM_MULTITASK is 1. */
#ifndef ESL_SPIMEM_MAXWAIT
# define ESL_SPIMEM_MAXWAIT                 (50)
#endif

//******************************************************************************
#endif // ESL_SPIMEM_CONFIG_H_90349085902938498604012049
