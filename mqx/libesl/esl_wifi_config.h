/** ****************************************************************************
 *
 *  @file       esl_wifi.h
 *  @brief      WIFI module config file
 *
 *  Default configuration of the WIFI module. The settings should not be changed
 *  here but can be overridden in a project specific esl_config.h.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.0 2014-01-20: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision for esl_wifi v1.0.
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

#ifndef ESL_WIFI_CONFIG_H_23059752476507342510667426
#define ESL_WIFI_CONFIG_H_23059752476507342510667426
//******************************************************************************

#include "esl_config.h"

//******************************************************************************
// Main module settings
//******************************************************************************

/** @def ESL_WIFI_MODULE_ENABLE
 * @brief Set 1/0 to get module enabled or disabled. */
#ifndef ESL_WIFI_MODULE_ENABLE
# define ESL_WIFI_MODULE_ENABLE         (0)
#endif

/** @def ESL_WIFI_MSGQ_SIZE
 * @brief Size of the wifi message queue in a number of messages. This queue
 *        is used to receive messages from the AtherosWifi task. */
#ifndef ESL_WIFI_MSGQ_SIZE
# define ESL_WIFI_MSGQ_SIZE             (3)
#endif

//******************************************************************************
// Access Point configuration
//******************************************************************************

/** @def ESL_WIFI_AP_HIDDEN_DEFAULT
 * @brief Set to 1 to disable SSID broadcast by default, use 0 to enable. */
#ifndef ESL_WIFI_AP_HIDDEN_DEFAULT
/** @def ESL_WIFI_AP_HIDDEN
 * @brief Deprecated, use @see ESL_WIFI_AP_HIDDEN_DEFAULT instead.
 * @deprecated This definition has been replaced by ESL_WIFI_AP_HIDDEN_DEFAULT
 *             as of ESL 1.0.3 and will be removed in future versions. */
# ifdef ESL_WIFI_AP_HIDDEN
#  define ESL_WIFI_AP_HIDDEN_DEFAULT    (ESL_WIFI_AP_HIDDEN)
# else // ESL_WIFI_AP_HIDDEN //
#  define ESL_WIFI_AP_HIDDEN_DEFAULT    (0)
# endif // ESL_WIFI_AP_HIDDEN //
#endif // ESL_WIFI_AP_HIDDEN_DEFAULT //

//******************************************************************************
// Client configuration
//******************************************************************************

/** @def ESL_WIFI_CLI_IP_STATIC_DEFAULT
 * @brief Set to 1 to use static client IP by default, 0 to get it from DHCP. */
#ifndef ESL_WIFI_CLI_IP_STATIC_DEFAULT
# define ESL_WIFI_CLI_IP_STATIC_DEFAULT (1)
#endif

//******************************************************************************
#endif /* ESL_WIFI_CONFIG_H_23059752476507342510667426 */
