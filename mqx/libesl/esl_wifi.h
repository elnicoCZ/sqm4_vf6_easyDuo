/** ****************************************************************************
 *
 *  @file       esl_wifi.h
 *  @brief      AR4100 wifi access module.
 *
 *  Provides a set of common functions for controlling the Atheros AR4100
 *  wifi chip. The module is built on top of the MQX driver provided by Atheros.
 *
 *  @copyright  Elnico Ltd. All rights reserved.
 *  @author     Petr Kubiznak <kubiznak.petr@elnico.cz>
 *
 *  @version    1.1 2014-01-29: Petr Kubiznak <kubiznak.petr@elnico.cz>
 *                              Header updated (responsibility, license).
 *
 *  @version    1.0 2014-01-20: Petr Kubiznak <kubiznak.petr@elnico.cz>
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

#ifndef ESL_WIFI_H_02374547012594538450622305
#define ESL_WIFI_H_02374547012594538450622305
//******************************************************************************

#include "esl_wifi_config.h"

#include <mqx.h>
#include <bsp.h>
#include <rtcs.h>
#include <ipcfg.h>

//******************************************************************************
/** @def ESL_WIFI_MAC_BYTES
 * @brief Size of MAC address in bytes. */
#define ESL_WIFI_MAC_BYTES              (6)

//******************************************************************************
// ESL_WIFI_TMsg
//******************************************************************************

typedef struct esl_wifi_msg_struct {
  uint_8  u8Type;                       //!< Message type.
} ESL_WIFI_TMsg;

//******************************************************************************
// Security
//******************************************************************************

#define ESL_WIFI_WEP_KEYS_CNT           (4)                 //!< Maximum number of WEP keys.
#define ESL_WIFI_WEP_KEY_MAXLEN         (26)                //!< Maximum number of characters of a WEP key (HEX, 128bit).

#define ESL_WIFI_WPA_PSK_MINLEN         (8)                 //!< Minimum length of the WPA preshared key
#define ESL_WIFI_WPA_PSK_MAXLEN         (64)                //!< Maximum length of the WPA preshared key
#define ESL_WIFI_WPA_PMK_LEN            (64)                //!< Length of Pairwise Master Key. If WPA password is shorter, its an ASCII PSK.

#define ESL_WIFI_WPA_VERSION_1          (0)                 //!< RC4
#define ESL_WIFI_WPA_VERSION_2          (1)                 //!< AES
#define ESL_WIFI_WPA_TKIP               (0)                 //!< Temporal Key Integrity Protocol
#define ESL_WIFI_WPA_CCMP               (1)                 //!< Counter Mode with Cipher Block Chaining Message Authentication Code Protocol

/** WEP security configuration. */
typedef struct esl_wifi_secwep_struct {
  uint_8        u4DefaultKey  : 4;                                              //!< 1-4
  uint_8        u4KeysCnt     : 4;                                              //!< 1-4
  char          asKeys[ESL_WIFI_WEP_KEYS_CNT][ESL_WIFI_WEP_KEY_MAXLEN+1];       //!< WPA keys array.
} ESL_WIFI_TSecWEP;

/** WPA/WPA2 security configuration. */
typedef struct esl_wifi_secwpa_struct {
  uint_8        bfVersion : 1;                              //!< ESL_WIFI_WPA_VERSION_1 or ESL_WIFI_WPA_VERSION_2
  uint_8        bfUCipher : 1;                              //!< ESL_WIFI_WPA_TKIP or ESL_WIFI_WPA_CCMP
  uint_8        bfMCipher : 1;                              //!< ESL_WIFI_WPA_TKIP or ESL_WIFI_WPA_CCMP
  char          sPassword[ESL_WIFI_WPA_PSK_MAXLEN+1];       //!< PSK
} ESL_WIFI_TSecWPA;

/** General security structure. */
typedef struct esl_wifi_sec_struct {
  uint_8        u8Type;                                     //!< Open / WEP / WPA
  union {
    ESL_WIFI_TSecWEP    wep;
    ESL_WIFI_TSecWPA    wpa;
  }             unData;                                     //!< Security data
} ESL_WIFI_TSec;

//******************************************************************************
// Return values
//******************************************************************************
enum {
  ESL_WIFI_OK = MQX_OK,

