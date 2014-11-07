/** ****************************************************************************
 *
 *  @file       esl_wifi_cli.h
 *  @brief      Client submodule of the WIFI module.
 *
 *  All Client-related functions are located here. Use this submodule
 *  to operate in the managed wifi mode (infrastructure).
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.0 2014-02-28: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef ESL_WIFI_CLI_H_09831466545853141302164541
#define ESL_WIFI_CLI_H_09831466545853141302164541
//******************************************************************************

#include "esl_wifi.h"

//******************************************************************************
// Configuration structure
//******************************************************************************
typedef struct esl_wifi_cli_config_struct {
  uint_8                  bfDynamicIp : 1;                  //!< 1 to get IP from DHCP, 0 for static.
  IPCFG_IP_ADDRESS_DATA   oIpData;                          //!< Network addresses.
  ESL_WIFI_TSec           oSecurity;                        //!< Security settings.
} ESL_WIFI_CLI_TConfig;

//******************************************************************************
// Public functions
//******************************************************************************

/** Connects to a network in the managed mode.
 * @param[in] sSSID   (Extended) Service Set Identifier of the network
 *                    to connect to.
 * @param[in] poConfig  Network configuration. Retrieve the structure by
 *                      @see esl_wifi_cli_getDefaultConfiguration(), then change
 *                      requested configuration using different
 *                      esl_wifi_cli_configXXX() functions.
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
uint_8 esl_wifi_cli_connect (const char                  * sSSID,
                             const ESL_WIFI_CLI_TConfig  * poConfig);

/** Retrieves the default network configuration.
 * @param[out]  poConfig  Pointer to object to set its fields to defaults.
 * @return      ESL_WIFI_OK on success.
 *              ESL_WIFI_INVALID_ARGUMENT if NULL given. */
uint_8 esl_wifi_cli_getDefaultConfiguration (ESL_WIFI_CLI_TConfig * poConfig);
/** Modifies client configuration to have static IP address.
 * @param[in,out] poConfig  Configuration structure to modify.
 * @param[in]     pAddr     Static IP to be used on the network.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if NULL given. */
uint_8 esl_wifi_cli_configIpStatic (ESL_WIFI_CLI_TConfig        * poConfig,
                                    const IPCFG_IP_ADDRESS_DATA * pAddr);
/** Modifies client configuration to fetch dynamic IP address from DHCP server.
 * @param[in,out] poConfig  Configuration structure to modify.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if NULL given. */
uint_8 esl_wifi_cli_configIpDynamic (ESL_WIFI_CLI_TConfig * poConfig);
/** Modifies client configuration to use no security.
 * @param[in,out] poConfig  Configuration structure to modify.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if NULL given. */
uint_8 esl_wifi_cli_configSecOpen (ESL_WIFI_CLI_TConfig * poConfig);
/** Modifies client configuration to use WEP security.
 * @param[in,out] poConfig  Configuration structure to modify.
 * @param[in]     sKey1     First WEP key - either 5 characters long ASCII string,
 *                          10 characters long HEX string, 13 characters long
 *                          ASCII string or 26 characters long HEX string.
 * @param[in]     sKey2     Second WEP key. May be NULL or empty to ignore,
 *                          sKey3 and sKey4 will then be ignored too.
 * @param[in]     sKey3     Third WEP key. May be NULL or empty to ignore,
 *                          sKey4 will then be ignored too.
 * @param[in]     sKey4     Fourth WEP key. May be NULL or empty to ignore.
 * @param[in]     u8DefaultKey  Number of the default key used for TX.
 *                          A value from 1 to 4, the selected key must be used.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if any argument is invalid. */
uint_8 esl_wifi_cli_configSecWEP (ESL_WIFI_CLI_TConfig  * poConfig,
                                  const char            * sKey1,
                                  const char            * sKey2,
                                  const char            * sKey3,
                                  const char            * sKey4,
                                  uint_8                  u8DefaultKey);
/** Modifies client configuration to use WPA/WPA2 security.
 * @param[in,out] poConfig  Configuration structure to modify.
 * @param[in]     u8Version ESL_WIFI_WPA_VERSION_1 for WPA,
 *                          ESL_WIFI_WPA_VERSION_2 for WPA2.
 * @param[in]     u8UCipher ESL_WIFI_WPA_TKIP or ESL_WIFI_WPA_CCMP.
 * @param[in]     u8MCipher ESL_WIFI_WPA_TKIP or ESL_WIFI_WPA_CCMP.
 * @param[in]     sPSK      Preshared key, i.e. the password.
 *                          Use either at most 63-characters long ASCII string
 *                          or a 64-characters long HEX string (PMK).
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if any argument is invalid. */
uint_8 esl_wifi_cli_configSecWPA (ESL_WIFI_CLI_TConfig  * poConfig,
                                  uint_8                  u8Version,
                                  uint_8                  u8UCipher,
                                  uint_8                  u8MCipher,
                                  const char            * sPSK);

//******************************************************************************
#endif // ESL_WIFI_CLI_H_09831466545853141302164541 //
