/** ****************************************************************************
 *
 *  @file       esl_wifi_ap.h
 *  @brief      Access Point submodule of the WIFI module.
 *
 *  All AP-related functions are located here.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.0 2014-01-22: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Initial revision
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

#ifndef ESL_WIFI_AP_H_82366227055205629614430512
#define ESL_WIFI_AP_H_82366227055205629614430512
//******************************************************************************

#include "esl_wifi.h"

//******************************************************************************
// Configuration structure
//******************************************************************************
typedef struct esl_wifi_ap_config_struct {
  uint_8        bfHidden : 1;                               //!< Enable SSID broadcast?
  _ip_address   ipDhcpFirst;                                //!< DHCP pool first IP.
  _ip_address   ipDhcpLast;                                 //!< DHCP pool last IP.
  int_32        i32DhcpLeaseTime;                           //!< DHCP IP lease time.
  ESL_WIFI_TSec oSecurity;                                  //!< Security settings.
} ESL_WIFI_AP_TConfig;

//******************************************************************************
// Public functions
//******************************************************************************

/** Establishes a new network access point.
 * @param[in] sSSID   (Extended) Service Set Identifier of the network.
 * @param[in] pAddr   Network addresses (IP, mask, gateway) to set.
 * @param[in] poConfig  Network configuration. Retrieve the structure by
 *                      @see esl_wifi_ap_getDefaultConfiguration(), then change
 *                      requested configuration using different
 *                      esl_wifi_ap_configXXX() functions.
 *                      Use NULL for default settings.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_NOT_INITIALIZED if the module is not initialized yet,
 *           @see esl_wifi_init().
 *          ESL_WIFI_CONNECTED if the device is already configured and connected.
 *          Further error values: ESL_WIFI_CALLBACK_FAILURE,
 *           ESL_WIFI_MODE_FAILURE, ESL_WIFI_SSID_FAILURE,
 *           ESL_WIFI_COMMIT_FAILURE, ESL_WIFI_IP_FAILURE,
 *           ESL_WIFI_DHCP_FAILURE, ESL_WIFI_PARAM_FAILURE,
 *           ESL_WIFI_SEC_FAILURE. */
uint_8 esl_wifi_ap_connect (const char                  * sSSID,
                            const IPCFG_IP_ADDRESS_DATA * pAddr,
                            const ESL_WIFI_AP_TConfig   * poConfig);

/** Retrieves the default network configuration.
 * @param[out]  poConfig  Pointer to object to set its fields to defaults.
 * @return      ESL_WIFI_OK on success.
 *              ESL_WIFI_INVALID_ARGUMENT if NULL given. */
uint_8 esl_wifi_ap_getDefaultConfiguration (ESL_WIFI_AP_TConfig * poConfig);
/** Modifies network configuration to hidden.
 * @param[in,out] poConfig  Configuration structure to modify.
 * @param[in]     bHidden   Use TRUE for hidden network, FALSE for visible.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if NULL given. */
uint_8 esl_wifi_ap_configHidden (ESL_WIFI_AP_TConfig * poConfig,
                                 boolean               bHidden);
/** Modifies network configuration to run DHCP server.
 * @param[in,out] poConfig  Configuration structure to modify.
 * @param[in]     ipFirst   First IP address to make available for clients.
 * @param[in]     ipLast    Last IP address to make available for clients.
 * @param[in]     i32LeaseTime  Client IP lease time in seconds.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_IP_FAILURE if the last address is smaller than the first.
 *          ESL_WIFI_INVALID_ARGUMENT if NULL given.
 *          ESL_WIFI_NOT_IMPLEMENTED if Atheros stack offloading is disabled,
 *           which generally is (@see ESL_WIFI_ENABLE_STACK_OFFLOAD).
 *           Use standard DHCP server available in the RTCS stack of MQX. */
uint_8 esl_wifi_ap_configDHCP (ESL_WIFI_AP_TConfig  * poConfig,
                               _ip_address            ipFirst,
                               _ip_address            ipLast,
                               int_32                 i32LeaseTime);
/** Modifies network configuration to use no security.
 * @param[in,out] poConfig  Configuration structure to modify.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if NULL given. */
uint_8 esl_wifi_ap_configSecOpen (ESL_WIFI_AP_TConfig * poConfig);
/** Modifies network configuration to use WPA/WPA2 security.
 * @param[in,out] poConfig  Configuration structure to modify.
 * @param[in]     u8Version ESL_WIFI_WPA_VERSION_1 for WPA,
 *                          ESL_WIFI_WPA_VERSION_2 for WPA2.
 * @param[in]     sPSK      Preshared key, i.e. the password.
 *                          Use either at most 63-characters long ASCII string
 *                          or a 64-characters long HEX string (PMK).
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if any argument is invalid. */
uint_8 esl_wifi_ap_configSecWPA (ESL_WIFI_AP_TConfig  * poConfig,
                                 uint_8                 u8Version,
                                 const char           * sPSK);

//******************************************************************************
#endif // ESL_WIFI_AP_H_82366227055205629614430512 //
