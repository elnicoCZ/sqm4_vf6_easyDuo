/** ****************************************************************************
 *
 *  @file       esl_cfg_config.h
 *  @brief      Configuration files access module config file
 *
 *  Default configuration of the cfg module. The settings should not be changed
 *  here but can be overridden in a project specific esl_cfg.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    3.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    3.0 2013-11-21: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_cfg v3.0.
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

#ifndef ESL_CFG_CONFIG_H_31756032606545316218145154
#define ESL_CFG_CONFIG_H_31756032606545316218145154
//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_CFG_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_CFG_MODULE_ENABLE
# define ESL_CFG_MODULE_ENABLE          (0)
#endif

/** @def ESL_CFG_MAX_FILE_SIZE
 * @brief Maximum allowed size (in bytes) of the config file.
 *        If the file is bigger, open operation fails. */
#ifndef ESL_CFG_MAX_FILE_SIZE
# define ESL_CFG_MAX_FILE_SIZE          (10240)
#endif

//******************************************************************************
#endif /* ESL_CFG_CONFIG_H_31756032606545316218145154 */