  ESL_WIFI_NOT_IMPLEMENTED,
  ESL_WIFI_ERROR,
  ESL_WIFI_BUSY,
  ESL_WIFI_TIMEOUT,
  ESL_WIFI_INVALID_ARGUMENT,
  ESL_WIFI_NOT_INITIALIZED,
  ESL_WIFI_ALREADY_INITIALIZED,
  ESL_WIFI_DEVICE_INIT_FAILURE,
  ESL_WIFI_HANDLE_FAILURE,
  ESL_WIFI_MSGQ_FAILURE,
  ESL_WIFI_IOCTL_FAILURE,
  ESL_WIFI_CONNECTED,
  ESL_WIFI_DISCONNECTED,
  ESL_WIFI_AUTH_SUCCESS,
  ESL_WIFI_AUTH_FAILURE,
  ESL_WIFI_CALLBACK_FAILURE,
  ESL_WIFI_MAC_FAILURE,
  ESL_WIFI_IP_FAILURE,
  ESL_WIFI_DHCP_FAILURE,
  ESL_WIFI_MODE_FAILURE,
  ESL_WIFI_SSID_FAILURE,
  ESL_WIFI_PARAM_FAILURE,
  ESL_WIFI_COMMIT_FAILURE,
  ESL_WIFI_SEC_FAILURE,
  ESL_WIFI_PASS_FAILURE,

  ESL_WIFI_MODULE_OFF,
};

//******************************************************************************
// Public functions
//******************************************************************************

/** Initializes the WIFI module.
 * @param[in] enetDevice  ENET device to be used.
 * @return    ESL_WIFI_OK on success.
 *            ESL_WIFI_ALREADY_INITIALIZED if the module is already initialized.
 *            ESL_WIFI_MAC_FAILURE if default MAC address retrieval fails.
 *            ESL_WIFI_DEVICE_INIT_FAILURE if Atheros driver initialization fails.
 *            ESL_WIFI_HANDLE_FAILURE if device handle retrieval fails.
 *            ESL_WIFI_MSGQ_FAILURE if message queue creation fails. */
uint_8 esl_wifi_init (uint_32 enetDevice);

/** Disconnects from any network, connected by a call to esl_wifi_[MODE]_connect().
 * @return    ESL_WIFI_OK on success.
 *            ESL_WIFI_NOT_INITIALIZED if the module is not initialized yet,
 *             @see esl_wifi_init().
 *            ESL_WIFI_DISCONNECTED when no network is connected.
 *            ESL_WIFI_SSID_FAILURE, ESL_WIFI_COMMIT_FAILURE or
 *             ESL_WIFI_IP_FAILURE if wifi disconnection fails. */
uint_8 esl_wifi_disconnect (void);

/** Checks for new messages from the AtherosWifi task.
 * @param[out]  pMsg  Destination memory where to store the received message.
 *                    Its u8Type field may contain:
 *                     ESL_WIFI_CONNECTED when the connection is established.
 *                     ESL_WIFI_DISCONNECTED when the connection is aborted.
 *                     ESL_WIFI_AUTH_SUCCESS when the Four-way handshake succeeds.
 *                     ESL_WIFI_AUTH_FAILURE when the Four-way handshake fails.
 * @param[in]   uWaitTicks  Number of ticks to wait before timeout.
 *                          Use 0 for infinite wait.
 * @return    ESL_WIFI_OK on success.
 *            ESL_WIFI_TIMEOUT if no message received in given number of ticks.
 *            ESL_WIFI_ERROR if message receiving fails for a different reason.
 *            ESL_WIFI_NOT_INITIALIZED if the module is not initialized yet,
 *             @see esl_wifi_init().
 *            ESL_WIFI_INVALID_ARGUMENT if NULL argument given. */
uint_8 esl_wifi_receiveMsg (ESL_WIFI_TMsg * pMsg, _mqx_uint uWaitTicks);

/** Retrieves the MAC address.
 * @param[out]  acMac   Destination memory. Must be at least
 *                      ESL_WIFI_MAC_BYTES long.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if NULL argument given.
 *          ESL_WIFI_NOT_INITIALIZED if the driver is not ready yet.
 *          ESL_WIFI_BUSY if the device is busy.
 *          ESL_WIFI_ERROR on different failure. */
uint_8 esl_wifi_getMac (char * acMac);

/** Retrieves current network addresses (IP, mask and gateway).
 * @param[out]  pData   Destination memory to store the addresses to.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if NULL argument given.
 *          ESL_WIFI_NOT_INITIALIZED if the driver is not ready yet.
 *          ESL_WIFI_ERROR on different failure. */
uint_8 esl_wifi_getIp4 (IPCFG_IP_ADDRESS_DATA * pData);
/** Sets new network address (IP, mask and gateway).
 * @param[in]   pData   Static addresses to be set. In Client mode, use NULL
 *                      to start DHCP client and fetch a dynamic address instead.
 * @return  ESL_WIFI_OK on success.
 *          ESL_WIFI_INVALID_ARGUMENT if NULL argument given in AP mode.
 *          ESL_WIFI_NOT_INITIALIZED if the driver is not ready yet.
 *          ESL_WIFI_ERROR on different failure. */
uint_8 esl_wifi_setIp4 (const IPCFG_IP_ADDRESS_DATA * pData);

//******************************************************************************
#endif // ESL_WIFI_H_02374547012594538450622305 //
